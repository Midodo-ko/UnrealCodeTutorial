// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCODETUTORIAL_API AMyPlayer : public AMyCharacter
{
	GENERATED_BODY()
	
	
private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* L_Weapon;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* R_Weapon;
public:
	AMyPlayer();
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

public:
	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);
	void LookLeftRight(float value);
};
