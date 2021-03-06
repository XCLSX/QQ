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
    void SIG_UpdateSearchfriendList(char *);
private slots:      //请求

private slots:      //回复
    void slot_DealRs(char *,int);
    void slot_RegisterRs(char *,int);
    void slot_LoginRs(char *,int);
    void slot_SearchFriendRs(char *,int);
    void slot_Fresh_FriListRs(char*,int);
    void slot_AddfriendRq(char *,int);
    void slot_UpdateFriendStatus(char *,int);
    void slot_GetMsg(char *,int);
    void slot_UploadRs(char *,int);
    void slot_Destroyapp();
    void slot_AcceptFile(char *,int);
    void slot_GetFile(char *,int);
    void slot_DelFriend(char *,int);
    void slot_UpdateUserInfo(char *,int);
    void slot_CreateGroupRs(char* ,int);
    void slot_GetGroupInfo(char *,int);
    void slot_GetGroupMsg(char *,int);
    void slot_GetHotLine(char *,int);
public:
    LoginDlg *m_logindlg;
    QQMainDlg *m_maindlg;
    PFUN NetPack[DEF_PACK_COUNT];
    STRU_USER_INFO *m_userInfo;
    QVBoxLayout *m_ChatLayout;
};

#endif // CKERNEL_H
