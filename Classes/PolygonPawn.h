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

#include "GameFramework/Pawn.h"
#include "Components/MeshComponent.h"

#include "PolygonPawn.generated.h"

UENUM()
enum class EViewMode
{
	FirstPerson,
	FirstPersonExtended,
	ThirdPerson
};

UCLASS()
class APolygonPawn : public APawn
{
	GENERATED_BODY()

// Creation:
public:
	APolygonPawn() {}
protected:
	template<class TMeshComponent>
	void Create(bool bCameraRotation);

public:
// View:
	UFUNCTION(BlueprintCallable)
	EViewMode ViewMode() const { return mViewMode; };
	// Use Choose[Mode]View methods to set particular view mode

// Components:
	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadWrite)
	class UMeshComponent* MeshComponent;

	UPROPERTY(Category="Components", VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComponent;

	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* PhysicalComponent() const { return MeshComponent; }

// Functions:
	void SwitchControl(APolygonPawn* NewPawn);

// Control:
	void ChooseFirstPersonView();
	void ChooseFirstPersonExtendedView();
	void ChooseThirdPersonView();

private:
	EViewMode mViewMode = EViewMode::FirstPerson;
};

// Implementation:

// Creation:

template<class TMeshComponent>
void APolygonPawn::Create(bool bCameraRotation)
{
// Mesh:
	MeshComponent = CreateDefaultSubobject<TMeshComponent>(TEXT("PrimaryMesh"));
	MeshComponent->SetupAttachment(RootComponent);
// Root:
	RootComponent = MeshComponent;
// Camera:
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	CameraComponent->bUsePawnControlRotation = bCameraRotation;
}

// Functions:

inline void APolygonPawn::SwitchControl(APolygonPawn* NewPawn)
{
// Check:
	/*if (NewPawn)
	{
		AController* const HoldController = GetController();
		if (HoldController)
		{
			HoldController->UnPossess();
			HoldController->Possess(NewPawn);
		}
	}*/
}

// Control:

inline void APolygonPawn::ChooseFirstPersonView()
{
	MeshComponent->SetOwnerNoSee(true);
}
inline void APolygonPawn::ChooseFirstPersonExtendedView()
{
	MeshComponent->SetOwnerNoSee(true);
}
inline void APolygonPawn::ChooseThirdPersonView()
{
	MeshComponent->SetOwnerNoSee(false);
}
