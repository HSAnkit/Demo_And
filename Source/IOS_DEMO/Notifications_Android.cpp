// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifications_Android.h"
#include "HelpshiftLibrary.h"

// Sets default values
ANotifications_Android::ANotifications_Android()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANotifications_Android::BeginPlay()
{
	TMap<FString, FHelpshiftConfigParameter> Parameters;
	UHelpshiftLibrary::Init(Parameters);
	Super::BeginPlay();
	FString Token;
	UHelpshiftLibrary::RegisterPushToken(Token);

	
}

// Called every frame
void ANotifications_Android::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANotifications_Android::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

