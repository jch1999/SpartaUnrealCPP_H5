// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
AMyActor::AMyActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Delay = 2.0f;
    NowTime = 0.0f;
    MoveCnt = 0;
    bEnablePhysicsHandle = false;
    RedMaterial = nullptr;
    BlueMaterial = nullptr;
    YellowMaterial = nullptr;

    PhysicsHandle =
        CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay() {
  Super::BeginPlay();
  SetActorLocation(FVector(0, 50, 0));

  UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(
      GetComponentByClass(UStaticMeshComponent::StaticClass()));
  if (MeshComp) {
    RedMaterial =
        UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
    RedMaterial->SetVectorParameterValue("Color", FVector4(1.0f, 0.0f, 0.0f));
    BlueMaterial =
        UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
    BlueMaterial->SetVectorParameterValue("Color", FVector4(0.0f, 0.0f, 1.0f));
    YellowMaterial =
        UMaterialInstanceDynamic::Create(MeshComp->GetMaterial(0), this);
    YellowMaterial->SetVectorParameterValue("Color",
                                            FVector4(1.0f, 1.0f, 0.0f));
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
            } else {
              PrintScreenMessage(3.0f, FColor::Red, TEXT("No RandomEvent!"));
            }
        }
    } else {  // Physics Handle로 PlayerController에서 일정 위치를 유지하며 따라다니기
      
    }
}

void AMyActor::Move() {
  SetActorLocation(
      FVector(FMath::Rand() % 150, FMath::Rand() % 150, FMath::Rand() % 150));

  FString DebugMessage =
      FString::Printf(TEXT("Move : %s"), *(GetActorLocation().ToString()));
  PrintScreenMessage(3.0f, FColor::Purple, DebugMessage);
}

void AMyActor::Turn() {
  SetActorRotation(
      FRotator(FMath::Rand() % 360, FMath::Rand() % 360, FMath::Rand() % 360));

  FString DebugMessage =
      FString::Printf(TEXT("Rotate : %s"), *(GetActorRotation().ToString()));
  PrintScreenMessage(3.0f, FColor::Yellow, DebugMessage);
}

void AMyActor::PlayRandomEvent() {
  PrintScreenMessage(3.0f, FColor::Cyan, TEXT("Play RandomEvent!"));

  FString DebugMessage;
  switch (FMath::Rand() % 4) {
    case 1: {
      DebugMessage = FString::Printf(TEXT("CurrentTime : %d"),
                                     GetWorld()->GetTimeSeconds());
    } break;
    case 2: {
      DebugMessage = "Pikaboo!";
    } break;
    case 3: {
      ChangeColor();
    } break;
    default: {
      DebugMessage = "404 Not Found.";
    } break;
  }
  PrintScreenMessage(3.0f, FColor::Cyan, DebugMessage);
}

void AMyActor::ChangeColor() {
  UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(
      GetComponentByClass(UStaticMeshComponent::StaticClass()));

  if (MeshComp) {
    switch (FMath::Rand() % 3) {
      case 0: {
        if (RedMaterial) {
          MeshComp->SetMaterial(0, RedMaterial);
          PrintScreenMessage(3.0f, FColor::Red, TEXT("Color Change: Red"));
        }
      } break;
      case 1: {
        if (BlueMaterial) {
          MeshComp->SetMaterial(0, BlueMaterial);
          PrintScreenMessage(3.0f, FColor::Blue, TEXT("Color Change: Blue"));
        }
      } break;
      case 2: {
        if (YellowMaterial) {
          MeshComp->SetMaterial(0, YellowMaterial);
          PrintScreenMessage(3.0f, FColor::Yellow,
                             TEXT("Color Change: Yellow"));
        }
      } break;
      default: {
      } break;
    }
  }
}

void AMyActor::SetEnablePhysicsHandle(bool enabled) {
    bEnablePhysicsHandle = enabled;
}

bool AMyActor::GetEnablePhysicsHandle() {
    return bEnablePhysicsHandle; }

void AMyActor::PrintScreenMessage(float LifeTime, const FColor& Color, const FString& Message) {
  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(-1, LifeTime, Color, Message);
  }
}

