// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCODETUTORIAL_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void BindHp(class UMyActorComponent* ActorComponent);
	void UpdateHp();

private:
	UPROPERTY()
	class UMyActorComponent* MyActorComponent;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* PB_HpBar;
};
