// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KismetCompilerMisc.h"

#include "K2Node_GetTensorValues.generated.h"


UCLASS(Blueprintable, BlueprintType)
class ATUMUNCOOKED_API UK2Node_GetTensorValues : public UK2Node
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ATUM|K2 Node", meta = (AllowPrivateAccess))
	FName FunctionName;

public:
	UE_NODISCARD_CTOR
	UK2Node_GetTensorValues();

protected:
	class FKCHandler_GetTensorValues : public FNodeHandlingFunctor
	{
	public:
		explicit FKCHandler_GetTensorValues(FKismetCompilerContext& InCompilerContext)
		: FNodeHandlingFunctor(InCompilerContext) {}

		virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override;
	};

public:
	virtual void AllocateDefaultPins() override;

	UE_NODISCARD
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinTypeChanged(UEdGraphPin* Pin) override;

	UE_NODISCARD
	virtual bool IsNodePure() const override;
	
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;

	UE_NODISCARD
	virtual FNodeHandlingFunctor* CreateNodeHandler(FKismetCompilerContext& CompilerContext) const override;
	
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	UE_NODISCARD
	virtual FText GetMenuCategory() const override;
};
