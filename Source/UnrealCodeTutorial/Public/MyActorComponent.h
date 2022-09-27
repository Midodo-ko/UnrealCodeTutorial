// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCODETUTORIAL_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = true))
		int32 Level;
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = true))
		int32 Hp;
public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:	
	void SetLevel(int32 NewLevel);
	void OnDamage(float DamageAmount);

	int32 GetLevel() { return Level; }
	int32 GetHp() { return Hp; }
};
