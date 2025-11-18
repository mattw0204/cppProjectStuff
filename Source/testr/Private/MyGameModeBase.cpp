// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Script/testr.PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Script/testr.MyPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
