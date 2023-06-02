// © 2023 Kaya Adrian.

#include "FunctionLibraries/AtumLibraryUtilities.h"

#include "Engine/Texture2D.h"
#include "IAtumModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"


#define LOCTEXT_NAMESPACE "AtumLibraryUtilities"

bool UAtumLibraryUtilities::LoadFileContentFrom(
	const FString& AtumContentRelativePath,
	TArray<FString>& OutContent
) noexcept
{
	const IPlugin* const AtumPlugin = IPluginManager::Get().FindPlugin(IAtumModule::ModuleName.ToString()).Get();
	return LIKELY(AtumPlugin) && FFileHelper::LoadFileToStringArray(
		OutContent,
		*(AtumPlugin->GetContentDir() / AtumContentRelativePath)
	);
}

bool UAtumLibraryUtilities::SetTextureData(UTexture2D* const Texture, const TArray<uint8>& Pixels) noexcept
{
	if (Texture == nullptr)
		return false;
	
	const int32 PixelCount = Pixels.Num();
	if (UNLIKELY(PixelCount != 4 * Texture->GetSizeX() * Texture->GetSizeY()))
		return false;
	
	FByteBulkData& BulkData = Texture->GetPlatformData()->Mips[0].BulkData;
	FMemory::Memcpy(BulkData.Lock(LOCK_READ_WRITE), Pixels.GetData(), PixelCount);
	BulkData.Unlock();
	
	Texture->UpdateResource();
	return true;
}

UTexture2D* UAtumLibraryUtilities::CreateTexture(
	const int32 SizeX,
	const int32 SizeY,
	const TArray<uint8>& Pixels
) noexcept
{
	auto* const Image = UTexture2D::CreateTransient(SizeX, SizeY);
	return SetTextureData(Image, Pixels) ? Image : nullptr;
}

void UAtumLibraryUtilities::CreateEmptyTextures(
	const int32 SizeX,
	const int32 SizeY,
	TArray<UTexture2D*>& OutTextures,
	const int32 Count
) noexcept
{
	OutTextures.Empty(Count);
	for (int32 Index = 0; Index < Count; ++Index)
	{
		OutTextures.Add(UTexture2D::CreateTransient(SizeX, SizeY));
	}
}

#undef LOCTEXT_NAMESPACE
