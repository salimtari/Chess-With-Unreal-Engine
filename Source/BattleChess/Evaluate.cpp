// Fill out your copyright notice in the Description page of Project Settings.


#include "Evaluate.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UEvaluate::Activate()
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
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
				if(FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					FString BestMove = JsonObject->GetStringField("extractedPart");
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, BestMove);
					OnRequestComplete.Broadcast(BestMove);
				}
				
			}
			else
			{
				OnRequestFailed.Broadcast("Request failed");
			}
		});
	
	Request->SetURL("http://localhost:3000/go");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

UEvaluate* UEvaluate::Evaluate(int TimeToThink)
{
	UEvaluate* Evaluate = NewObject<UEvaluate>();
	Evaluate->m_TimeToThink = TimeToThink;
	return Evaluate;
}
