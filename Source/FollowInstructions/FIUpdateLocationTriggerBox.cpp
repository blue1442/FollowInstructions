// Fill out your copyright notice in the Description page of Project Settings.


#include "FIUpdateLocationTriggerBox.h"
#include "FollowInstructionsCharacter.h"
#include "GameFramework/Actor.h"

AFIUpdateLocationTriggerBox::AFIUpdateLocationTriggerBox() {
	this->OnActorBeginOverlap.AddDynamic(this, &AFIUpdateLocationTriggerBox::OnOverlapBegin);
	this->OnActorEndOverlap.AddDynamic(this, &AFIUpdateLocationTriggerBox::OnOverlapEnd);
}

void AFIUpdateLocationTriggerBox::BeginPlay() {
	Super::BeginPlay();
}

void AFIUpdateLocationTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor) {
	AFollowInstructionsCharacter* MainChar = Cast<AFollowInstructionsCharacter>(OtherActor);
	if (!MainChar) { return; }
	MainChar->SetCharacterLocation(MyLocation);
}


void AFIUpdateLocationTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor) {

}
