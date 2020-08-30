#include "AsteroidsRock.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AAsteroidsRock::AAsteroidsRock() {
  // Static reference to the mesh to use for the asteroid
  static ConstructorHelpers::FObjectFinder<UStaticMesh> RockMeshAsset(
      TEXT("/Game/Asteroid/Asteroid.Asteroid"));

  // Create mesh component for the asteroids
  RockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid"));
  RockMesh->SetStaticMesh(RockMeshAsset.Object);
  RockMesh->SetupAttachment(RootComponent);
  RockMesh->BodyInstance.SetCollisionProfileName("Rock");
  RockMesh->OnComponentHit.AddDynamic(
      this, &AAsteroidsRock::OnHit);  // set up a notification for when
                                      // this component hits something
  RootComponent = RockMesh;
}

void AAsteroidsRock::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp,
                           FVector NormalImpulse, const FHitResult& Hit) {
  // Only break up asteroid if we hit a physics
  if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) &&
      OtherComp->IsSimulatingPhysics()) {
    // TODO: Break up asteroid into pieces
  }

  Destroy();
}