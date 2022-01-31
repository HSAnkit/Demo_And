// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterpro.h"
#include "HelpshiftLibrary.h"

// Sets default values
AMyCharacterpro::AMyCharacterpro()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacterpro::BeginPlay()
{
	TMap<FString, FHelpshiftConfigParameter> Parameters;
	UHelpshiftLibrary::Init(Parameters);
	Super::BeginPlay();

	// Show FAQs
	UHelpshiftLibrary::ShowFrequentlyAskedQuestions(Parameters);

	
}

// Called every frame
void AMyCharacterpro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterpro::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

