// Fill out your copyright notice in the Description page of Project Settings.


#include "FIAnimInstance.h"
#include "FollowInstructionsCharacter.h"

void UFIAnimInstance::NativeInitializeAnimation() {
	MainChar = Cast<AFollowInstructionsCharacter>(TryGetPawnOwner());
}

void UFIAnimInstance::UpdateAnimationProperties() {
	if (!MainChar) return;

	bIsRunning = MainChar->bIsSprinting;
	Speed = MainChar->GetVelocity().Size();

	
}
