// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FIGlobal.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPlayerLocation : uint8 { //uint8 is the primary type for enums in unreal (unsigned int 8 bits)
	EPLS_None				UMETA(DisplayName = "None"),

	EPLS_FFLivingRoom		UMETA(DisplayName = "FirstFloorLivingRoom"),
	EPLS_FFKitchen			UMETA(DisplayName = "FirstFloorKitchen"),
	EPLS_FFHallway			UMETA(DisplayName = "FirstFloorHallway"),
	EPLS_FFLibrary			UMETA(DisplayName = "FirstFloorLibrary"),
	EPLS_FFBathroom1		UMETA(DisplayName = "FirstFloorBathroom1"),
	EPLS_FFBathroom2		UMETA(DisplayName = "FirstFloorBathroom2"),
	EPLS_FFDiningRoom		UMETA(DisplayName = "FirstFloorDiningRoom"),
	EPLS_FFStudy			UMETA(DisplayName = "FirstFloorStudy"),
	EPLS_FFStairs1			UMETA(DisplayName = "FirstFloorStairs1"),
	EPLS_FFCloset			UMETA(DisplayName = "FirstFloorCloset"),

	EPLS_SFBalcony			UMETA(DisplayName = "SecondFloorBalcony"),
	EPLS_SFGameRoom			UMETA(DisplayName = "SecondFloorGameRoom"),
	EPLS_SFBedRoom2			UMETA(DisplayName = "SecondFloorBedRoom2"),
	EPLS_SFMaster			UMETA(DisplayName = "SecondFloorMaster"),
	EPLS_SFCloset2			UMETA(DisplayName = "SecondFloorCloset2"),
	EPLS_SFBathroom			UMETA(DisplayName = "SecondFloorBathroom"),
	EPLS_SFStaircase		UMETA(DisplayName = "SecondFloorStaircase"),

	EPLS_Attic				UMETA(DisplayName = "Attic"),
	EPLS_Basement			UMETA(DisplayName = "Basement")
};

UCLASS()
class FOLLOWINSTRUCTIONS_API UFIGlobal : public UObject {
	GENERATED_BODY()
};
