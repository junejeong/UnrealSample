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
//    // ���� �̺�Ʈ Ÿ��
//    UPROPERTY(EditAnywhere)
//    ESoundEventType EventType;
//
//    // ���� ť
//    UPROPERTY(EditAnywhere)
//    USoundCue* SoundCue;
//
//    // ����
//    UPROPERTY(EditAnywhere)
//    float Volume;
//
//    // ��ġ
//    UPROPERTY(EditAnywhere)
//    float Pitch;
//};

UCLASS()
class SC_API USCSoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
};
