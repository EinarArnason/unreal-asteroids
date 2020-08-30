#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AsteroidsRock.generated.h"

class URockMovementComponent;
class UStaticMeshComponent;

UCLASS(config = Game)
class AAsteroidsRock : public AActor {
  GENERATED_BODY()

  // Sphere collision component
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rock,
            meta = (AllowPrivateAccess = "true"))
  UStaticMeshComponent* RockMesh;

 public:
  AAsteroidsRock();

  // Function to handle the asteroid hitting something
  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
             UPrimitiveComponent* OtherComp, FVector NormalImpulse,
             const FHitResult& Hit);

  // Returns RockMesh subobject
  FORCEINLINE UStaticMeshComponent* GetRockMesh() const { return RockMesh; }
};
