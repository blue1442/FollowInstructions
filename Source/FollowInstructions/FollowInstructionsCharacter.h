// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FIGlobal.h"
#include "FollowInstructionsCharacter.generated.h"



UCLASS(config=Game)
class AFollowInstructionsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

public:
	AFollowInstructionsCharacter();

	//toggled when user hits shift
	bool bIsSprinting;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AFIPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller")
	float RunSpeed = 400;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	float BaseRunSpeed = 400;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller")
	float WalkSpeed = 300;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	float BaseWalkSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller")
	bool bCheckingPhone;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controller")
	bool bCheckingList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CheckMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	EPlayerLocation CurrentLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Location")
	FDateTime StartDateTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Location")
	FDateTime CurrentDateTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Location")
	int32 TimeMultiplier = 4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
	class UArrowComponent* FarBehindArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sound")
	class UArrowComponent* CloseBehindArrow;

private:
	
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void CheckPhoneStart();
	void CheckPhoneEnd();
	void CheckListStart();
	void CheckListEnd();
	void TurnRight(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void ShiftDown();
	void ShiftUp();
	void UpdateCurrentDateTime();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	void GetTime();

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetPlayerCamera() const { return PlayerCamera; }
	
	UFUNCTION(BlueprintCallable)
	FVector GetCloseBehindArrow();

	UFUNCTION(BlueprintCallable)
	FVector GetFarBehindArrow();

	UFUNCTION(BlueprintCallable)
	float GetRunSpeed();

	UFUNCTION(BlueprintCallable)
	float GetBaseRunSpeed();

	UFUNCTION(BlueprintCallable)
	float GetBaseWalkSpeed();

	UFUNCTION(BlueprintCallable)
	void SetRunSpeed(float a);

	UFUNCTION(BlueprintCallable)
	void SetWalkSpeed(float a);

	UFUNCTION(BlueprintCallable)
	float GetWalkSpeed();

	UFUNCTION(BlueprintCallable)
	void SetCharacterLocation(EPlayerLocation NewLocation);
};

