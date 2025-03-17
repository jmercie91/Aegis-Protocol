#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MechCharacter.generated.h" // Include the generated header file

UCLASS()
class AEGISPROTOCOL_API AMechCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMechCharacter();

    void DisableRadar(float DisableDuration);
    void DisableHUD(float DisableDuration);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "EMP Effects")
    bool bIsRadarDisabled;

    UPROPERTY(EditAnywhere, Category = "EMP Effects")
    bool bIsHUDDisabled;

    void RestoreRadar();
    void RestoreHUD();
};