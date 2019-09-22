// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FollowInstructionsCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "FIPlayerController.h"
//////////////////////////////////////////////////////////////////////////
// AFollowInstructionsCharacter

AFollowInstructionsCharacter::AFollowInstructionsCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(36.f, 80.f);

	// set our turn rates for input
	BaseTurnRate = 15.f;
	BaseLookUpRate = 15.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(GetRootComponent()); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	PlayerCamera->bUsePawnControlRotation = true; // Camera does rotate relative to arm
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}


void AFollowInstructionsCharacter::BeginPlay() {
	Super::BeginPlay();
	PlayerController = Cast<AFIPlayerController>(GetController());
}

void AFollowInstructionsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("ShiftDown", IE_Pressed, this, &AFollowInstructionsCharacter::ShiftDown);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFollowInstructionsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &AFollowInstructionsCharacter::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AFollowInstructionsCharacter::LookUp);
}

void AFollowInstructionsCharacter::MoveForward(float Value) {
	if (Controller && (Value != 0.0f)) {
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
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
	//player has pressed shift key, what happens?
}

void AFollowInstructionsCharacter::MoveRight(float Value) {
	if (Controller) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find controller!"));
	}
}