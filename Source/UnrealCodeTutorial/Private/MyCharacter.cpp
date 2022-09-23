// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "MyItem.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 600.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/PolygonDungeonRealms/Meshes/Characters/SK_BR_Chr_Demon_01.SK_BR_Chr_Demon_01'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	}

	X = 0.f;
	Y = 0.f;
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


	FName WeaponLeftSocket(TEXT("Hand_LSocket"));
	FName WeaponRightSocket(TEXT("Hand_RSocket"));
	//왼손
	if (GetMesh()->DoesSocketExist(WeaponLeftSocket))
	{
		// 1번째 방법
		/*L_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("L_Weapon"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SW_L(TEXT("StaticMesh'/Game/PolygonDungeonRealms/Meshes/Weapons/SM_Wep_Knife_Large_01.SM_Wep_Knife_Large_01'"));

		if (SW_L.Succeeded())
		{
			L_Weapon->SetStaticMesh(SW_L.Object);
		}


		L_Weapon->SetupAttachment(GetMesh(), WeaponLeftSocket);*/

		// 2번째 방법
		auto MyWeapon = GetWorld()->SpawnActor<AMyItem>(FVector::ZeroVector, FRotator::ZeroRotator);

		if (MyWeapon)
		{
			MyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponLeftSocket);
		}
	}

	// 오른손
	/*if (GetMesh()->DoesSocketExist(WeaponRightSocket))
	{
		R_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("R_Weapon"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh> SW_R(TEXT("StaticMesh'/Game/PolygonDungeonRealms/Meshes/Weapons/SM_Wep_Knife_Large_02.SM_Wep_Knife_Large_02'"));

		if (SW_R.Succeeded())
		{
			R_Weapon->SetStaticMesh(SW_R.Object);
		}

		R_Weapon->SetupAttachment(GetMesh(), WeaponRightSocket);
	}*/
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &AMyCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AMyCharacter::MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyCharacter::LookLeftRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
}

void AMyCharacter::Jump()
{
	if (IsAttack)
	{
		return;
	}
	ACharacter::Jump();
}

void AMyCharacter::MoveForwardBackward(float value)
{
	if (IsAttack)
	{
		return;
	}
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::MoveLeftRight(float value)
{
	if (IsAttack)
	{
		return;
	}
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::LookLeftRight(float value)
{
	AddControllerYawInput(value);
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

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

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
}

void AMyCharacter::OnAttackMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttack = false;
}