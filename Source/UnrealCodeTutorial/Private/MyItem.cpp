// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyItem::AMyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Item = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/PolygonDungeonRealms/Meshes/Weapons/SM_Wep_Knife_Small_01.SM_Wep_Knife_Small_01'"));
	if (SM.Succeeded())
	{
		Item->SetStaticMesh(SM.Object);
	}
	Item->SetCollisionProfileName(TEXT("NoCollision"));
	Trigger->SetupAttachment(Item);

	Item->SetCollisionProfileName(TEXT("MyItem"));
	Trigger->SetCollisionProfileName(TEXT("MyItem"));
	Trigger->SetBoxExtent(FVector(20.f, 20.f, 40.f));
}

void AMyItem::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		FName WeaponSocket(TEXT("Hand_LSocket"));
		if (MyCharacter->GetMesh()->DoesSocketExist(WeaponSocket))
		{
			AttachToComponent(MyCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		}
	}
}

void AMyItem::PostInitProperties()
{
	Super::PostInitProperties();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();
}

