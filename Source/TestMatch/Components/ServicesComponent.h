// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Structs/FriendStatus.h"
#include "ServicesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataChange, TArray<FFriendStatus>&, friendProfiles);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTMATCH_API UServicesComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UServicesComponent();

	/// Everytime We have a change this is Notified abroad
	UPROPERTY(BlueprintAssignable, Category = EventDispatcher)
	FOnDataChange NotifyDataChange;

	class UDataTable* LoadTableRefFromPath(const FName& Path);

private:
	UPROPERTY(EditAnywhere, Category = DataBase)
	UDataTable* FriendsTable;

	TArray<FFriendStatus> FriendProfiles;

	/// This Simulates all the random changes inside the DataTable
	UFUNCTION()
	void ChangeRandomData();

protected:
	virtual void BeginPlay() override;

	FTimerHandle AutoUpdateTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AutoUpdateDelay = 3.0f;
		
};
