// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

    AShooterCharacter* ShooterPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (!ShooterPawn) return EBTNodeResult::Failed;

    ShooterPawn->Shoot();

    return EBTNodeResult::Succeeded;
}
