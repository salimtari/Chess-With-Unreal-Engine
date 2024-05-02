// Fill out your copyright notice in the Description page of Project Settings.


#include "StartEngine.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


void UStartEngine::Activate()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if(bWasSuccessful)
			{
				TSharedPtr<FJsonObject> JsonObject;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Response->GetContentAsString());
				OnSuccess.Broadcast();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Request failed");
				OnFailure.Broadcast();
			}
		});
	
	Request->SetURL("http://localhost:3000/startengine");
	Request->SetVerb("POST");
	Request->ProcessRequest();
}

UStartEngine* UStartEngine::StartEngine()
{
	UStartEngine* StartEngine = NewObject<UStartEngine>();
	return StartEngine;
}
