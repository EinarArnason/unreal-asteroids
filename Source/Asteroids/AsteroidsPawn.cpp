// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsteroidsPawn.h"

#include "AsteroidsProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

const FName AAsteroidsPawn::MoveForwardBinding("MoveForward");
const FName AAsteroidsPawn::MoveRightBinding("MoveRight");
const FName AAsteroidsPawn::FireBinding("Fire");

AAsteroidsPawn::AAsteroidsPawn() {
  static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(
      TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
  // Create the mesh component
  ShipMeshComponent =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
  RootComponent = ShipMeshComponent;
  ShipMeshComponent->SetCollisionProfileName(
      UCollisionProfile::Pawn_ProfileName);
  ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

  // Cache our sound effect
  static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(
      TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
  FireSound = FireAudio.Object;

  // Create a camera boom...
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);
  CameraBoom->SetUsingAbsoluteRotation(
      true);  // Don't want arm to rotate when ship does
  CameraBoom->TargetArmLength = 1200.f;
  CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
  CameraBoom->bDoCollisionTest =
      false;  // Don't want to pull camera in when it collides with level

  // Create a camera...
  CameraComponent =
      CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
  CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
  CameraComponent->bUsePawnControlRotation =
      false;  // Camera does not rotate relative to arm

  // Movement
  MoveSpeed = 80.0f;
  MaxVelocity = 100.0f;
  thrustDamping = 0.9f;
  currentMovement = FVector(0.0f, 0.0f, 0.0f);
  // Rotation
  rotationSpeed = 330.0f;
  currentRotation = FRotator(0.0f);
  // Weapon
  GunOffset = FVector(90.f, 0.f, 0.f);
  FireRate = 0.1f;
  bCanFire = true;
}

void AAsteroidsPawn::SetupPlayerInputComponent(
    class UInputComponent* PlayerInputComponent) {
  check(PlayerInputComponent);

  // set up gameplay key bindings
  PlayerInputComponent->BindAxis(MoveForwardBinding);
  PlayerInputComponent->BindAxis(MoveRightBinding);
  PlayerInputComponent->BindAxis(FireBinding);
}

void AAsteroidsPawn::Tick(float DeltaSeconds) {
  // Find movement direction
  const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
  const float RightValue = GetInputAxisValue(MoveRightBinding);

  // Calculate rotation
  if (RightValue) {
    currentRotation =
        currentRotation.Add(0, RightValue * rotationSpeed * DeltaSeconds, 0);
  }

  // Calculate velocity
  if (ForwardValue) {
    currentMovement += currentRotation.Vector().GetUnsafeNormal2D() *
                       MoveSpeed * thrustDamping * DeltaSeconds;
    currentMovement = currentMovement.GetClampedToMaxSize2D(MaxVelocity);
  }

  FHitResult Hit(1.f);
  RootComponent->MoveComponent(currentMovement, currentRotation, true, &Hit);

  // If non-zero size, move this actor
  if (currentMovement.SizeSquared() > 0.0f) {
    if (Hit.IsValidBlockingHit()) {
      const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
      currentMovement = FVector::VectorPlaneProject(currentMovement, Normal2D) *
                        (1.f - Hit.Time);
      RootComponent->MoveComponent(currentMovement, currentRotation, true);
    }
  }

  if (GetInputAxisValue(FireBinding)) {
    // Try and fire a shot
    FireShot(currentRotation.Vector().GetUnsafeNormal2D());
  }
}

void AAsteroidsPawn::FireShot(FVector FireDirection) {
  // If it's ok to fire again
  if (bCanFire == true) {
    // If we are pressing fire stick in a direction
    if (FireDirection.SizeSquared() > 0.0f) {
      const FRotator FireRotation = FireDirection.Rotation();
      // Spawn projectile at an offset from this pawn
      const FVector SpawnLocation =
          GetActorLocation() + FireRotation.RotateVector(GunOffset);

      UWorld* const World = GetWorld();
      if (World != NULL) {
        // spawn the projectile
        World->SpawnActor<AAsteroidsProjectile>(SpawnLocation, FireRotation);
      }

      bCanFire = false;
      World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this,
                                        &AAsteroidsPawn::ShotTimerExpired,
                                        FireRate);

      // try and play the sound if specified
      if (FireSound != nullptr) {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound,
                                              GetActorLocation());
      }

      bCanFire = false;
    }
  }
}

void AAsteroidsPawn::ShotTimerExpired() { bCanFire = true; }