// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

// Delegate 함수명 F + 아무거나
DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

/**
 * 
 */
UCLASS()
class UNREALCODETUTORIAL_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


private:
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Horizontal;

	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float Vertical;

	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool IsFalling;

	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AttackMontage;

public:
	FOnAttackHit OnAttackHit;

public:
	UMyAnimInstance();
public:
	virtual void NativeUpdateAnimation(float DeletaSeconds) override;
public:
	void PlayerAttackAnimation(int32 index);

	// AnimNotify_이벤트이름()
	UFUNCTION()
		void AnimNotify_Hit();
};
