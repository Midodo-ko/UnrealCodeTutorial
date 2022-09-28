// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyAnimInstance.h"
#include "MyActorComponent.h"
#include "Components/WidgetComponent.h"
#include "MyUserWidget.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	X = 0.f;
	Y = 0.f;

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActor"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UW (TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnd);
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::OnHit);
	}

	HpBar->InitWidget();

	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(MyActorComponent);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void AMyCharacter::Attack()
{
	if (IsAttack)
	{
		if (AttackIndex > 3)
		{
			return;
		}
	}
	if (AnimInstance)
	{
		AnimInstance->PlayerAttackAnimation(AttackIndex);
		AttackIndex = ++AttackIndex % 4;
		IsAttack = true;
	}
}

void AMyCharacter::OnHit()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 200.f;
	float AttackRadius = 80.f;

	bool Result = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector Forward = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Forward * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();
	FColor DrawColor;

	if (Result)
	{
		DrawColor = FColor::Green;
	}
	else
	{
		DrawColor = FColor::Red;
	}

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);

	if (Result && HitResult.GetActor())
	{
		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(10.f, DamageEvent, GetController(), this);
	}
}

void AMyCharacter::OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttack = false;
}

float AMyCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	MyActorComponent->OnDamage(Damage);
	return Damage;
}