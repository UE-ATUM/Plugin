// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "K2Node.h"

#include "K2Node_GetTensorValues.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "K2_GetTensorValues")
class ATUMUNCOOKED_API UK2Node_GetTensorValues : public UK2Node
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ATUM|K2 Node", meta = (AllowPrivateAccess))
	FName FunctionName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ATUM|K2 Node", meta = (AllowPrivateAccess))
	TObjectPtr<const UClass> InputClass;

public:
	static inline const FName TargetPinName = TEXT("Target");
	static inline const FName ResultPinName = TEXT("Result");
	
	UE_NODISCARD_CTOR
	UK2Node_GetTensorValues();
	
	virtual void AllocateDefaultPins() override;

	UE_NODISCARD
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	virtual void PinTypeChanged(UEdGraphPin* Pin) override;

	UE_NODISCARD
	virtual bool IsNodePure() const override;
	
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

	UE_NODISCARD
	virtual FText GetMenuCategory() const override;

protected:
	UE_NODISCARD
	FORCEINLINE UEdGraphPin& GetTargetPin() const { return *FindPinChecked(TargetPinName, EGPD_Input); }

	UE_NODISCARD
	FORCEINLINE UEdGraphPin& GetResultPin() const { return *FindPinChecked(ResultPinName, EGPD_Output); }

public:
	UE_NODISCARD
	FORCEINLINE const FName& GetFunctionName() const { return FunctionName; }

	UE_NODISCARD
	FORCEINLINE const UClass* GetInputClass() const { return InputClass.Get(); }
};
