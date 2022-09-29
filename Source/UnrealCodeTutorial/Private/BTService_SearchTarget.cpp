// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MyAIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn != nullptr)
	{
		UWorld* World = CurrentPawn->GetWorld();
		FVector Center = CurrentPawn->GetActorLocation();
		float SearchDistance = 500.f;

		if (World != nullptr)
		{
			TArray<FOverlapResult> OverlapResults;
			FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

			bool bResult = World->OverlapMultiByChannel(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_EngineTraceChannel2,
				FCollisionShape::MakeSphere(SearchDistance),
				QueryParams);
			if (bResult)
			{
				for (auto& OverlapResult : OverlapResults)
				{
					AMyPlayer* MyPlayer = Cast<AMyPlayer>(OverlapResult.GetActor());
					if (MyPlayer)
					{
						if (MyPlayer->GetController()->IsPlayerController())
						{
							OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), MyPlayer);
							DrawDebugSphere(World, Center, SearchDistance, 16, FColor::Green, false, 0.5f);
							return;
						}
					}

					DrawDebugSphere(World, Center, SearchDistance, 16, FColor::Red, false, 0.5f);
				}
			}
			else
			{
				DrawDebugSphere(World, Center, SearchDistance, 16, FColor::Red, false, 0.5f);
			}
		}
	}
}
