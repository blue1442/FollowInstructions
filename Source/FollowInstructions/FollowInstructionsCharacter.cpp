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
#include "Misc/DateTime.h"
#include "Misc/Timespan.h"
#include <TimerManager.h>
#include <Components/ArrowComponent.h>
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


	FarBehindArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FarBehindArrow"));
	FarBehindArrow->SetupAttachment(GetCapsuleComponent());

	CloseBehindArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("CloseBehindArrow"));
	CloseBehindArrow->SetupAttachment(GetCapsuleComponent());

	bCheckingList = false;
	bCheckingPhone = false;

	CurrentLocation = EPlayerLocation::EPLS_None;
}


void AFollowInstructionsCharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<AFIPlayerController>(GetController());
	//PlayerCamera->AttachTo(GetMesh(), "Head");
	StartDateTime = FDateTime(2002, 5, 15, 19);
	CurrentDateTime = FDateTime(2002, 5, 15, 19);
	FTimerHandle Timerhandle;
	GetWorldTimerManager().SetTimer(Timerhandle, this, &AFollowInstructionsCharacter::UpdateCurrentDateTime, 1.0f, true);
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
	PlayerInputComponent->BindAxis("MoveRight", this, &AFollowInstructionsCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &AFollowInstructionsCharacter::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFollowInstructionsCharacter::LookUp);
}

void AFollowInstructionsCharacter::GetTime() {
	UE_LOG(LogTemp, Warning, TEXT("Game Time: %s"), *CurrentDateTime.ToString());
}

FVector AFollowInstructionsCharacter::GetCloseBehindArrow() {
	return CloseBehindArrow->GetComponentLocation();
}

FVector AFollowInstructionsCharacter::GetFarBehindArrow() {
	return FarBehindArrow->GetComponentLocation();
}

float AFollowInstructionsCharacter::GetRunSpeed() { return RunSpeed; }
float AFollowInstructionsCharacter::GetWalkSpeed() { return WalkSpeed; }

void AFollowInstructionsCharacter::SetCharacterLocation(EPlayerLocation NewLocation) {
	CurrentLocation = NewLocation;
}



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
		GetTime();
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

void AFollowInstructionsCharacter::UpdateCurrentDateTime() {
	auto TimeInSeconds = GetWorld()->GetTimeSeconds();
	
	CurrentDateTime = StartDateTime + FTimespan(0, 0, (int32) (TimeInSeconds * TimeMultiplier));
	GetTime();
	/*int32 TimeMultiplier = 15;
	int32 ModMinutes = (CurrentDateTime.GetMinute + TimeToUse / TimeMultiplier) % 60;
	if (ModMinutes > 0) {
		CurrentDateTime.
	}*/
	
}

void AFollowInstructionsCharacter::MoveRight(float Value) {
	if (Controller) {
		auto Direction = GetActorRightVector();
		AddMovementInput(Direction, Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}