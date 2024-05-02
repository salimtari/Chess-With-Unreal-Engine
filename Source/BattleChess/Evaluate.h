// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Evaluate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEvaluateDelegate, FString, BestMove);

UCLASS()
class BATTLECHESS_API UEvaluate : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FEvaluateDelegate OnRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FEvaluateDelegate OnRequestFailed;
	
	UPROPERTY()
	int m_TimeToThink;

	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UEvaluate* Evaluate(int TimeToThink);
};
