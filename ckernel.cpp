#include "ckernel.h"

CKernel *CKernel::GetInstance()
{
    static CKernel ck ;
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
    m_logindlg->show();
}

void CKernel::MyConnect()
{
    connect(m_tcp,SIGNAL(SIG_ReadyData(char*,int)),this,SLOT(slot_DealRs(char*,int)));
    connect(m_logindlg,SIGNAL(SIG_RegisterRq(char*,int)),this,SLOT(slot_RegisterRq(char*,int)));
    connect(m_logindlg,SIGNAL(SIG_LoginRq(char*,int)),this,SLOT(slot_LoginRq(char*,int)));

}

void CKernel::SetNetPack()
{
    NetPack[DEF_PACK_REGISTER_RS - DEF_PACK_BASE] = slot_RegisterRs;
    NetPack[DEF_PACK_LOGIN_RS - DEF_PACK_BASE] = slot_LoginRs;
}
////发出请求包
//注册请求
void CKernel::slot_RegisterRq(char *szbuf, int nlen)
{
    qDebug()<<__func__;
    m_tcp->SendData(szbuf,nlen);
}

void CKernel::slot_LoginRq(char *szbuf, int nlen)
{
    qDebug()<<__func__;
    m_tcp->SendData(szbuf,nlen);
}

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
    qDebug()<<__func__;
}
//登录回复
void CKernel::slot_LoginRs(char *szbuf, int nlen)
{
    qDebug()<<__func__;

}
