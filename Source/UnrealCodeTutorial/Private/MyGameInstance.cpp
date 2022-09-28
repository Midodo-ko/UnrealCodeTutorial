// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Data(TEXT("DataTable'/Game/Data/CharacterDataTable.CharacterDataTable'"));
	
	if (Data.Succeeded())
	{
		CharacterDataTable = Data.Object;
	}
}

void UMyGameInstance::Init()
{
	//Super::Init();
}

FMyCharacterData* UMyGameInstance::GetCharacterData(int32 Level)
{
	FName RowName = FName(*FString::Printf(TEXT("Lv.%d"), Level));
	return CharacterDataTable->FindRow<FMyCharacterData>(RowName, TEXT(""));
}
