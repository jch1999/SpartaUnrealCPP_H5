// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Delay = 2.0f;
    NowTime = 0.0f;
    MoveCnt = 0;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay() {
    Super::BeginPlay();
    SetActorLocation(FVector(0, 50, 0));

    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("Hello World!"));
    }
}

// Called every frame
void AMyActor::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (MoveCnt < 10) {
        NowTime += DeltaTime;
        if (Delay <= NowTime) {
            Move();
            Turn();

            // Reset
            MoveCnt++;
            NowTime = 0.0f;

            if (FMath::Rand() % 2 == 0) {
                PlayRandomEvent();
            }
        }
    }
}

void AMyActor::Move() {
    SetActorLocation(FVector(FMath::Rand() % 150, FMath::Rand() % 150, FMath::Rand() % 150));

    if (GEngine) {
        FString DebugMessage = FString::Printf(TEXT("Move : %s"), *(GetActorLocation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, DebugMessage);
    }
}

void AMyActor::Turn() {
    SetActorRotation(FRotator(FMath::Rand() % 360, FMath::Rand() % 360, FMath::Rand() % 360));

    if (GEngine) {
        FString DebugMessage = FString::Printf(TEXT("Rotate : %s"), *(GetActorRotation().ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, DebugMessage);
    }
}

void AMyActor::PlayRandomEvent()
{
    if (GEngine) {
        FString DebugMessage;
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("RandomEvent!"));
        switch (FMath::Rand()%3)
        {
            case 1:
            {
                DebugMessage = FString::Printf(TEXT("CurrentTime : %d"), GetWorld()->GetTimeSeconds());
            }
            break;
            case 2:
            {
                DebugMessage = "Pikaboo!";
            }
            break;
            default:
            {
                DebugMessage = "404 Not Found.";
            }
            break;
        }
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, DebugMessage);
    }
}

