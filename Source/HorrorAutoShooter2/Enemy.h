// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HORRORAUTOSHOOTER2_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemy();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Attack();

	//~AEnemy();

	// called when something enters the sphere component
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// called when something leaves the sphere component
	// UFUNCTION()
	// void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// UFUNCTION()
	// void DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintPure)
	bool IsHit();

	UFUNCTION()
	void SetbHit(bool NewHit);

	UFUNCTION()
	void SetDealDamageDelay(bool bWaitAttack);

	UPROPERTY(VisibleAnywhere)
	bool bDamageDeal = true;

	UPROPERTY(VisibleAnywhere)
	bool bHit = false;

	FTimerHandle AttackTimer;
	FTimerHandle DamageTimer;

	UFUNCTION(BlueprintPure)
	bool InAttackRange();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UPROPERTY(EditAnywhere)
	float AttackDamage = 40.f;

	class UCapsuleComponent* EnemyCapsule;
	UStaticMeshComponent* EnemyMesh;
	
	UPROPERTY(EditAnywhere)
	float AttackDelay = 1.f;
	UPROPERTY(EditAnywhere)
	float DamageDelay = 1.f;

	UPROPERTY(EditAnywhere)
    class USphereComponent* AttackCollision;

	UPROPERTY(EditAnywhere)
    TSubclassOf<USphereComponent> SphereClass;
};
