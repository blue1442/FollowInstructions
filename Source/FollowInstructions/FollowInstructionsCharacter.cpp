// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FollowInstructionsCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "FIPlayerController.h"
//////////////////////////////////////////////////////////////////////////
// AFollowInstructionsCharacter

AFollowInstructionsCharacter::AFollowInstructionsCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 70.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// Create a CameraComponent	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
	//PlayerCamera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	PlayerCamera->bUsePawnControlRotation = true;

	bCheckingList = false;
	bCheckingPhone = false;
}


void AFollowInstructionsCharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<AFIPlayerController>(GetController());
	PlayerCamera->AttachTo(GetMesh(), "Head");
}

void AFollowInstructionsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("ShiftDown", IE_Pressed, this, &AFollowInstructionsCharacter::ShiftDown);
	PlayerInputComponent->BindAction("ShiftDown", IE_Released, this, &AFollowInstructionsCharacter::ShiftUp);

	PlayerInputComponent->BindAction("QButton", IE_Pressed, this, &AFollowInstructionsCharacter::CheckPhoneStart);
	PlayerInputComponent->BindAction("QButton", IE_Released, this, &AFollowInstructionsCharacter::CheckPhoneEnd);

	PlayerInputComponent->BindAction("EButton", IE_Pressed, this, &AFollowInstructionsCharacter::CheckListStart);
	PlayerInputComponent->BindAction("EButton", IE_Released, this, &AFollowInstructionsCharacter::CheckListEnd);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFollowInstructionsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &AFollowInstructionsCharacter::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFollowInstructionsCharacter::LookUp);
}

float AFollowInstructionsCharacter::GetRunSpeed() { return RunSpeed; }
float AFollowInstructionsCharacter::GetWalkSpeed() { return WalkSpeed; }



void AFollowInstructionsCharacter::MoveForward(float Value) {
	if (Controller) {
		AddMovementInput(GetActorForwardVector(), Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}
void AFollowInstructionsCharacter::CheckPhoneStart() {
	if (!bCheckingPhone && !bCheckingList) {
		bCheckingPhone = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CheckMontage) {
			AnimInstance->Montage_Play(CheckMontage, 1.0f);
			AnimInstance->Montage_JumpToSection(FName("CheckTime"), CheckMontage);
		}
	}
}

void AFollowInstructionsCharacter::CheckPhoneEnd() {
	bCheckingPhone = false;
}

void AFollowInstructionsCharacter::CheckListStart() {
	if (!bCheckingPhone && !bCheckingList) {
		bCheckingList = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CheckMontage) {
			AnimInstance->Montage_Play(CheckMontage, 1.0f);
			AnimInstance->Montage_JumpToSection(FName("CheckList"), CheckMontage);
		}
	}

}

void AFollowInstructionsCharacter::CheckListEnd() {
	bCheckingList = false;

}
void AFollowInstructionsCharacter::TurnRight(float Value) {
	if (Controller) {
		AddControllerYawInput(Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}

void AFollowInstructionsCharacter::LookUp(float Value) {
	if (Controller) {
		AddControllerPitchInput(Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}

void AFollowInstructionsCharacter::ShiftDown() {
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AFollowInstructionsCharacter::ShiftUp() {
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AFollowInstructionsCharacter::MoveRight(float Value) {
	if (Controller) {
		AddMovementInput(GetActorRightVector(), Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}