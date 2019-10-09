// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaySoundVolume.generated.h"

UCLASS()
class FOLLOWINSTRUCTIONS_API APlaySoundVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaySoundVolume();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locations")
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locations", meta = (EditCondition = "bPlayFromTarget"))
	class ATargetPoint* PlayFromActorLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	bool bPlayFromTarget;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	bool bPlayFromPlayer;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	bool bPlayFromVolume;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 NumOfTimesToPlay;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 NumOfTimesToPlayed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
