#include "pcars.h"

#define MEMORY_KEY "$pcars$"



Pcars::Pcars()
{
    m_sharedMemory.setNativeKey(MEMORY_KEY);
    m_sharedMemory.attach(QSharedMemory::ReadOnly);

    m_pcarsData = reinterpret_cast<MemoryMap_Pcars*> (m_sharedMemory.data());
}

bool Pcars::writeDataTo(gameDataStruct *gameData)
{
    if(!isRunning()) return false;

    ParticipantInfo *racerInfo = m_pcarsData->mParticipantInfo;

    gameData->racePosition = racerInfo->mRacePosition;

    gameData->gear          = (uint8_t) m_pcarsData->mGear;
    gameData->rpm           = m_pcarsData->mRpm;
    gameData->maxRpm        = m_pcarsData->mMaxRPM;
    gameData->speed         = (m_pcarsData->mSpeed * 3.6);
    gameData->fuelLevel     = (m_pcarsData->mFuelLevel * m_pcarsData->mFuelCapacity);
    gameData->fuelCapacity  = m_pcarsData->mFuelCapacity;

    gameData->tempOil                       = m_pcarsData->mOilTempCelsius;
    gameData->tempWater                     = m_pcarsData->mWaterTempCelsius;
    gameData->tempBrake[eTYRE_FRONT_LEFT]   = m_pcarsData->mBrakeTempCelsius[TYRE_FRONT_LEFT];
    gameData->tempBrake[eTYRE_FRONT_RIGHT]  = m_pcarsData->mBrakeTempCelsius[TYRE_FRONT_RIGHT];
    gameData->tempBrake[eTYRE_REAR_LEFT]    = m_pcarsData->mBrakeTempCelsius[TYRE_REAR_LEFT];
    gameData->tempBrake[eTYRE_REAR_RIGHT]   = m_pcarsData->mBrakeTempCelsius[TYRE_REAR_RIGHT];
    gameData->tempTyre[eTYRE_FRONT_LEFT]    = m_pcarsData->mTyreTemp[TYRE_FRONT_LEFT];
    gameData->tempTyre[eTYRE_FRONT_RIGHT]   = m_pcarsData->mTyreTemp[TYRE_FRONT_RIGHT];
    gameData->tempTyre[eTYRE_REAR_LEFT]     = m_pcarsData->mTyreTemp[TYRE_REAR_LEFT];
    gameData->tempTyre[eTYRE_REAR_RIGHT]    = m_pcarsData->mTyreTemp[TYRE_REAR_RIGHT];

    gameData->damageAero                            = m_pcarsData->mAeroDamage * 100;
    gameData->damageEngine                          = m_pcarsData->mEngineDamage * 100;
    gameData->damageBrake[eTYRE_FRONT_LEFT]         = m_pcarsData->mBrakeDamage[TYRE_FRONT_LEFT] * 100;
    gameData->damageBrake[eTYRE_FRONT_RIGHT]        = m_pcarsData->mBrakeDamage[TYRE_FRONT_RIGHT] * 100;
    gameData->damageBrake[eTYRE_REAR_LEFT]          = m_pcarsData->mBrakeDamage[TYRE_REAR_LEFT] * 100;
    gameData->damageBrake[eTYRE_REAR_RIGHT]         = m_pcarsData->mBrakeDamage[TYRE_REAR_RIGHT] * 100;
    gameData->damageSuspension[eTYRE_FRONT_LEFT]    = m_pcarsData->mSuspensionDamage[TYRE_FRONT_LEFT] * 100;
    gameData->damageSuspension[eTYRE_FRONT_RIGHT]   = m_pcarsData->mSuspensionDamage[TYRE_FRONT_RIGHT] * 100;
    gameData->damageSuspension[eTYRE_REAR_LEFT]     = m_pcarsData->mSuspensionDamage[TYRE_REAR_LEFT] * 100;
    gameData->damageSuspension[eTYRE_REAR_RIGHT]    = m_pcarsData->mSuspensionDamage[TYRE_REAR_RIGHT] * 100;
    gameData->damageTyre[eTYRE_FRONT_LEFT]          = m_pcarsData->mTyreWear[TYRE_FRONT_LEFT] * 100;
    gameData->damageTyre[eTYRE_FRONT_RIGHT]         = m_pcarsData->mTyreWear[TYRE_FRONT_RIGHT] * 100;
    gameData->damageTyre[eTYRE_REAR_LEFT]           = m_pcarsData->mTyreWear[TYRE_REAR_LEFT] * 100;
    gameData->damageTyre[eTYRE_REAR_RIGHT]          = m_pcarsData->mTyreWear[TYRE_REAR_RIGHT] * 100;

    gameData->timeBestLap           = m_pcarsData->mBestLapTime;
    gameData->timeLastLap           = m_pcarsData->mLastLapTime;
    gameData->timeCurrentSector1    = m_pcarsData->mCurrentSector1Time;
    gameData->timeCurrentSector2    = m_pcarsData->mCurrentSector2Time;
    gameData->timeCurrentSector3    = m_pcarsData->mCurrentSector3Time;
    gameData->timeFastestSector1    = m_pcarsData->mFastestSector1Time;
    gameData->timeFastestSector2    = m_pcarsData->mFastestSector2Time;
    gameData->timeFastestSector3    = m_pcarsData->mFastestSector3Time;
    gameData->timeSplitAhead        = m_pcarsData->mSplitTimeAhead;
    gameData->timeSplitBehind       = m_pcarsData->mSplitTimeBehind;

    return true;
}

bool Pcars::isRunning()
{
    if(!m_sharedMemory.isAttached())
    {
        m_sharedMemory.attach(QSharedMemory::ReadOnly);
    }

    return m_sharedMemory.isAttached();
}

























