// © 2023 Kaya Adrian.

#pragma once

#include "UObject/Interface.h"

#include "IAtumSerializable.generated.h"


#define LOCTEXT_NAMESPACE "IAtumSerializable"

/**
 * Interface object class used by the engine
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Serializable")
class UAtumSerializable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Serialisable object interface which offers the ability to save to and load from files
 */
class ATUM_API IAtumSerializable
{
	GENERATED_BODY()
	
public:
	/**
	 * Saves the serialisable object data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure = "false", Category = "ATUM|Serializable")
	bool SaveToFile(const FString& RelativePath) const;
	
	/**
	 * Loads the serialisable object data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Serializable")
	bool LoadFromFile(const FString& RelativePath);
	
protected:
	/**
	 * Saves the serialisable object data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool SaveToFile_Implementation([[maybe_unused]] const FString& RelativePath) const
	PURE_VIRTUAL(IAtumSerializable::SaveToFile, return false;);
	
	/**
	 * Loads the serialisable object data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation([[maybe_unused]] const FString& RelativePath)
	PURE_VIRTUAL(IAtumSerializable::LoadFromFile, return false;);
};

#undef LOCTEXT_NAMESPACE
