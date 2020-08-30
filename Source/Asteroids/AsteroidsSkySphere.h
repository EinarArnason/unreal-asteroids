#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AsteroidsSkySphere.generated.h"

class USkySphereMovementComponent;
class UStaticMeshComponent;

UCLASS(config = Game)
class AAsteroidsSkySphere : public AActor {
  GENERATED_BODY()

  // Sphere collision component
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SkySphere,
            meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* SkySphereMesh;

 public:
  AAsteroidsSkySphere();

  // Returns SkySphereMesh subobject
  FORCEINLINE UStaticMeshComponent* GetSkySphereMesh() const {
    return SkySphereMesh;
  }
};
