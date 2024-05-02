// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "StartEngine.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartEngineDelegate);


UCLASS()
class BATTLECHESS_API UStartEngine : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FStartEngineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FStartEngineDelegate OnFailure;

	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UStartEngine* StartEngine();
};
