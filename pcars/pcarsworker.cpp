#include "pcarsworker.h"
#include <QDebug>
#include <QThread>


#define MEMORY_KEY "$pcars$"

PcarsWorker::PcarsWorker(QThread *parentThread, clientDataStruct *data)
{
    this->parentThread = parentThread;
    this->clientData = data;
    loop = true;


    sharedMemory = new QSharedMemory();

    sharedMemory->setNativeKey(MEMORY_KEY);
    sharedMemory->attach(QSharedMemory::ReadOnly);

    pcarsData = reinterpret_cast<MemoryMap_Pcars*> (sharedMemory->data());
}




void PcarsWorker::exitLoop()
{
    loop = false;
}




bool PcarsWorker::isGameRunning()
{
    QSharedMemory pcarsData;
    pcarsData.setNativeKey(MEMORY_KEY);

     if(!pcarsData.attach(QSharedMemory::ReadOnly))
     {
         return false;
     }

     return true;
}




void PcarsWorker::process()
{

    while(loop == true)
    {
        convert();
        parentThread->msleep(100);
    }

    qDebug() << "QObject: I'm finishing!";

    emit finished();
}



void PcarsWorker::convert()
{
    ParticipantInfo *racerInfo = pcarsData->mParticipantInfo;

    clientData->racePosition = racerInfo->mRacePosition;

    clientData->gear = (uint8_t) pcarsData->mGear;
    clientData->rpm = pcarsData->mRpm;
    clientData->maxRpm = pcarsData->mMaxRPM;
    clientData->speed = (pcarsData->mSpeed * 3.6);
    clientData->fuelLevel = (pcarsData->mFuelLevel * pcarsData->mFuelCapacity);
    clientData->fuelCapacity = pcarsData->mFuelCapacity;

    clientData->tempOil = pcarsData->mOilTempCelsius;
    clientData->tempWater = pcarsData->mWaterTempCelsius;
    clientData->tempBrake[eTYRE_FRONT_LEFT] = pcarsData->mBrakeTempCelsius[TYRE_FRONT_LEFT];
    clientData->tempBrake[eTYRE_FRONT_RIGHT] = pcarsData->mBrakeTempCelsius[TYRE_FRONT_RIGHT];
    clientData->tempBrake[eTYRE_REAR_LEFT] = pcarsData->mBrakeTempCelsius[TYRE_REAR_LEFT];
    clientData->tempBrake[eTYRE_REAR_RIGHT] = pcarsData->mBrakeTempCelsius[TYRE_REAR_RIGHT];
    clientData->tempTyre[eTYRE_FRONT_LEFT] = pcarsData->mTyreTemp[TYRE_FRONT_LEFT];
    clientData->tempTyre[eTYRE_FRONT_RIGHT] = pcarsData->mTyreTemp[TYRE_FRONT_RIGHT];
    clientData->tempTyre[eTYRE_REAR_LEFT] = pcarsData->mTyreTemp[TYRE_REAR_LEFT];
    clientData->tempTyre[eTYRE_REAR_RIGHT] = pcarsData->mTyreTemp[TYRE_REAR_RIGHT];

    clientData->damageAero = pcarsData->mAeroDamage * 100;
    clientData->damageEngine = pcarsData->mEngineDamage * 100;
    clientData->damageBrake[eTYRE_FRONT_LEFT] = pcarsData->mBrakeDamage[TYRE_FRONT_LEFT] * 100;
    clientData->damageBrake[eTYRE_FRONT_RIGHT] = pcarsData->mBrakeDamage[TYRE_FRONT_RIGHT] * 100;
    clientData->damageBrake[eTYRE_REAR_LEFT] = pcarsData->mBrakeDamage[TYRE_REAR_LEFT] * 100;
    clientData->damageBrake[eTYRE_REAR_RIGHT] = pcarsData->mBrakeDamage[TYRE_REAR_RIGHT] * 100;
    clientData->damageSuspension[eTYRE_FRONT_LEFT] = pcarsData->mSuspensionDamage[TYRE_FRONT_LEFT] * 100;
    clientData->damageSuspension[eTYRE_FRONT_RIGHT] = pcarsData->mSuspensionDamage[TYRE_FRONT_RIGHT] * 100;
    clientData->damageSuspension[eTYRE_REAR_LEFT] = pcarsData->mSuspensionDamage[TYRE_REAR_LEFT] * 100;
    clientData->damageSuspension[eTYRE_REAR_RIGHT] = pcarsData->mSuspensionDamage[TYRE_REAR_RIGHT] * 100;
    clientData->damageTyre[eTYRE_FRONT_LEFT] = pcarsData->mTyreWear[TYRE_FRONT_LEFT] * 100;
    clientData->damageTyre[eTYRE_FRONT_RIGHT] = pcarsData->mTyreWear[TYRE_FRONT_RIGHT] * 100;
    clientData->damageTyre[eTYRE_REAR_LEFT] = pcarsData->mTyreWear[TYRE_REAR_LEFT] * 100;
    clientData->damageTyre[eTYRE_REAR_RIGHT] = pcarsData->mTyreWear[TYRE_REAR_RIGHT] * 100;

    clientData->timeBestLap = pcarsData->mBestLapTime;
    clientData->timeLastLap = pcarsData->mLastLapTime;
    clientData->timeCurrentSector1 = pcarsData->mCurrentSector1Time;
    clientData->timeCurrentSector2 = pcarsData->mCurrentSector2Time;
    clientData->timeCurrentSector3 = pcarsData->mCurrentSector3Time;
    clientData->timeFastestSector1 = pcarsData->mFastestSector1Time;
    clientData->timeFastestSector2 = pcarsData->mFastestSector2Time;
    clientData->timeFastestSector3 = pcarsData->mFastestSector3Time;
    clientData->timeSplitAhead = pcarsData->mSplitTimeAhead;
    clientData->timeSplitBehind = pcarsData->mSplitTimeBehind;

}
