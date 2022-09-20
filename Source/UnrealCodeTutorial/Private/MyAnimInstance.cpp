// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
