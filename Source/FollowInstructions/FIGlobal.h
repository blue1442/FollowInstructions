// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FIGlobal.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlayerLocation : uint8 { //uint8 is the primary type for enums in unreal (unsigned int 8 bits)
	EPLS_None				UMETA(DisplayName = "None"),
	EPLS_FFLivingRoom		UMETA(DisplayName = "FirstFloorLivingRoom"),
	EPLS_FFKitch			UMETA(DisplayName = "FirstFloorKitchen"),
	EPLS_FFHallway			UMETA(DisplayName = "FirstFloorHallway"),
	EPLS_FFLibrary			UMETA(DisplayName = "FirstFloorLibrary"),
	EPLS_FFBathroom1		UMETA(DisplayName = "FirstFloorBathroom1"),
	EPLS_FFBathroom2		UMETA(DisplayName = "FirstFloorBathroom2"),
	EPLS_FFBathroom3		UMETA(DisplayName = "FirstFloorBathroom3"),
	EPLS_FFDiningRoom		UMETA(DisplayName = "FirstFloorDiningRoom")
};

UCLASS()
class FOLLOWINSTRUCTIONS_API UFIGlobal : public UObject {
	GENERATED_BODY()
};
