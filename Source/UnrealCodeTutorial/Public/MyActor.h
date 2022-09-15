// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNREALCODETUTORIAL_API AMyActor : public AActor
{
	GENERATED_BODY()

private:
	// 엔진에서 확인가능
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	// 엔진에서 수정가능
	UPROPERTY(EditAnywhere, Category = Level)
	int32 level;
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
