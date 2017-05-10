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

#pragma once

#include "Classes/PolygonPawn.h"

#include "Mechanoid.generated.h"

class AGlider;
class UInputComponent;

UCLASS(BlueprintType, Blueprintable)
class AMechanoid : public APolygonPawn
{
	GENERATED_BODY()

// Creation:
public:
	AMechanoid();
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

public:
// Glider:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGlider* Glider = nullptr;

// Specification:
	UPROPERTY(Category="MechanoidSpecification", EditAnywhere, BlueprintReadOnly)
	float TurnRate;
	UPROPERTY(Category="MechanoidSpecification", EditAnywhere, BlueprintReadOnly)
	float LookUpRate;

// Functions:
	UFUNCTION(BlueprintCallable)
	void SwitchControlToGlider() { SwitchControl((APolygonPawn*)Glider); } // Cast because Glider isn't included

// Control:
	void Turn(float Amount);
	void LookUp(float Amount);

// Events:
	virtual void Tick(float DeltaSeconds) override;
};
