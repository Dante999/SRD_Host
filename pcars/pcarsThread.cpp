#include "pcarsThread.h"
#include <QDebug>
#include <QThread>


#define MEMORY_KEY "$pcars$"




PcarsThread::PcarsThread(gameDataStruct *data) : loopThread(100)
{
    this->gameData = data;

    sharedMemory.setNativeKey(MEMORY_KEY);
    sharedMemory.attach(QSharedMemory::ReadOnly);

    pcarsData = reinterpret_cast<MemoryMap_Pcars*> (sharedMemory.data());
}



void PcarsThread::processLoop()
{
    ParticipantInfo *racerInfo = pcarsData->mParticipantInfo;

    gameData->racePosition = racerInfo->mRacePosition;

    gameData->gear = (uint8_t) pcarsData->mGear;
    gameData->rpm = pcarsData->mRpm;
    gameData->maxRpm = pcarsData->mMaxRPM;
    gameData->speed = (pcarsData->mSpeed * 3.6);
    gameData->fuelLevel = (pcarsData->mFuelLevel * pcarsData->mFuelCapacity);
    gameData->fuelCapacity = pcarsData->mFuelCapacity;

    gameData->tempOil = pcarsData->mOilTempCelsius;
    gameData->tempWater = pcarsData->mWaterTempCelsius;
    gameData->tempBrake[eTYRE_FRONT_LEFT] = pcarsData->mBrakeTempCelsius[TYRE_FRONT_LEFT];
    gameData->tempBrake[eTYRE_FRONT_RIGHT] = pcarsData->mBrakeTempCelsius[TYRE_FRONT_RIGHT];
    gameData->tempBrake[eTYRE_REAR_LEFT] = pcarsData->mBrakeTempCelsius[TYRE_REAR_LEFT];
    gameData->tempBrake[eTYRE_REAR_RIGHT] = pcarsData->mBrakeTempCelsius[TYRE_REAR_RIGHT];
    gameData->tempTyre[eTYRE_FRONT_LEFT] = pcarsData->mTyreTemp[TYRE_FRONT_LEFT];
    gameData->tempTyre[eTYRE_FRONT_RIGHT] = pcarsData->mTyreTemp[TYRE_FRONT_RIGHT];
    gameData->tempTyre[eTYRE_REAR_LEFT] = pcarsData->mTyreTemp[TYRE_REAR_LEFT];
    gameData->tempTyre[eTYRE_REAR_RIGHT] = pcarsData->mTyreTemp[TYRE_REAR_RIGHT];

    gameData->damageAero = pcarsData->mAeroDamage * 100;
    gameData->damageEngine = pcarsData->mEngineDamage * 100;
    gameData->damageBrake[eTYRE_FRONT_LEFT] = pcarsData->mBrakeDamage[TYRE_FRONT_LEFT] * 100;
    gameData->damageBrake[eTYRE_FRONT_RIGHT] = pcarsData->mBrakeDamage[TYRE_FRONT_RIGHT] * 100;
    gameData->damageBrake[eTYRE_REAR_LEFT] = pcarsData->mBrakeDamage[TYRE_REAR_LEFT] * 100;
    gameData->damageBrake[eTYRE_REAR_RIGHT] = pcarsData->mBrakeDamage[TYRE_REAR_RIGHT] * 100;
    gameData->damageSuspension[eTYRE_FRONT_LEFT] = pcarsData->mSuspensionDamage[TYRE_FRONT_LEFT] * 100;
    gameData->damageSuspension[eTYRE_FRONT_RIGHT] = pcarsData->mSuspensionDamage[TYRE_FRONT_RIGHT] * 100;
    gameData->damageSuspension[eTYRE_REAR_LEFT] = pcarsData->mSuspensionDamage[TYRE_REAR_LEFT] * 100;
    gameData->damageSuspension[eTYRE_REAR_RIGHT] = pcarsData->mSuspensionDamage[TYRE_REAR_RIGHT] * 100;
    gameData->damageTyre[eTYRE_FRONT_LEFT] = pcarsData->mTyreWear[TYRE_FRONT_LEFT] * 100;
    gameData->damageTyre[eTYRE_FRONT_RIGHT] = pcarsData->mTyreWear[TYRE_FRONT_RIGHT] * 100;
    gameData->damageTyre[eTYRE_REAR_LEFT] = pcarsData->mTyreWear[TYRE_REAR_LEFT] * 100;
    gameData->damageTyre[eTYRE_REAR_RIGHT] = pcarsData->mTyreWear[TYRE_REAR_RIGHT] * 100;

    gameData->timeBestLap = pcarsData->mBestLapTime;
    gameData->timeLastLap = pcarsData->mLastLapTime;
    gameData->timeCurrentSector1 = pcarsData->mCurrentSector1Time;
    gameData->timeCurrentSector2 = pcarsData->mCurrentSector2Time;
    gameData->timeCurrentSector3 = pcarsData->mCurrentSector3Time;
    gameData->timeFastestSector1 = pcarsData->mFastestSector1Time;
    gameData->timeFastestSector2 = pcarsData->mFastestSector2Time;
    gameData->timeFastestSector3 = pcarsData->mFastestSector3Time;
    gameData->timeSplitAhead = pcarsData->mSplitTimeAhead;
    gameData->timeSplitBehind = pcarsData->mSplitTimeBehind;
}

void PcarsThread::processStopping()
{
    // Nothing to do
}




bool PcarsThread::isGameRunning()
{
    QSharedMemory pcarsData;
    pcarsData.setNativeKey(MEMORY_KEY);

     if(!pcarsData.attach(QSharedMemory::ReadOnly))
     {
         return false;
     }

     return true;
}









