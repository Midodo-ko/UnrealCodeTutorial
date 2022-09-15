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
	// �������� Ȯ�ΰ���
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	// �������� ��������
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
