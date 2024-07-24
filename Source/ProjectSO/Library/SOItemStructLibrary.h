#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SOItemStructLibrary.generated.h"


USTRUCT(BlueprintType)
struct FSOSpawnableItemClasses : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TSubclassOf<AActor> ItemClass; // 여기에 블루프린트 클래스를 담습니다.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TSubclassOf<AActor> AmmoClass; // 여기에 블루프린트 클래스를 담습니다.
	
};
