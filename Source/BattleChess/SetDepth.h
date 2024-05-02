// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SetDepth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetDepthDelegate, FString, Output);

UCLASS()
class BATTLECHESS_API USetDepth : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FSetDepthDelegate OnRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FSetDepthDelegate OnRequestFailed;
	
	virtual void Activate() override;

	UPROPERTY()
	int32 m_Depth;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static USetDepth* SetDepth(int32 Depth);
	
};
