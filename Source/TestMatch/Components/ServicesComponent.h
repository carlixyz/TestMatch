// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Structs/FriendStatus.h"
#include "ServicesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataChange, TArray<FFriendStatus>&, friendProfiles);


/// <summary>
/// Services MODEL Component
/// Main Entry point for processing & answer Social controller data requests
/// [M] <- C -> V
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTMATCH_API UServicesComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UServicesComponent();

	class UDataTable* LoadTableRefFromPath(const FName& Path);

	TArray<FFriendStatus>& ProvideFriendsData();

	/// Everytime We have a change this is Notified abroad
	UPROPERTY(BlueprintAssignable, Category = EventDispatcher)
	FOnDataChange NotifyDataChange;


private:
	UPROPERTY(EditAnywhere, Category = DataBase)
	UDataTable* FriendsTable;

	TArray<FFriendStatus> FriendProfiles;

	/// This Simulates any random change inside the DataTable
	UFUNCTION()
	void ChangeRandomData();

protected:
	virtual void BeginPlay() override;

	TArray<FFriendStatus> ProcessFriendsRawDataTable(UDataTable* friendDataTable);

	FTimerHandle AutoUpdateTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AutoUpdateDelay = 3.0f;

	int32 LastRandomIndex = 0;
		
};
