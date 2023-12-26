// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PAGameMode.h"

APAGameMode::APAGameMode()
{
	// DefaultPawnClass
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT(""));
	if (DefaultPawnClassRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	//PlayerController
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT(""));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
