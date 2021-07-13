#ifndef CKERNEL_H
#define CKERNEL_H
#include "ui_logindlg.h"
#include <QObject>
#include <logindlg.h>
#include <Packdef.h>
#include <qqmaindlg.h>
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
private slots:      //请求

private slots:      //回复
    void slot_DealRs(char *,int);
    void slot_RegisterRs(char *,int);
    void slot_LoginRs(char *,int);
    void slot_SearchFriendRs(char *,int);
    void slot_Fresh_FriListRs(char*,int);
    void slot_AddfriendRq(char *,int);


    void slot_Destroyapp();
public:
    LoginDlg *m_logindlg;
    QQMainDlg *m_maindlg;
    PFUN NetPack[DEF_PACK_COUNT];
    STRU_USER_INFO *m_userInfo;
};

#endif // CKERNEL_H
