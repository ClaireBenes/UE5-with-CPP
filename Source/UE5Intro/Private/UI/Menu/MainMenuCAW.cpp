// UI
#include "UI/Menu/MainMenuCAW.h"
#include "UI/MainCommonButtonBase.h"

// Controller
#include "Controller/MainPlayerController.h"

// Settings
#include "Kismet/GameplayStatics.h"

void UMainMenuCAW::NativeConstruct()
{
}

void UMainMenuCAW::OnStartButtonClicked()
{

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