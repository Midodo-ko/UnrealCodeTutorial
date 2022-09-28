// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AMyPlayer::AMyPlayer()
{
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
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

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
		//auto MyWeapon = GetWorld()->SpawnActor<AMyItem>(FVector::ZeroVector, FRotator::ZeroRotator);

		//if (MyWeapon)
		//{
		//	MyWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponLeftSocket);
		//}
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

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &AMyPlayer::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AMyPlayer::MoveLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyPlayer::LookLeftRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyPlayer::Attack);

}

void AMyPlayer::Jump()
{
	if (IsAttack)
	{
		return;
	}
	ACharacter::Jump();
}

void AMyPlayer::MoveForwardBackward(float value)
{
	if (IsAttack)
	{
		return;
	}
	Y = value;
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyPlayer::MoveLeftRight(float value)
{
	X = value;
	AddMovementInput(GetActorRightVector(), value);
}

void AMyPlayer::LookLeftRight(float value)
{
	AddControllerYawInput(value);
}
