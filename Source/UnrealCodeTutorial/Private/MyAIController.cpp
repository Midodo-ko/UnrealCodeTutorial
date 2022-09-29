// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_MyEnemy.BT_MyEnemy'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_MyEnemy.BB_MyEnemy'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}

}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyAIController::RandomMove, 3.f, true);
	
	auto BlackboardComponent = GetBlackboardComponent();
	
	if (UseBlackboard(BlackboardData, BlackboardComponent))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Log, TEXT("It works"));
		}
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMyAIController::RandomMove()
{
	auto CurrentPawn = GetPawn();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	
	if (NavSystem != nullptr)
	{
		FNavLocation RandomLocation;
		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 1000.f, RandomLocation))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
		}
	}
}