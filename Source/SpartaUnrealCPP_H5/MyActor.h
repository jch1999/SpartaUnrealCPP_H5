// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class SPARTAUNREALCPP_H5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move();
	void Turn();

	void PlayRandomEvent();

	void ChangeColor();

	void SetEnablePhysicsHandle(bool enabled);
    bool GetEnablePhysicsHandle();
    void PlayPhysicsHandle();

	void PrintScreenMessage(float LifeTime, const FColor& Color,
            const FString& Message);

   protected:
    UPROPERTY(VisibleAnywhere)
    class UPhysicsHandleComponent* PhysicsHandle;
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComp;

   private:
	float NowTime;
	float Delay;
	int MoveCnt;
	bool bEnablePhysicsHandle;
    
	UPROPERTY(category = "Material", VisibleAnywhere)
    UMaterialInstanceDynamic* RedMaterial;
    UPROPERTY(category = "Material", VisibleAnywhere)
    UMaterialInstanceDynamic* BlueMaterial;
    UPROPERTY(category = "Material", VisibleAnywhere)
    UMaterialInstanceDynamic* YellowMaterial;
};
