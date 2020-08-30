#include "AsteroidsInGameHUD.h"

AAsteroidsInGameHUD::AAsteroidsInGameHUD() {}

void AAsteroidsInGameHUD::BeginPlay() {
  Super::BeginPlay();

  if (AsteroidsScoreWidgetClass) {
    AsteroidsScoreWidget = CreateWidget<UAsteroidsScoreWidget>(
        GetWorld(), AsteroidsScoreWidgetClass);

    // Make sure widget was created
    if (AsteroidsScoreWidget) {
      // Add it to the viewport
      AsteroidsScoreWidget->AddToViewport();
    }
  }
}

void AAsteroidsInGameHUD::Tick(float DeltaSeconds) {
  Super::Tick(DeltaSeconds);
  if (AsteroidsScoreWidget) {
  }
}

void AAsteroidsInGameHUD::DrawHUD() { Super::DrawHUD(); }

void AAsteroidsInGameHUD::UpdateScoreCount(int Value) {
  if (AsteroidsScoreWidget) {
    AsteroidsScoreWidget->UpdateScoreCount(Value);
  }
}

void AAsteroidsInGameHUD::ResetScore() {
  if (AsteroidsScoreWidget) {
    AsteroidsScoreWidget->ResetScore();
  }
}