// Fill out your copyright notice in the Description page of Project Settings.


#include "SetupBoard.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void USetupBoard::Activate()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("fen", m_FenNotation);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if(bWasSuccessful)
			{
				TSharedPtr<FJsonObject> JsonObject;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Response->GetContentAsString());
				OnBoardSet.Broadcast();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Request failed");
				OnBoardSetFailed.Broadcast();
			}
		});
	
	Request->SetURL("http://localhost:3000/setupboard");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

USetupBoard* USetupBoard::SetupBoard(FString FenNotation)
{
	USetupBoard* SetupBoard = NewObject<USetupBoard>();
	SetupBoard->m_FenNotation = FenNotation;
	return SetupBoard;
}
