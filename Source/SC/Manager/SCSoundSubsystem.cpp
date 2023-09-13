// @jung june


#include "SCSoundSubsystem.h"

#include <Kismet/GameplayStatics.h>
#include <PhysicalMaterials/PhysicalMaterial.h>

void USCSoundSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USCSoundSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USCSoundSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void USCSoundSubsystem::PlaySound(USoundBase* Sound)
{
	if (Sound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Sound);
	}
}

void USCSoundSubsystem::PlayFootstepSound()
{
    FVector Start = FVector(0, 0, 10);
    FVector End = Start - FVector(0, 0, 100);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    USoundBase* Sound = nullptr;

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        const UPhysicalMaterial* PhysicalMaterial = nullptr;

        if (HitResult.PhysMaterial.IsValid())
        {
            PhysicalMaterial = HitResult.PhysMaterial.Get();

            if (PhysicalMaterial)
            {
                if (PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType1)
                {
                    PlaySound(Sound);
                }
                else if (PhysicalMaterial->SurfaceType == EPhysicalSurface::SurfaceType2)
                {
                    PlaySound(Sound);
                }
            }
        }
    }
    else
    {
       //Do Somethings
    }
}
