// @jung june

#pragma once

#include "SC.h"

#include <Subsystems/GameInstanceSubsystem.h>

#include "SCSoundSubsystem.generated.h"

/**
 * 
 */
//enum class ESoundEventType : uint8
//{
//    BGM,
//    SFX,
//};
//
//USTRUCT()
//struct FSoundEvent
//{
//    GENERATED_BODY()
//
//    // 사운드 이벤트 타입
//    UPROPERTY(EditAnywhere)
//    ESoundEventType EventType;
//
//    // 사운드 큐
//    UPROPERTY(EditAnywhere)
//    USoundCue* SoundCue;
//
//    // 볼륨
//    UPROPERTY(EditAnywhere)
//    float Volume;
//
//    // 피치
//    UPROPERTY(EditAnywhere)
//    float Pitch;
//};

UCLASS()
class SC_API USCSoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
};
