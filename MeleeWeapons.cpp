// Aegis Protocol - MeleeWeapons.cpp
// Implements melee attack logic, damage, and knockback effects

#include "MeleeWeapons.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AMeleeWeapons::AMeleeWeapons()
{
    PrimaryActorTick.bCanEverTick = true;
    MeleeType = EMeleeWeaponType::Light;
    bCanAttack = true;

    // Set weapon-specific values
    switch (MeleeType)
    {
    case EMeleeWeaponType::Light:
        AttackDamage = 40.0f;
        AttackRange = 175.0f;
        AttackCooldown = 0.8f;
        KnockbackForce = 500.0f;
        break;
    case EMeleeWeaponType::Heavy:
        AttackDamage = 80.0f;
        AttackRange = 200.0f;
        AttackCooldown = 1.5f;
        KnockbackForce = 1000.0f;
        break;
    case EMeleeWeaponType::Hammer:
        AttackDamage = 60.0f;
        AttackRange = 250.0f;
        AttackCooldown = 2.0f;
        KnockbackForce = 1200.0f;
        break;
    }
}

void AMeleeWeapons::BeginPlay()
{
    Super::BeginPlay();
}

void AMeleeWeapons::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMeleeWeapons::PerformMeleeAttack()
{
    if (CanAttack())
    {
        FVector Start = GetActorLocation();
        FVector End = Start + (GetActorForwardVector() * AttackRange);
        FHitResult HitResult;

        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);

        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams))
        {
            ApplyMeleeDamage(HitResult.GetActor());
        }

        UE_LOG(LogTemp, Log, TEXT("Melee attack performed: %s"), *UEnum::GetValueAsString(MeleeType));

        StartCooldown();
    }
}

void AMeleeWeapons::ApplyMeleeDamage(AActor* Target)
{
    if (Target)
    {
        UGameplayStatics::ApplyDamage(Target, AttackDamage, nullptr, this, nullptr);

        FVector KnockbackDirection = Target->GetActorLocation() - GetActorLocation();
        KnockbackDirection.Normalize();

        if (UPrimitiveComponent* TargetComp = Cast<UPrimitiveComponent>(Target->GetRootComponent()))
        {
            TargetComp->AddImpulse(KnockbackDirection * KnockbackForce, NAME_None, true);
        }

        UE_LOG(LogTemp, Log, TEXT("Hit Target: %s with %f damage"), *Target->GetName(), AttackDamage);

        if (MeleeType == EMeleeWeaponType::Hammer)
        {
            // Apply small AOE damage for Hammer type
            TArray<AActor*> OverlappingActors;
            GetOverlappingActors(OverlappingActors, AActor::StaticClass());

            for (AActor* NearbyActor : OverlappingActors)
            {
                if (NearbyActor != Target)
                {
                    UGameplayStatics::ApplyDamage(NearbyActor, AttackDamage * 0.5f, nullptr, this, nullptr);
                }
            }
        }
    }
}

bool AMeleeWeapons::CanAttack() const
{
    return bCanAttack;
}

void AMeleeWeapons::StartCooldown()
{
    bCanAttack = false;
    GetWorldTimerManager().SetTimer(CaptureTimerHandle, this, &AMeleeWeapons::EndCooldown, AttackCooldown, false);
}

void AMeleeWeapons::EndCooldown()
{
    bCanAttack = true;
}