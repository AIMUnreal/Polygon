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
#include "Classes/Glider.h"
#include "Classes/Mechanoid.h"
//#include "Polygon/PolygonProjectile.h"
//#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"
//#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
//#include "MotionControllerComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

// Creation:

AGlider::AGlider()
{
// Polygon pawn:
	APolygonPawn::Create<UStaticMeshComponent>(true);

// Properties:
	//TurnRate = 45.0f;
	//LookUpRate = 45.0f;

	/*
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	*/

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	/*VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.
	*/
	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void AGlider::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

// View:
	PlayerInputComponent->BindAction("ChooseFirstPersonView", IE_Pressed, this, &APolygonPawn::ChooseFirstPersonView);
	PlayerInputComponent->BindAction("ChooseFirstPersonExtendedView", IE_Pressed, this, &APolygonPawn::ChooseFirstPersonExtendedView);
	PlayerInputComponent->BindAction("ChooseThirdPersonView", IE_Pressed, this, &APolygonPawn::ChooseThirdPersonView);
// Rotation:
	PlayerInputComponent->BindAxis("Turn", this, &AGlider::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AGlider::LookUp);
// Movement:
	PlayerInputComponent->BindAxis("Move", this, &AGlider::Move);
	PlayerInputComponent->BindAxis("Strafe", this, &AGlider::Strafe);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGlider::Jump);
// Fire:
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AGlider::Fire);
}

void AGlider::BeginPlay()
{
// Parent:
	APawn::BeginPlay();

// Physics:
	/*PhysicalComponent()->SetSimulatePhysics(true);
	PhysicalComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PhysicalComponent()->OnComponentHit.AddDynamic(this, &AGlider::Hit);*/

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void AGlider::Equip(UConfiguration* Configuration)
{

}

// Control:

void AGlider::Turn(float Value)
{
	AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}
void AGlider::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGlider::Move(float Value)
{
	if (Value != 0.0f)
	{
		//AddMovementInput(GetActorForwardVector(), Value);
		PhysicalComponent()->AddImpulse(FVector(0,0,1000));
	}
}
void AGlider::Strafe(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}
void AGlider::Jump()
{
}

void AGlider::Fire()
{
/*
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<APolygonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<APolygonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
*/
}

// Events:

void AGlider::Tick(float DeltaSeconds)
{
}

void AGlider::Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	/*if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}*/
}

void AGlider::Destroyed()
{
	SwitchControlToMechanoid();
}
