// Fill out your copyright notice in the Description page of Project Settings.

#include "K2Node_GetTensorValues.h"

#include "AtumGraphUtilities.h"
#include "AtumUtilities.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "UK2Node_GetTensorValues"

UK2Node_GetTensorValues::UK2Node_GetTensorValues() : FunctionName(NAME_None), InputClass(nullptr)
{
}

void UK2Node_GetTensorValues::AllocateDefaultPins()
{
	auto* const Schema = GetDefault<const UEdGraphSchema_K2>();
	check(Schema)
	
	UEdGraphPin* const TargetPin = CreatePin(
		EGPD_Input,
		UEdGraphSchema_K2::PC_Interface,
		UAtumTensor::StaticClass(),
		TargetPinName
	);
	check(TargetPin)

	Schema->ConstructBasicPinTooltip(
		*TargetPin,
		LOCTEXT("TargetPinTooltip", ""),
		TargetPin->PinToolTip
	);

	FCreatePinParams ResultPinParams;
	ResultPinParams.ContainerType = EPinContainerType::Array;
	
	UEdGraphPin* const ResultPin = CreatePin(
		EGPD_Output,
		UEdGraphSchema_K2::PC_Byte,
		nullptr,
		ResultPinName,
		ResultPinParams
	);
	check(ResultPin)
	
	Schema->ConstructBasicPinTooltip(
		*ResultPin,
		LOCTEXT("ResultPinTooltip", ""),
		ResultPin->PinToolTip
	);

	Super::AllocateDefaultPins();
}

FText UK2Node_GetTensorValues::GetNodeTitle([[maybe_unused]] const ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("GetTensorValuesNodeTitle", "Get Tensor Values");
}

void UK2Node_GetTensorValues::PinTypeChanged(UEdGraphPin* const Pin)
{
	if (Pin->PinName != ResultPinName)
	{
		Super::PinTypeChanged(Pin);
		return;
	}

	
	Super::PinTypeChanged(Pin);
}

bool UK2Node_GetTensorValues::IsNodePure() const
{
	return true;
}

void UK2Node_GetTensorValues::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* const SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	FCompilerResultsLog& MessageLog = CompilerContext.MessageLog;
	InputClass = UAtumGraphUtilities::GetInputClass(FindPinChecked(TargetPinName, EGPD_Input));
	
	const UFunction* const BlueprintFunction = UAtumUtilities::StaticClass()->FindFunctionByName(FunctionName);
	if (BlueprintFunction == nullptr)
	{
		MessageLog.Error(*FText::Format(
			LOCTEXT("GetTensorValuesInvalidFunction", "Node @@. Type '{0}' is not supported."),
			FText::FromString(InputClass->GetName())
		).ToString(), this);
		
		return;
	}
	
	auto* const CallFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	check(CallFunction)

	CallFunction->SetFromFunction(BlueprintFunction);
	CallFunction->AllocateDefaultPins();
	MessageLog.NotifyIntermediateObjectCreation(CallFunction, this);

	BreakAllNodeLinks();
}

void UK2Node_GetTensorValues::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);

	UClass* const Action = GetClass();
	if (!ActionRegistrar.IsOpenForRegistration(Action))
		return;

	UBlueprintNodeSpawner* const Spawner = UBlueprintNodeSpawner::Create(Action);
	check(Spawner)

	ActionRegistrar.AddBlueprintAction(Action, Spawner);
}

FText UK2Node_GetTensorValues::GetMenuCategory() const
{
	return LOCTEXT("GetTensorValuesMenuCategory", "ATUM|Tensor");
}

#undef LOCTEXT_NAMESPACE
