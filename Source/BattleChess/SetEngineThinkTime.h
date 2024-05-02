// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SetEngineThinkTime.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetTimeToThinkDelegate, FString, Output);


UCLASS()
class BATTLECHESS_API USetEngineThinkTime : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FSetTimeToThinkDelegate OnRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FSetTimeToThinkDelegate OnRequestFailed;
	
	virtual void Activate() override;

	UPROPERTY()
	int32 m_TimeToThink;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static USetEngineThinkTime* SetEngineThinkTime(int32 TimeToThink);
	
};
