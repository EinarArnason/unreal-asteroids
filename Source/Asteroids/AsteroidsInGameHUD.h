#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "AsteroidsScoreWidget.h"

#include "AsteroidsInGameHUD.generated.h"


UCLASS()
class ASTEROIDS_API AAsteroidsInGameHUD : public AHUD
{
	GENERATED_BODY()
 	  
public:
	AAsteroidsInGameHUD();

	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateScoreCount(int Value);

	UFUNCTION()
	void ResetScore();

	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
	TSubclassOf<UUserWidget> AsteroidsScoreWidgetClass;

private:
	UAsteroidsScoreWidget* AsteroidsScoreWidget;
};