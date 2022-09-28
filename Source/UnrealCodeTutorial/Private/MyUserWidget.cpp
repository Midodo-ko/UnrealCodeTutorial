// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "MyActorComponent.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::BindHp(UMyActorComponent* ActorComponent)
{
	MyActorComponent = ActorComponent;
	MyActorComponent->OnHpChanged.AddUObject(this, &UMyUserWidget::UpdateHp);
}

void UMyUserWidget::UpdateHp()
{
	PB_HpBar->SetPercent(MyActorComponent->GetHpRatio());
}
