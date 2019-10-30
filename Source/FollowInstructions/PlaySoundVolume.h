// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaySoundVolume.generated.h"
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlaySound : uint8 { //uint8 is the primary type for enums in unreal (unsigned int 8 bits)
	EPS_NONE				UMETA(DisplayName = "None"),

	EPS_AtTargetPoint		UMETA(DisplayName = "AtTargetPoint"),
	EPS_PCloseToFar			UMETA(DisplayName = "PlayerCloseToFar"),
	EPS_PFarToClose			UMETA(DisplayName = "PlayerFarToClose"),
	EPS_AtVolume			UMETA(DisplayName = "AtCenterOfVolume"),
	EPS_FromVolumeToTarget  UMETA(DisplayName = "FromVolumeToTarget"),
	EPS_FromTargetToVolume  UMETA(DisplayName = "FromTargetToVolume")
};
UCLASS()
class FOLLOWINSTRUCTIONS_API APlaySoundVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaySoundVolume();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Locations")
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	class UAudioComponent* AudioComponent;

	//UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Locations")
	//class USceneComponent* SceneComponent;

	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	class ATargetPoint* TargetActor;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings" )
	bool bPlayDuringTimesOnly;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	EPlaySound HowToPlaySound;

	/* remember its military time! integer between 0-24*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings", meta = (EditCondition = "bPlayDuringTimesOnly"))
	int32 StartHourActive;

	/* remember its military time! integer between 0-24*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings", meta = (EditCondition = "bPlayDuringTimesOnly"))
	int32 EndHourActive;

	/*enter integer between 0 and 60*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings", meta = (EditCondition = "bPlayDuringTimesOnly"))
	int32 StartMinuteActive;

	/*enter integer between 0 and 60*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings", meta = (EditCondition = "bPlayDuringTimesOnly"))
	int32 EndMinuteActive;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 NumOfTimesToPlay;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	int32 NumOfTimesToPlayed;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "PlaySettings")
	float TimeToTravel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PlaySoundAtLocation(FVector Location);
	void PlaySoundToAndFrom(FVector StartLocation, FVector EndLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "MoveTarget"))
	void BP_MoveTarget(FVector EndLocation, float TravelTime);

	UFUNCTION()
	virtual void PlayerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void PlayerTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
