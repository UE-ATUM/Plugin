﻿// © 2023 Kaya Adrian.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include <sstream>
#include <vector>

#include "AtumLibraryUtilities.generated.h"


#define LOCTEXT_NAMESPACE "AtumLibraryUtilities"

UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Utility Library")
class ATUM_API UAtumLibraryUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template <typename T>
	UE_NODISCARD
	static std::string FormatWithConjunction(
		const std::vector<T>& Values,
		const std::string& Separator,
		const std::string& Prefix = "",
		const std::string& Suffix = "",
		const std::string& Conjunction = "",
		bool bSerialSeparator = true
	) noexcept;
};


template <typename T>
std::string UAtumLibraryUtilities::FormatWithConjunction(
	const std::vector<T>& Values,
	const std::string& Separator,
	const std::string& Prefix,
	const std::string& Suffix,
	const std::string& Conjunction,
	const bool bSerialSeparator
) noexcept
{
	const size_t ValueCount = Values.size();
	if (UNLIKELY(ValueCount == 0ULL))
		return "";
	
	std::ostringstream Stream;
	
	Stream << Prefix;
	if (ValueCount > 1ULL)
	{
		if (ValueCount > 2ULL)
		{
			std::copy(
				Values.begin(),
				Values.end() - 2,
				std::ostream_iterator<T>(Stream, (Suffix + Separator + Prefix).c_str())
			);
		}
		Stream << Values[ValueCount - 2ULL] << Suffix << (bSerialSeparator ? Separator : "") << Conjunction << Prefix;
	}
	Stream << Values.back() << Suffix;
	
	return Stream.str();
}

#undef LOCTEXT_NAMESPACE
