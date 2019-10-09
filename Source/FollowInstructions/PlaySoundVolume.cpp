// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySoundVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "Components/AudioComponent.h"

// Sets default values
APlaySoundVolume::APlaySoundVolume() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoundTrigger"));
	TriggerBox->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APlaySoundVolume::BeginPlay() {
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlaySoundVolume::PlayerTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APlaySoundVolume::PlayerTriggerEndOverlap);
}

// Called every frame
void APlaySoundVolume::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlaySoundVolume::PlayerTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

void APlaySoundVolume::PlayerTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

}



