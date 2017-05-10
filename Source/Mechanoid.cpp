/*
* Polygon
* Copyright (C) 2017 Krogoth
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Polygon.h"
#include "Classes/Mechanoid.h"
#include "Classes/Glider.h"
#include "Classes/Configuration.h"
#include "GameFramework/Controller.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

// Creation:

AMechanoid::AMechanoid()
{
// Polygon pawn:
	APolygonPawn::Create<UStaticMeshComponent>(true);
}

void AMechanoid::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

// Rotation:
	PlayerInputComponent->BindAxis("Turn", this, &AMechanoid::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMechanoid::LookUp);
}

void AMechanoid::BeginPlay()
{
// Parent:
	Super::BeginPlay();

// Start configuration:
	static ConstructorHelpers::FObjectFinder<UConfiguration>
		StartConfigurationFinder(TEXT("Class'/Game/Mods/Zero/Configurations/Start.Start'"));
	if (StartConfigurationFinder.Succeeded())
	{
		UConfiguration* const StartConfiguration = StartConfigurationFinder.Object;
		UClass* const GliderClass = StartConfiguration->Glider;
		if (GliderClass)
		{
			Glider = GetWorld()->SpawnActor<AGlider>(GliderClass, FVector::ZeroVector, FRotator::ZeroRotator);
			Glider->Mechanoid = this;
			Glider->Equip(StartConfiguration);
		}
	}

	SwitchControlToGlider();
}

// Control:

void AMechanoid::Turn(float Value)
{
	AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}
void AMechanoid::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

// Events:

void AMechanoid::Tick(float DeltaSeconds)
{
}
