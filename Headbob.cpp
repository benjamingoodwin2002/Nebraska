// Fill out your copyright notice in the Description page of Project Settings.


#include "Headbob.h"
#include "Camera/CameraShake.h"

UHeadbob::UHeadbob()
{
    OscillationDuration = 1.00f;
    OscillationBlendInTime = 0.1f;
    OscillationBlendOutTime = 0.2f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(0.2f, 0.5f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(8.0f, 10.0f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(0.0f, 0.1f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(3.0f, 5.0f);

    RotOscillation.Roll.Amplitude = FMath::RandRange(0.9f, 1.0f);
    RotOscillation.Roll.Frequency = FMath::RandRange(8.0f, 9.0f);

    LocOscillation.Z.Amplitude = FMath::RandRange(0.9f, 1.0f);
    LocOscillation.Z.Frequency = FMath::RandRange(8.0f, 10.0f);
}
