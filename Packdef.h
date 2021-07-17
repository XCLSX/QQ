#ifndef _PACKDEF_H
#define _PACKDEF_H
#include <iostream>
#include <QMessageBox>
#include <qmytcpclient.h>
#include <QCryptographicHash>
#include <QByteArray>
#include <QTime>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QBitmap>
#include <string>
#include <QFile>
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

    DEF_PACK_UPDATESTATUS,                      //更新用户状态

    DEF_PACK_SENDMSG_RQ,                        //发送聊天信息请求

    DEF_PACK_OFFLINE_RQ,                        //下线请求

    DEF_PACK_UPLOAD_RQ,                         //上传文件请求
    DEF_PACK_UPLOAD_RS,
    DEF_PACK_FILEBLOCK_RQ,                      //发送文件块请求

    DEF_PACK_TEST,
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
#define MAX_MGS_SIZE        (2048)
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

        //文件信息
        typedef struct STRU_FILE_INFO
        {
            STRU_FILE_INFO()
            {
                fileMd5 = "";
                filePos = 0;
                fileSize = 0;
                filePath = "";
                fileName = "";
                pFile = NULL;
                bFLag = true;
            }
            QString fileMd5;
            int64_t filePos;
            int64_t fileSize;
            QString filePath;
            QString fileName;
            QFile * pFile;
            bool bFLag;

        }STRU_FILE_INFO;
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
typedef struct STRU_ADDFRIEND_RS
{
    STRU_ADDFRIEND_RS()
    {
        m_nType = DEF_PACK_ADDFRIEND_RS;
    }
    PackType m_nType;
    int m_userid;
    int m_frid;
}STRU_ADDFRIEND_RS;

//更新在线状态
typedef struct STRU_UPDATE_STATUS
{
    STRU_UPDATE_STATUS()
    {
        m_nType = DEF_PACK_UPDATESTATUS;
    }
    PackType m_nType;
    STRU_USER_INFO m_UserInfo;
}STRU_UPDATE_STATUS;

typedef struct STRU_TEST
{
    STRU_TEST()
    {
        m_nType = DEF_PACK_TEST;
    }
    PackType m_nType;
}STRU_TEST;

//发送信息请求
typedef struct STRU_SENDMSG_RQ
{
    STRU_SENDMSG_RQ()
    {
        m_nType = DEF_PACK_SENDMSG_RQ;
        m_userid = 0;
        m_Touserid = 0;
        memset(msg,0,sizeof(msg));
    }
    PackType m_nType;
    int m_userid;
    int m_Touserid;
    char msg[MAX_MGS_SIZE];
}STRU_SENDMSG_RQ;

typedef struct STRU_OFFLINE_RQ
{
    STRU_OFFLINE_RQ()
    {
        m_nType = DEF_PACK_OFFLINE_RQ;
        m_userid = 0;
    }
    PackType m_nType;
    int m_userid;
}STRU_OFFLINE_RQ;

//上传文件请求
typedef struct STRU_UPLOAD_RQ
{
    STRU_UPLOAD_RQ()
    {
        m_nType = DEF_PACK_UPLOAD_RQ;
        m_UserId = 0;
        m_friendId = 0;
        m_nFileSize = 0;
        memset( m_szFileMD5 , 0 , MAX_SIZE);
        memset(m_szFileName , 0 ,MAX_PATH);
    }
    PackType m_nType; //包类型
    int m_UserId; //用于查数据库, 获取用户名字, 拼接路径
    int m_friendId; //对方的id

    int64_t m_nFileSize; //文件大小, 用于文件传输结束
    char m_szFileMD5[MAX_SIZE];
    char m_szFileName[MAX_PATH]; //文件名, 用于存储文件

}STRU_UPLOAD_RQ;

//上传文件请求回复
typedef struct STRU_UPLOAD_RS
{
    STRU_UPLOAD_RS()
    {
        m_nType = DEF_PACK_UPLOAD_RS;
        m_UserId= 0 ;
        m_friendId = 0;
        memset( m_szFileMD5 , 0 , MAX_SIZE);
        m_nResult = 0;
    }
    PackType m_nType; //包类型
    int m_nResult;
    int m_UserId; //用于查数据库, 获取用户名字, 拼接路径
    int m_friendId; //对方的id
    char m_szFileMD5[MAX_SIZE];
}STRU_UPLOAD_RS;

//文件块请求
typedef struct STRU_FILEBLOCK_RQ
{
    STRU_FILEBLOCK_RQ()
    {
        m_nType = DEF_PACK_FILEBLOCK_RQ;
        m_nUserId = 0;
        m_friendId = 0;
        memset( m_szFileMD5 , 0 , MAX_SIZE);
        m_nBlockLen =0;
        memset(m_szFileContent, 0 , MAX_CONTENT_LEN);
    }
    PackType m_nType; //包类型
    int m_nUserId; //用户 ID
    int m_friendId; //对方的id
    char m_szFileMD5[MAX_SIZE]; // 文件块身份标识
    int m_nBlockLen; //文件写入大小
    char m_szFileContent[MAX_CONTENT_LEN];
}STRU_FILEBLOCK_RQ;
#endif
