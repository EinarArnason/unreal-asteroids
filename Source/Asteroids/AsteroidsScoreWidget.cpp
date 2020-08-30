#include "AsteroidsScoreWidget.h"

#include "Engine.h"
#include "UObject/ConstructorHelpers.h"

UAsteroidsScoreWidget::UAsteroidsScoreWidget(
    const FObjectInitializer& ObjectInitializer)
    : UUserWidget(ObjectInitializer) {}

void UAsteroidsScoreWidget::NativeConstruct() { Super::NativeConstruct(); }

void UAsteroidsScoreWidget::UpdateScoreCount(int Value) {
  // only update if more than one hit
  if (TXTScore && Value > 1) {
    if (TXTScore->Visibility == ESlateVisibility::Hidden) {
      TXTScore->SetVisibility(ESlateVisibility::Visible);
    }

    TXTScore->SetText(FText::FromString(("Score: " + FString::FromInt(Value))));
  }
}

void UAsteroidsScoreWidget::ResetScore() {
  GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, __FUNCTION__);

  if (TXTScore) {
    TXTScore->SetVisibility(ESlateVisibility::Hidden);
  }
}