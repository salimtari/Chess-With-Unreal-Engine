// Fill out your copyright notice in the Description page of Project Settings.



#include "SetEngineThinkTime.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void USetEngineThinkTime::Activate()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetNumberField("time", m_TimeToThink);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if(bWasSuccessful)
			{
				TSharedPtr<FJsonObject> JsonObject;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Response->GetContentAsString());
				OnRequestComplete.Broadcast(Response->GetContentAsString());
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Request failed");
				OnRequestFailed.Broadcast("Request failed");
			}
		});
	
	Request->SetURL("http://localhost:3000/time");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

USetEngineThinkTime* USetEngineThinkTime::SetEngineThinkTime(int32 TimeToThink)
{
	USetEngineThinkTime* SetEngineThinkTime = NewObject<USetEngineThinkTime>();
	SetEngineThinkTime->m_TimeToThink = TimeToThink;
	return SetEngineThinkTime;
}
