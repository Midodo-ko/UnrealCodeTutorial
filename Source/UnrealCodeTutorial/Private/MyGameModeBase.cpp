// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	ConstructorHelpers::FClassFinder<ACharacter> BP_Character(TEXT("Blueprint'/Game/BluePrint/BP_MyCharacter.BP_MyCharacter_C'"));
	if (BP_Character.Succeeded())
	{
		DefaultPawnClass = BP_Character.Class;
	}
}