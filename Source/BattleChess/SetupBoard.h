// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SetupBoard.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetupBoardDelegate);

UCLASS()
class BATTLECHESS_API USetupBoard : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FSetupBoardDelegate OnBoardSet;
	UPROPERTY(BlueprintAssignable)
	FSetupBoardDelegate OnBoardSetFailed;
	
	UPROPERTY()
	FString m_FenNotation;

	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static USetupBoard* SetupBoard(FString FenNotation);

	
};
