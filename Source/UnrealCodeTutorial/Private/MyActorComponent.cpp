// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyGameInstance.h"
#include "kismet/GameplayStatics.h"

UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
	Level = 1;
}

void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetLevel(Level);
}

void UMyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UMyActorComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto CharacterData = MyGameInstance->GetCharacterData(NewLevel);
		if (CharacterData)
		{
			Level = CharacterData->Level;
			MaxHp = CharacterData->MaxHp;
			Hp = MaxHp;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Lv : %d Hp : %d"), Level, Hp);
}

void UMyActorComponent::OnDamage(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;
	SetHp(NewHp);
}

void UMyActorComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
	{
		Hp = 0;
	}
	OnHpChanged.Broadcast();
}

float UMyActorComponent::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hp : %f"), (float)Hp);
		UE_LOG(LogTemp, Warning, TEXT("MaxHp : %f"), (float)MaxHp);
		return 0.f;
	}
	return (float)Hp / (float)MaxHp;
}