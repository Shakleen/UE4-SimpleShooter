// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

#define BB_PARAM_STARTLOCATION TEXT("StartLocation")

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (Behavior)
    {
        RunBehaviorTree(Behavior);
        PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        GetBlackboardComponent()->SetValueAsVector(
            BB_PARAM_STARTLOCATION,
            GetPawn()->GetActorLocation());
    }
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter *ControllerCharacter = Cast<AShooterCharacter>(GetPawn());

    if (ControllerCharacter)
    {
        return ControllerCharacter->IsDead();
    }

    return true;
}