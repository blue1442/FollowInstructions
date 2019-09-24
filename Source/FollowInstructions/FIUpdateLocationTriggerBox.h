// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FIGlobal.h"
#include "FIUpdateLocationTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class FOLLOWINSTRUCTIONS_API AFIUpdateLocationTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AFIUpdateLocationTriggerBox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	EPlayerLocation MyLocation;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

};

