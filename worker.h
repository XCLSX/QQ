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
    void slot_dowork(STRU_FILE_INFO *szbuf,int,int);

signals:
    void SIG_TASK_OVER(STRU_FILE_INFO*);
    void SIG_VALUE_CHANGE(int);
private:
    mutex mx;
};

#endif // WORKER_H
