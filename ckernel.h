#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include <logindlg.h>
#include <qmytcpclient.h>
#include <Packdef.h>
class CKernel;
typedef void (CKernel::*PFUN)(char *,int);


class CKernel : public QObject
{
    Q_OBJECT
public:
    static CKernel *GetInstance();
private:
    explicit CKernel(QObject *parent = nullptr);
    CKernel(const CKernel &)
    {

    }
    ~CKernel()
    {

    }
public:

    void InitObject();
    void MyConnect();
    void SetNetPack();
signals:

private slots:
    void slot_RegisterRq(char *,int);

    void slot_LoginRq(char *,int);

private slots:
    void slot_DealRs(char *,int);
    void slot_RegisterRs(char *,int);
    void slot_LoginRs(char *,int);

public:
    LoginDlg *m_logindlg;
    QMyTcpClient *m_tcp;
    PFUN NetPack[DEF_PACK_COUNT];
};

#endif // CKERNEL_H
