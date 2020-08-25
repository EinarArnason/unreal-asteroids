#include "AsteroidsSkySphere.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

AAsteroidsSkySphere::AAsteroidsSkySphere() {
  // Static reference to the mesh to use for the projectile
  static ConstructorHelpers::FObjectFinder<UStaticMesh> SkySphereMeshAsset(
      TEXT("/Game/StarDome/StarDome.StarDome"));

  // Create mesh component for the projectile sphere
  SkySphereMesh =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarDome"));
  SkySphereMesh->SetStaticMesh(SkySphereMeshAsset.Object);
  SkySphereMesh->SetupAttachment(RootComponent);
  RootComponent = SkySphereMesh;
}
