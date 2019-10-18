// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySoundVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "Components/AudioComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Engine/LatentActionManager.h>
#include "FollowInstructionsCharacter.h"
#include <GameFramework/Actor.h>

// Sets default values
APlaySoundVolume::APlaySoundVolume() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoundTrigger"));
	TriggerBox->SetupAttachment(Root);

	SoundLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SoundActor"));
	SoundLocation->SetupAttachment(Root);

	SoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundToPlay"));
	SoundComponent->SetupAttachment(SoundLocation);
	NumOfTimesToPlayed = 0;
	NumOfTimesToPlay = 1;
}

// Called when the game starts or when spawned
void APlaySoundVolume::BeginPlay() {
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlaySoundVolume::PlayerTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APlaySoundVolume::PlayerTriggerEndOverlap);
}

void APlaySoundVolume::PlaySoundAtLocation(FVector Location) {
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(SoundLocation, Location, FRotator(0.0f, 0.0f, 0.0f), 
										  false, false, 0.0f, false, EMoveComponentAction::Type::Move, LatentInfo);
	SoundComponent->Play();
}

void APlaySoundVolume::PlaySoundToAndFrom(FVector StartLocation, FVector EndLocation) {
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = nullptr;
	UKismetSystemLibrary::MoveComponentTo(SoundLocation, StartLocation, FRotator(0.0f, 0.0f, 0.0f),
										  false, false, 0.0f, false, EMoveComponentAction::Type::Move, LatentInfo);
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(SoundLocation, EndLocation, FRotator(0.0f, 0.0f, 0.0f),
										  false, false, 0.0f, false, EMoveComponentAction::Type::Move, LatentInfo);
}

// Called every frame
void APlaySoundVolume::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlaySoundVolume::PlayerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!SoundComponent->Sound || NumOfTimesToPlayed == NumOfTimesToPlay) { return; }
	
	if (bPlayDuringTimesOnly) {
		auto MainChar = Cast<AFollowInstructionsCharacter>(OtherActor);
		if (MainChar) {
			FDateTime CurrentTime = MainChar->CurrentDateTime;
			FDateTime StartTime = FDateTime(2002, 5, 15, StartHourActive, StartMinuteActive);
			FDateTime EndTime = FDateTime(2002, 5, 15, EndHourActive, EndHourActive);
			if (CurrentTime < StartTime || CurrentTime > EndTime) {
				return;
			}
		}
	}

	switch (HowToPlaySound) {
	case EPlaySound::EPS_AtTargetPoint:
		break;

	case EPlaySound::EPS_AtVolume:
		break;

	case EPlaySound::EPS_FromVolumeToTarget:
		break;

	case EPlaySound::EPS_PCloseToFar:
		break;

	case EPlaySound::EPS_PFarToClose:
		break;

	default:
		break;
	}

	NumOfTimesToPlayed++;
}


void APlaySoundVolume::PlayerTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}



