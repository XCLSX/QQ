#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <Packdef.h>
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);
public slots:
    void dowork(char *szbuf,int,int);

signals:
    void SIG_TASK_OVER();
};

#endif // WORKER_H
