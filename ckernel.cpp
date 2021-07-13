#include "ckernel.h"
QMyTcpClient *m_tcp;

CKernel *CKernel::GetInstance()
{
    static CKernel ck;
    return &ck;
}

CKernel::CKernel(QObject *parent) : QObject(parent)
{
    InitObject();
    MyConnect();
    SetNetPack();

}

void CKernel::InitObject()
{
    m_tcp = new QMyTcpClient;
    m_tcp->setIpAndPort();
    m_logindlg = new LoginDlg;
    m_maindlg = new QQMainDlg;
    m_logindlg->show();
}

void CKernel::MyConnect()
{
    connect(m_tcp,SIGNAL(SIG_ReadyData(char*,int)),this,SLOT(slot_DealRs(char*,int)));

    connect(m_maindlg->m_SearchDlg,SIGNAL(SIG_Search(char*,int)),this,SLOT(slot_SearchFriendRq(char*,int)));


}

void CKernel::SetNetPack()
{
    NetPack[DEF_PACK_REGISTER_RS - DEF_PACK_BASE] = slot_RegisterRs;
    NetPack[DEF_PACK_LOGIN_RS - DEF_PACK_BASE] = slot_LoginRs;
    NetPack[DEF_PACK_SEARCHFRIEND_RS - DEF_PACK_BASE] = slot_SearchFriendRs;
    NetPack[DEF_PACK_FRIENDLIST_FRESH_RS - DEF_PACK_BASE] = slot_Fresh_FriListRs;


}
////发出请求包
//注册请求




////处理回复包
void CKernel::slot_DealRs(char *szbuf, int nlen)
{
    qDebug()<<__func__;
    PackType type = *(PackType*)szbuf;
    if(type>=DEF_PACK_BASE&&type<=DEF_PACK_BASE + DEF_PACK_COUNT)
    {
        PFUN fun = NetPack[type - DEF_PACK_BASE];
        if(fun)
        {
            (this->*fun)(szbuf,nlen);
        }
    }
}
//注册回复
void CKernel::slot_RegisterRs(char *szbuf, int nlen)
{
//    userid_is_exist      0
//    register_sucess      1
    qDebug()<<__func__;
    STRU_REGISTER_RS * rs = (STRU_REGISTER_RS*)szbuf;
    switch (rs->m_lResult) {
    case userid_is_exist:
        QMessageBox::about(m_logindlg,"提示","账号已存在");
        break;
    case register_sucess:
        QMessageBox::about(m_logindlg,"提示","注册成功");
        m_logindlg->GetUi()->tb_loginDlg->setCurrentIndex(0);
        break;
    default:
        break;
    }
}
//登录回复
void CKernel::slot_LoginRs(char *szbuf, int nlen)
{
//    userid_no_exist
//    password_error
//    login_sucess
//    user_online
    qDebug()<<__func__;
    STRU_LOGIN_RS *rs = (STRU_LOGIN_RS*)szbuf;
    switch (rs->m_lResult) {
    case userid_no_exist:
        QMessageBox::about(m_logindlg,"错误","用户不存在");
        break;
    case password_error:
        QMessageBox::about(m_logindlg,"错误","密码不正确");
        break;
    case login_sucess:
    {
        m_logindlg->hide();
        m_maindlg->SetInfo(&rs->m_userInfo);
        m_maindlg->show();
        break;
    }
    default:
        break;
    }

}

void CKernel::slot_SearchFriendRs(char *szbuf, int nlen)
{

    STRU_SEARCHFRIEND_RS *rs = (STRU_SEARCHFRIEND_RS*) szbuf;
    int i=0;
    SearchFriendDlg *dlg = m_maindlg->GetSearchDLg();
    SearchFriendItem *item = new SearchFriendItem;
    while(rs->m_userInfoArr[i].m_user_id!=0)
    {
        item->InitInfo(&rs->m_userInfoArr[i]);
        dlg->AddFriWidget(item);
        i++;
    }

}

void CKernel::slot_Fresh_FriListRs(char *szbuf, int len)
{
    UserItem *item;
   // STRU_USER_INFO info;
    m_maindlg->AddUserItem(item);
}
