#include "ProjectileBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBullet::AProjectileBullet()
{
    PrimaryActorTick.bCanEverTick = true;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 5000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    BulletSpeed = 3000.0f;
    Damage = 10.0f;
}

void AProjectileBullet::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectileBullet::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectileBullet::SetBulletSpeed(float Speed)
{
    BulletSpeed = Speed;
    ProjectileMovement->InitialSpeed = Speed;
    ProjectileMovement->MaxSpeed = Speed * 1.5f;
}