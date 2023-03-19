// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumNeuralNetworkEditorToolkit.h"

#include "AtumNeuralNetwork.h"
#include "SAtumNeuralNetworkWidget.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkEditorToolkit"

void FAtumNeuralNetworkEditorToolkit::InitEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UAtumNeuralNetwork* const ObjectToEdit
) noexcept
{
	NeuralNetwork = ObjectToEdit;

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(TEXT("AtumNeuralNetworkEditorLayout"))
	->AddArea(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6f)
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab(TEXT("AtumNeuralNetworkTestTab"), ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(TEXT("AtumNeuralNetworkDetailsTab"), ETabState::OpenedTab)
			)
		)
		->Split(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.4f)
			->AddTab(TEXT("OutputLog"), ETabState::OpenedTab)
		)
	);
	
	InitAssetEditor(
		Mode,
		InitToolkitHost, 
		TEXT("AtumNeuralNetworkEditor"),
		Layout,
		true,
		true,
		NeuralNetwork
	);
}

void FAtumNeuralNetworkEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(
		LOCTEXT("WorkspaceMenuCategory", "ATUM Neural Network Editor")
	);

	InTabManager->RegisterTabSpawner(
		TEXT("AtumNeuralNetworkTestTab"),
		FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
		{
			return SNew(SDockTab)[
				SNew(SAtumNeuralNetworkWidget)
			];
		})
	)
	.SetDisplayName(LOCTEXT("TestTab", "Test"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	FDetailsViewArgs DetailsViewArguments;
	DetailsViewArguments.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	
	const TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>(
		TEXT("PropertyEditor")
	).CreateDetailView(DetailsViewArguments);
	DetailsView->SetObject(NeuralNetwork);

	InTabManager->RegisterTabSpawner(
		TEXT("AtumNeuralNetworkDetailsTab"),
		FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
		{
			return SNew(SDockTab)[
				DetailsView
			];
		})
	)
	.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FAtumNeuralNetworkEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterAllTabSpawners();
}

FName FAtumNeuralNetworkEditorToolkit::GetToolkitFName() const
{
	return TEXT("AtumNeuralNetworkEditor");
}

FText FAtumNeuralNetworkEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("BaseToolkitName", "ATUM Neural Network Editor");
}

FString FAtumNeuralNetworkEditorToolkit::GetWorldCentricTabPrefix() const
{
	return TEXT("ATUM Neural Network");
}

FLinearColor FAtumNeuralNetworkEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor();
}

#undef LOCTEXT_NAMESPACE
