// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "AsteroidsPawn.generated.h"

UCLASS(Blueprintable)
class AAsteroidsPawn : public APawn {
  GENERATED_BODY()

  // The mesh component
  UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  class UStaticMeshComponent* ShipMeshComponent;

  // The camera
  UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  class UCameraComponent* CameraComponent;

  // Camera boom positioning the camera above the character
  UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  class USpringArmComponent* CameraBoom;

 public:
  AAsteroidsPawn();

  // Offset from the ships location to spawn projectiles
  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
  FVector GunOffset;

  // How fast the weapon will fire
  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
  float FireRate;

  // The speed our ship moves around the level
  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
  float MoveSpeed;

  // The speed our ship moves around the level
  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
  float MaxVelocity;

  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite,
            meta = (ClampMin = "0.0", ClampMax = "360.0", UIMin = "0.0",
                    UIMax = "360.0"))
  float RotationSpeed;

  UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite,
            meta = (ClampMin = "0.1", ClampMax = "1.0", UIMin = "0.1",
                    UIMax = "1.0"))
  float ThrustDamping;

  // Sound to play each time we fire
  UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
  class USoundBase* FireSound;

  // Begin Actor Interface
  virtual void Tick(float DeltaSeconds) override;
  virtual void SetupPlayerInputComponent(
      class UInputComponent* InputComponent) override;
  // End Actor Interface

  // Fire a shot in the specified direction
  void FireShot(FVector FireDirection);

  // Handler for the fire timer expiry
  void ShotTimerExpired();

  int GetCurrentScore() const;
  void IncrementScore();

  // Static names for axis bindings
  static const FName MoveForwardBinding;
  static const FName MoveRightBinding;
  static const FName FireBinding;

 private:
  // Flag to control firing
  uint32 bCanFire : 1;

  // Handle for efficient management of ShotTimerExpired timer
  FTimerHandle TimerHandle_ShotTimerExpired;
  FVector CurrentMovement;
  FRotator CurrentRotation;

  // Score
  int Score;

 public:
  // Returns ShipMeshComponent subobject **/
  FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const {
    return ShipMeshComponent;
  }
  // Returns CameraComponent subobject **/
  FORCEINLINE class UCameraComponent* GetCameraComponent() const {
    return CameraComponent;
  }
  // Returns CameraBoom subobject **/
  FORCEINLINE class USpringArmComponent* GetCameraBoom() const {
    return CameraBoom;
  }
};
