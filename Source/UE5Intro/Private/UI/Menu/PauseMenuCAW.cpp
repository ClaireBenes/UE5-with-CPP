// UI
#include "UI/Menu/PauseMenuCAW.h"
#include "UI/MainCommonButtonBase.h"

// Controller
#include "Controller/MainPlayerController.h"

// Settings
#include "Kismet/GameplayStatics.h"

void UPauseMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind all buttons
	if( BIND_Resume_Button )
	{
		BIND_Resume_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::CloseMenu);
	}
	if( BIND_Restart_Button )
	{
		BIND_Restart_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnRestartButtonClicked);
	}
	if( BIND_Quit_Button )
	{
		BIND_Quit_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnQuitButtonClicked);
	}
	if( BIND_Option_Button )
	{
		BIND_Option_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnOptionButtonClicked);
	}
	if( BIND_MainMenu_Button )
	{
		BIND_MainMenu_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnMainMenuButtonClicked);
	}
}

void UPauseMenuCAW::OpenMenu()
{
	Super::OpenMenu();

	// Show mouse cursor
	if( PlayerController.IsValid() )
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly{});
	}

	// Pause game
	UGameplayStatics::SetGamePaused(this, true);
}

void UPauseMenuCAW::CloseMenu()
{
	// Hide mouse cursor
	if( PlayerController.IsValid() )
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly{});
	}
 
	// Unpause game
	UGameplayStatics::SetGamePaused(this, false);

	Super::CloseMenu();
}

void UPauseMenuCAW::OnRestartButtonClicked()
{
	// Restart Current level
	FName LevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, LevelName);

	// This cpde will be called after restarting the level
	// We need to update this reference since our controller will be destroyed
	if( !PlayerController.IsValid() )
	{
		// Get Player Controller
		PlayerController = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}
	// Go back to Game Mode
	if( PlayerController.IsValid() )
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeGameOnly{});
	}
}
void UPauseMenuCAW::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const FString IsVisible = GetVisibility() == ESlateVisibility::Visible ? FString("TRUE") : FString("FALSE");
	UE_LOG(LogTemp, Log, TEXT("PAUSE MENU VISIBLE %s"), *IsVisible);
}

void UPauseMenuCAW::OnQuitButtonClicked()
{
	if( PlayerController.IsValid() )
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController.Get(), EQuitPreference::Quit, true);
	}
}

void UPauseMenuCAW::OnOptionButtonClicked()
{
	AddWidgetFromSubsystem(BIND_Option_Button->GetName());
}

void UPauseMenuCAW::OnMainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(this, MainMenudMapName);
}


