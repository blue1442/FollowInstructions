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
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUOEnemySpawner::EnemyTriggerBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUOEnemySpawner::EnemyTriggerEndOverlap);
}

// Called every frame
void APlaySoundVolume::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void APlaySoundVolume::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {

}

void APlaySoundVolume::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {

}

