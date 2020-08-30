// Copyright Epic Games, Inc. All Rights Reserved.

#include "AsteroidsGameMode.h"

#include "AsteroidsInGameHUD.h"
#include "AsteroidsPawn.h"

AAsteroidsGameMode::AAsteroidsGameMode() {
  // set default pawn class to our character class
  DefaultPawnClass = AAsteroidsPawn::StaticClass();
  HUDClass = AAsteroidsInGameHUD::StaticClass();
}
