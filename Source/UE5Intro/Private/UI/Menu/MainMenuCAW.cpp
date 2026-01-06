// UI
#include "UI/Menu/MainMenuCAW.h"
#include "UI/MainCommonButtonBase.h"

// Controller
#include "Controller/MainPlayerController.h"

// Settings
#include "Kismet/GameplayStatics.h"

void UMainMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind Buttons
	if( BIND_Start_Button )
	{
		BIND_Start_Button->OnButtonClicked.AddUniqueDynamic(this, &UMainMenuCAW::OnStartButtonClicked);
	}
	if( BIND_Quit_Button )
	{
		BIND_Quit_Button->OnButtonClicked.AddUniqueDynamic(this, &UMainMenuCAW::OnQuitButtonClicked);
	}
	if( BIND_Option_Button )
	{
		BIND_Option_Button->OnButtonClicked.AddUniqueDynamic(this, &UMainMenuCAW::OnOptionButtonClicked);
	}
}

void UMainMenuCAW::OpenMenu()
{
	Super::OpenMenu();

	// Show mouse cursor
	if( PlayerController.IsValid() )
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly{});
	}
}

void UMainMenuCAW::OnStartButtonClicked()
{
	// Check Controller and Map Name
	if( MainWorldMapName.IsNone() || !PlayerController.IsValid() )
	{
		return;
	}

	// Hide mouse cursor
	if( PlayerController.IsValid() )
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly{});
	}

	// Open new level
	UGameplayStatics::OpenLevel(PlayerController->GetWorld(), MainWorldMapName);
}

void UMainMenuCAW::OnQuitButtonClicked()
{
	if( PlayerController.IsValid() )
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController.Get(), EQuitPreference::Quit, true);
	}
}

void UMainMenuCAW::OnOptionButtonClicked()
{
	AddWidgetFromSubsystem(BIND_Option_Button->GetName());
}