#ifndef PCARSWORKER_H
#define PCARSWORKER_H

#include <QObject>
#include <QSharedMemory>

#include "../clientData.h"
#include "pcarssharedmemory.h"

class PcarsWorker : public QObject
{
    Q_OBJECT

private:
    bool loop;

    QThread *parentThread;

    QSharedMemory *sharedMemory;

    struct_client *clientData;
    MemoryMap_Pcars *pcarsData;

    void convert();
public:
    PcarsWorker(QThread *parentThread, struct_client *clientData);
    void exitLoop();
    static bool isGameRunning();




public slots:
    void process();

signals:
    void finished();
    void error(QString error);
};

#endif // PCARSWORKER_H
