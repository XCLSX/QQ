#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <Packdef.h>
#include <mutex>
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
public slots:
    void slot_SendFile(STRU_FILE_INFO *szbuf,int,int);
    void slot_pause();
    void slot_GetFIle(STRU_FILE_INFO*info,char*);

signals:
    void SIG_TASK_OVER(STRU_FILE_INFO*);
    void SIG_VALUE_CHANGE(int);
private:
    //mutex mx;
    bool isWork;
};

#endif // WORKER_H
