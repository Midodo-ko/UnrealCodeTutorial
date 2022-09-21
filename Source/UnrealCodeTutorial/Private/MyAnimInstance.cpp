// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> A_Montage(TEXT("AnimMontage'/Game/Animation/Attack_Montage.Attack_Montage'"));
	if (A_Montage.Succeeded())
	{
		AttackMontage = A_Montage.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeletaSeconds)
{
	Super::NativeUpdateAnimation(DeletaSeconds);
	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
		auto Character = Cast<AMyCharacter>(Pawn);

		if (IsValid(Character))
		{
			Vertical = Character->GetY();
			Horizontal = Character->GetX();

			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UMyAnimInstance::PlayerAttackAnimation()
{
	Montage_Play(AttackMontage, 1.f);
}
