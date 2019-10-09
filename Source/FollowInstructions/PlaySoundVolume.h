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
	bool bPlayDuringTimesOnly;

	/* remember its military time! integer between 0-24*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 StartHourActive;

	/* remember its military time! integer between 0-24*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 EndHourActive;

	/*enter integer between 0 and 60*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 StartMinuteActive;

	/*enter integer between 0 and 60*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 EndMinuteActive;

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
	virtual void PlayerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void PlayerTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
