#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBullet.generated.h"

UCLASS()
class AEGISPROTOCOL_API AProjectileBullet : public AActor
{
    GENERATED_BODY()

public:
    AProjectileBullet();
    virtual void Tick(float DeltaTime) override;
    void SetBulletSpeed(float Speed);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Bullet Stats")
    float BulletSpeed;

    UPROPERTY(EditAnywhere, Category = "Bullet Stats")
    float Damage;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;
};