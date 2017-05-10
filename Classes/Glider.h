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
#include "Equipment.h"

#include "Glider.generated.h"

class AMechanoid;
DECLARATION_EQUIPMENT()
class UConfiguration;
class UInputComponent;

UCLASS(BlueprintType, Blueprintable)
class AGlider : public APolygonPawn
{
	GENERATED_BODY()

// Creation:
public:
	AGlider();
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void BeginPlay() override;

public:
// Mechanoid:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMechanoid* Mechanoid = nullptr;

// Specification:
	UPROPERTY(Category="GliderSpecification", EditAnywhere, BlueprintReadOnly)
	float TurnRate;
	UPROPERTY(Category="GliderSpecification", EditAnywhere, BlueprintReadOnly)
	float LookUpRate;

	GLIDER_SLOTS_BODY()

	GLIDER_EQUIPMENT_BODY()

	UFUNCTION(BlueprintCallable)
	void Equip(UConfiguration* Configuration);

// Components:
	//UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	//class USphereComponent* ShieldComponent;

/*
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class APolygonProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;
*/

// Functions:
	UFUNCTION(BlueprintCallable)
	void SwitchControlToMechanoid() { SwitchControl((APolygonPawn*)Mechanoid); } // Cast because Mechanoid isn't included

// Control:
	void Turn(float Value);
	void LookUp(float Value);

	void Move(float Value);
	void Strafe(float Value);
	void Jump();

	void Fire();

// Events:
	virtual void Tick(float DeltaSeconds) override;
	void Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);
	virtual void Destroyed() override;
};
