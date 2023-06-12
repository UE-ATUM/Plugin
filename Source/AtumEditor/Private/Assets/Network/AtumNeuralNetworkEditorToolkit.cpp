// © 2023 Kaya Adrian.

#include "Assets/Network/AtumNeuralNetworkEditorToolkit.h"

#include "DetailsViewArgs.h"
#include "Layers/Network/AtumNeuralNetwork.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "Widgets/Docking/SDockTab.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkEditorToolkit"

const FName FAtumNeuralNetworkEditorToolkit::AtumNeuralNetworkAppIdentifier = TEXT("AtumNeuralNetworkEditor");


FAtumNeuralNetworkEditorToolkit::FAtumNeuralNetworkEditorToolkit() noexcept : NeuralNetwork(nullptr)
{
}

void FAtumNeuralNetworkEditorToolkit::InitEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UAtumNeuralNetwork* const NetworkToEdit
) noexcept
{
	NeuralNetwork = NetworkToEdit;
	OnPostCDOCompiledHandle = UAtumNeuralNetwork::OnPostCDOCompiled->AddLambda([this] { CloseWindow(); });
	
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(TEXT("AtumNeuralNetworkEditorLayout"))
	->AddArea(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6F)
			->SetOrientation(Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(1.0F)
				->AddTab(TEXT("AtumNeuralNetworkDetailsTab"), ETabState::OpenedTab)
			)
		)
		->Split(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.4F)
			->AddTab(TEXT("OutputLog"), ETabState::OpenedTab)
		)
	);
	
	static CONSTEXPR bool bCreateDefaultStandaloneMenu = true;
	static CONSTEXPR bool bCreateDefaultToolbar = true;
	static CONSTEXPR bool bInIsToolbarFocusable = false;
	static CONSTEXPR bool bInUseSmallToolbarIcons = false;
	InitAssetEditor(
		Mode,
		InitToolkitHost, 
		AtumNeuralNetworkAppIdentifier,
		Layout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolbar,
		NeuralNetwork,
		bInIsToolbarFocusable,
		bInUseSmallToolbarIcons
	);
	RegenerateMenusAndToolbars();
}

void FAtumNeuralNetworkEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(
		LOCTEXT("WorkspaceMenuCategory", "ATUM Neural Network Editor")
	);
	
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

FText FAtumNeuralNetworkEditorToolkit::GetToolkitName() const
{
	return NeuralNetwork ? GetToolTipTextForObject(NeuralNetwork) : INVTEXT("");
}

FString FAtumNeuralNetworkEditorToolkit::GetWorldCentricTabPrefix() const
{
	return TEXT("ATUM Neural Network");
}

FLinearColor FAtumNeuralNetworkEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(1.0F, 1.0F, 1.0F, 1.0F);
}

void FAtumNeuralNetworkEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(NeuralNetwork);
}

FString FAtumNeuralNetworkEditorToolkit::GetReferencerName() const
{
	return GetNameSafe(NeuralNetwork);
}

bool FAtumNeuralNetworkEditorToolkit::CloseWindow()
{
	UAtumNeuralNetwork::OnPostCDOCompiled->Remove(OnPostCDOCompiledHandle);
	return FAssetEditorToolkit::CloseWindow();
}

#undef LOCTEXT_NAMESPACE
