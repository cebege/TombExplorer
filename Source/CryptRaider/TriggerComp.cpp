// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComp.h"

UTriggerComp::UTriggerComp()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComp::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Mover == nullptr)
    {
        return;
    }

    AActor* Actor = GetAcceptableActor();
    if (Actor != nullptr)
    {
    //   UE_LOG(LogTemp, Display, TEXT("Unlocking"));
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component != nullptr)
        {
            Component->SetSimulatePhysics(false);
        }
        Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        Mover->SetShouldMove(true);
    }
    else
    {
    //   UE_LOG(LogTemp, Display, TEXT("Relocking"));
        Mover->SetShouldMove(false);
    }
}

void UTriggerComp::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}

AActor* UTriggerComp::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for (AActor* Actor : Actors)
    {
        bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
        bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (HasAcceptableTag && !IsGrabbed)
        {
            return Actor;
        }
    }
    return nullptr;
}

