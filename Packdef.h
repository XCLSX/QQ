#ifndef _PACKDEF_H
#define _PACKDEF_H

#include <QMessageBox>
#include <qmytcpclient.h>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QBitmap>
#include <string>
#include <map>
using namespace std;


#define BOOL bool
#define DEF_PACK_BASE  (10000)

typedef enum Net_PACK
{
    DEF_PACK_REGISTER_RQ = 10000,               //注册请求
    DEF_PACK_REGISTER_RS,

    DEF_PACK_LOGIN_RQ,                          //登录请求
    DEF_PACK_LOGIN_RS,

    DEF_PACK_FRIENDLIST_FRESH_RS,               //刷新好友回复

    DEF_PACK_SEARCHFRIEND_RQ,                   //查找好友请求
    DEF_PACK_SEARCHFRIEND_RS,

    DEF_PACK_ADDFRIEND_RQ,                      //添加好友请求
    DEF_PACK_ADDFRIEND_RS,

}Net_PACK;


//注册请求结果
#define userid_is_exist      0
#define register_sucess      1

//登录请求结果
#define userid_no_exist      0
#define password_error       1
#define login_sucess         2
#define user_online          3



#define DEF_PACK_COUNT (100)

#define MAX_PATH            (280 )
#define MAX_SIZE            (60  )
#define DEF_HOBBY_COUNT     (8  )
#define MAX_CONTENT_LEN     (4096 )


/////////////////////网络//////////////////////////////////////


#define DEF_MAX_BUF	  1024
#define DEF_BUFF_SIZE	  4096


typedef int PackType;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //用户信息
        typedef struct STRU_USER_INFO
        {
            STRU_USER_INFO()
            {
                m_user_id = 0;
                m_icon_id = 0;
                memset(m_userName,0,MAX_SIZE);
                memset(sz_feeling,0,MAX_SIZE);
                memset(m_userAccount,0,MAX_SIZE);
            }
            int m_user_id;
            char m_userAccount[MAX_SIZE];
            char m_userName[MAX_SIZE];
            int m_icon_id;
            int m_status;
            char sz_feeling[MAX_SIZE];
        }STRU_USER_INFO;

//注册
typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ()
    {
        m_nType = DEF_PACK_REGISTER_RQ;
        memset(m_szAccount,0,MAX_SIZE);
        memset(m_szName,0,MAX_SIZE);
        memset(m_szPwd,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szAccount[MAX_SIZE];
    char m_szName[MAX_SIZE];
    char m_szPwd[MAX_SIZE];
}STRU_REGISTER_RQ;
typedef struct STRU_REGISTER_RS
{
    STRU_REGISTER_RS()
    {
        m_nType = DEF_PACK_REGISTER_RS;
        m_lResult = 0;
    }
    PackType m_nType;
    int m_lResult;
}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
    STRU_LOGIN_RQ()
    {
        m_nType = DEF_PACK_LOGIN_RQ;
        memset(m_szAccount,0,MAX_SIZE);
        memset(m_szPwd,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szAccount[MAX_SIZE];
    char m_szPwd[MAX_SIZE];
}STRU_LOGIN_RQ;
typedef struct STRU_LOGIN_RS
{
    STRU_LOGIN_RS()
    {
        m_Type = DEF_PACK_LOGIN_RS;
        m_lResult = 0;
    }
    PackType m_Type;
    int m_lResult;
    STRU_USER_INFO m_userInfo;
}STRU_LOGIN_RS;

//获取好友列表
typedef struct STRU_GetFriList_Rs
{
    STRU_GetFriList_Rs()
    {
        m_nType = DEF_PACK_FRIENDLIST_FRESH_RS;
    }
    PackType m_nType;
    STRU_USER_INFO m_FriInfo[100];
}STRU_GetFriList_Rs;

//查找好友
typedef struct STRU_SEARCHFRIEND_RQ
{
    STRU_SEARCHFRIEND_RQ()
    {
        m_nType = DEF_PACK_SEARCHFRIEND_RQ;
        memset(m_szBuf,0,MAX_SIZE);
    }
    PackType m_nType;
    char m_szBuf[MAX_SIZE];
}STRU_SEARCHFRIEND_RQ;

typedef struct STRU_SEARCHFRIEND_RS
{
    STRU_SEARCHFRIEND_RS()
    {
        m_nType = DEF_PACK_SEARCHFRIEND_RS;
        memset(m_userid,0,MAX_SIZE);

    }
    PackType m_nType;
    STRU_USER_INFO m_userInfoArr[MAX_SIZE];
    int m_userid[MAX_SIZE];
}STRU_SEARCHFRIEND_RS;

//添加好友
typedef struct STRU_ADDFRIEND_RQ
{
    STRU_ADDFRIEND_RQ()
    {
        m_nType = DEF_PACK_ADDFRIEND_RQ;
        m_frid = 0;
    }
    PackType m_nType;
    int m_frid;
    STRU_USER_INFO m_UserInfo;
}STRU_ADDFRIEND_RQ;


#endif







