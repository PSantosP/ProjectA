// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PAGameMode.h"

APAGameMode::APAGameMode()
{
	// DefaultPawnClass
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ProjectA/Blueprints/BP_PACharacterPlayer.BP_PACharacterPlayer_C"));
	if (DefaultPawnClassRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	//PlayerController
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/ProjectA/Blueprints/BP_PAPlayerController.BP_PAPlayerController_C"));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
