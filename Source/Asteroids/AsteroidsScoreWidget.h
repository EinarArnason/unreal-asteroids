#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"

#include "AsteroidsScoreWidget.generated.h"

UCLASS()
class ASTEROIDS_API UAsteroidsScoreWidget : public UUserWidget {
  GENERATED_BODY()

 public:

  UAsteroidsScoreWidget(const FObjectInitializer& ObjectInitializer);

  virtual void NativeConstruct() override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
  class UTextBlock* TXTScore;

  void UpdateScoreCount(int Value);

  void ResetScore();
};