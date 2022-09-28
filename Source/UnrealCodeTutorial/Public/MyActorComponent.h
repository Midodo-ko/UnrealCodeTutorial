// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCODETUTORIAL_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()


private:
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = true))
		int32 Level;
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = true))
		int32 Hp;
	UPROPERTY(EditAnywhere, Category = Info, meta = (AllowPrivateAccess = true))
		int32 MaxHp;
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
	void SetHp(int32 NewHp);
	float GetHpRatio();

	int32 GetLevel() { return Level; }
	int32 GetHp() { return Hp; }
	int32 GetMaxHp() { return MaxHp; }

public:
	FOnHpChanged OnHpChanged;
};
