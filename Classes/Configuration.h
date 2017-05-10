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
* along with this program.  If not, see <http://www.gnu.org/licenses/*.
*/

#pragma once

#include "Classes/Glider.h"
#include "Equipment.h"

#include "Configuration.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UConfiguration : public UObject
{
	GENERATED_BODY()

public:
	UConfiguration();

// Glider:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UClass* Glider;

// Equipment:
	CONFIGURATION_EQUIPMENT_BODY()

// Utilities:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UClass*> Utilities;

// Goods:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UClass*> Goods;

protected:
	static constexpr TCHAR AboutUpdate[] =
		TEXT("Value is not updated when the Glider class is changed. Reset Glider class to update the value.");
// Update slots count when Glider is changed:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override {};
};

// Implementation:

inline UConfiguration::UConfiguration()
{
	RESERVE_CONFIGURATION_SLOTS();
	Utilities.Reserve(10);
	Goods.Reserve(10);
}

/*void UConfiguration::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.ChangeType == EPropertyChangeType::ValueSet)
	{
		FString const Property = PropertyChangedEvent.MemberProperty->GetNameCPP();
		if (Property == "Glider")
		{
			if (Glider)
			{
				AGlider* const NewGlider = Cast<AGlider>(Glider->GetDefaultObject(true));
				UPDATE_CONFIGURATION_SLOTS(NewGlider);
			}
			// No Glider:
			else
			{
				RESET_CONFIGURATION_SLOTS();
			}
		}
	}
}
*/