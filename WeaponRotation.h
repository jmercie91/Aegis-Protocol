// Aegis Protocol - WeaponRotation.h
// Handles weapon rotation mechanics for fine-tuning shot alignment.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponRotation.generated.h"

UCLASS()
class AEGISPROTOCOL_API AWeaponRotation : public AActor
{
    GENERATED_BODY()

public:
    AWeaponRotation();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Rotates the weapon along its axis based on user input
    UFUNCTION(BlueprintCallable, Category = "Weapon Rotation")
    void RotateWeapon(float RotationAmount);

    // Resets weapon to default rotation
    UFUNCTION(BlueprintCallable, Category = "Weapon Rotation")
    void ResetWeaponRotation();

    // Returns the current rotation of the weapon
    UFUNCTION(BlueprintCallable, Category = "Weapon Rotation")
    FRotator GetCurrentRotation() const;

    // Sets the weapon rotation manually (for saved loadouts)
    UFUNCTION(BlueprintCallable, Category = "Weapon Rotation")
    void SetWeaponRotation(FRotator NewRotation);

private:
    // The weapon’s current rotation
    UPROPERTY(VisibleAnywhere, Category = "Weapon Rotation")
    FRotator WeaponRotation;

    // Rotation speed modifier
    UPROPERTY(EditAnywhere, Category = "Weapon Rotation")
    float RotationSpeed;
};