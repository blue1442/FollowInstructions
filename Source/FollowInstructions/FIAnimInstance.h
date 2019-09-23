// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FOLLOWINSTRUCTIONS_API UFIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = "Animation Properties")
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	class AFollowInstructionsCharacter* MainChar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;
};
