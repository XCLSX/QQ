
#ifndef _PACKDEF_H
#define _PACKDEF_H
#include <QMessageBox>
#include <QDebug>
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

    DEF_PACK_CREATEROOM_RQ,                     //创建房间请求
    DEF_PACK_CREATEROOM_RS,

    DEF_PACK_JOINROOM_RQ ,                      //加入房间请求
    DEF_PACK_JOINROOM_RS,

    DEF_PACK_SEARCH_ROOM_RQ,                    //查找房间请求
    DEF_PACK_SEARCH_ROOM_RS,

    DEF_PACK_ROOM_MEMBER_RQ,                    //请求房间成员
    DEF_PACK_ROOM_MEMBER_RS,

    DEF_PACK_ASKROOM_RQ,                        //刷新房间列表请求
    DEF_PACK_ASKROOM_RS,

    DEF_PACK_CHECKOFFLINE_RQ,                   //查询离线数据请求A
    DEF_PACK_CHECKOFFLINE_RS,

    DEF_PACK_LEAVEROOM_RQ ,                     //离开房间请求
    DEF_PACK_LEAVEROOM_RS ,

    DEF_PACK_SEARCH_FRIEND_RQ,                  //查询好友请求
    DEF_PACK_SEARCH_FRIEND_RS,

    DEF_PACK_ADD_FRIEND_RQ,                     //添加好友请求
    DEF_PACK_ADD_FRIEND_RS,

    DEF_ALTER_USERINFO_RQ,                      //修改用户信息请求
    DEF_ALTER_USERINFO_RS,

    DEF_PACK_FRIEND_INFO,

    DEF_PACK_CHAT_RQ,                           //聊天请求
    DEF_PACK_CHAT_RS,

    DEF_PACK_OFFLINRE_RQ,                       //下线请求
    DEF_PACK_OFFLINRE_RS,
}Net_PACK;


//注册请求结果
#define userid_is_exist      0
#define register_sucess      1

//登录请求结果
#define userid_no_exist      0
#define password_error       1
#define login_sucess         2
#define user_online          3

//创建房间结果
#define room_is_exist        0
#define create_success       1

//加入房间结果
#define room_no_exist        0
#define join_success         1

//上传请求结果
#define file_is_exist        0
#define file_uploaded        1
#define file_uploadrq_sucess 2
#define file_upload_refuse   3

//上传回复结果
#define fileblock_failed     0
#define fileblock_success    1

//下载请求结果
#define file_downrq_failed   0
#define file_downrq_success  1

#define _downloadfileblock_fail  0
#define _downloadfileblock_success	1

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
                memset(sz_userName,0,MAX_SIZE);
                memset(sz_felling,0,MAX_SIZE);
            }
            int m_user_id;
            int m_icon_id;
            char sz_userName[MAX_SIZE];
            int m_status;
            char sz_felling[MAX_SIZE];
        }STRU_USER_INFO;

//登录请求
typedef struct STRU_LOGIN_RQ
{
    STRU_LOGIN_RQ()
    {
        m_nType = DEF_PACK_LOGIN_RQ;
        memset(m_szAccount,0,MAX_SIZE);
        memset(m_szPassword,0,MAX_SIZE);
    }

    PackType m_nType;   //包类型
    char     m_szAccount[MAX_SIZE] ; //用户ID
    char     m_szPassword[MAX_SIZE];  //密码
} STRU_LOGIN_RQ;


//登录回复
typedef struct STRU_LOGIN_RS
{
    STRU_LOGIN_RS()
    {
        m_nType= DEF_PACK_LOGIN_RS;
        m_lResult = 0;
    }
    PackType m_nType;   //包类型
    int  m_lResult ; //注册结果
    STRU_USER_INFO m_userInfo;


} STRU_LOGIN_RS;


//注册请求
typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ()
    {
        m_nType = DEF_PACK_REGISTER_RQ;
        memset(m_szAccount,0,MAX_SIZE);
        memset(m_szUserName,0,MAX_SIZE);
        memset(m_szPassword,0,MAX_SIZE);
    }

    PackType m_nType;   //包类型
    char     m_szAccount[MAX_SIZE] ; //用户名
    char     m_szUserName[MAX_SIZE];
    char     m_szPassword[MAX_SIZE];  //密码

} STRU_REGISTER_RQ;

//注册回复
typedef struct STRU_REGISTER_RS
{
    STRU_REGISTER_RS()
    {
        m_nType= DEF_PACK_REGISTER_RS;
        m_lResult = 0;
    }
    PackType m_nType;   //包类型
    int  m_lResult ; //注册结果

} STRU_REGISTER_RS;

//查找好友请求
typedef struct STRU_SEARCH_FRIEND_RQ
{
    STRU_SEARCH_FRIEND_RQ()
    {
        m_nType = DEF_PACK_SEARCH_FRIEND_RQ;
    }
    PackType m_nType;
    char m_szbuf[MAX_SIZE];

}STRU_SEARCH_FRIEND_RQ;

//查找好友回复
typedef struct STRU_SEARCH_FRIEND_RS
{
    STRU_SEARCH_FRIEND_RS()
    {
        m_nType = DEF_PACK_SEARCH_FRIEND_RQ;
        m_lResult = 0;
        memset(m_userInfoArr,0,sizeof(m_userInfoArr));
    }
    PackType m_nType;
    int m_lResult;
    STRU_USER_INFO m_userInfoArr[10];
}STRU_SEARCH_FRIEND_RS;



////创建房间请求
//typedef struct STRU_CREATEROOM_RQ
//{
//    STRU_CREATEROOM_RQ()
//    {
//        m_nType = DEF_PACK_CREATEROOM_RQ;
//        m_UserID = 0;
//        m_RoomID = 0;
//    }

//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_RoomID;

//} STRU_CREATEROOM_RQ;

////创建房间回复
//typedef struct STRU_CREATEROOM_RS
//{
//    STRU_CREATEROOM_RS()
//    {
//        m_nType= DEF_PACK_CREATEROOM_RS;
//        m_lResult = 0;
//        m_RoomId = 0;
//        m_AudioPort = 0;
//        memset( m_AudioIP, 0, 20);
//    }
//    PackType m_nType;   //包类型
//    int  m_lResult ;    //注册结果
//    int  m_RoomId;
//    int  m_AudioPort;
//    char m_AudioIP[20];


//} STRU_CREATEROOM_RS;

////加入房间请求
//typedef struct STRU_JOINROOM_RQ
//{
//    STRU_JOINROOM_RQ()
//    {
//        m_nType = DEF_PACK_JOINROOM_RQ;
//        m_UserID = 0;
//        m_RoomID = 0;
//    }

//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_RoomID;

//} STRU_JOINROOM_RQ;

////加入房间回复
//typedef struct STRU_JOINROOM_RS
//{
//    STRU_JOINROOM_RS()
//    {
//        m_nType= DEF_PACK_JOINROOM_RS;
//        m_lResult = 0;
//        m_RoomId = 0;
//        m_AudioPort = 0;
//        memset(m_AudioIP,0,20);
//    }
//    PackType m_nType;   //包类型
//    int  m_lResult ;    //注册结果
//    int  m_RoomId;
//    int m_AudioPort;
//    char m_AudioIP[20];

//} STRU_JOINROOM_RS;

////房间成员请求
//typedef struct STRU_ROOM_MEMBER_RQ
//{
//    STRU_ROOM_MEMBER_RQ()
//    {
//        m_nType= DEF_PACK_ROOM_MEMBER;
//        m_AudioPort = 0;
//        m_UserID = 0;
//        memset(m_szUser,0,MAX_SIZE);
//        memset(m_RtmpUrl,0,MAX_SIZE);
//        memset(m_AudioIP,0,MAX_SIZE);
//    }
//    PackType m_nType;   //包类型
//    int m_UserID;
//    int m_AudioPort;
//    char m_szUser[MAX_SIZE];
//    char m_RtmpUrl[MAX_SIZE];
//    char m_AudioIP[20];

//} STRU_ROOM_MEMBER_RQ;

////离开房间请求
//typedef struct STRU_LEAVEROOM_RQ
//{
//    STRU_LEAVEROOM_RQ()
//    {
//        m_nType = DEF_PACK_LEAVEROOM_RQ;
//        m_nUserId = 0;
//        m_RoomId = 0;
//    }
//    PackType   m_nType;   //包类型
//    int    m_nUserId; //用户ID
//    int    m_RoomId;
//} STRU_LEAVEROOM_RQ;

////离开房间回复
//typedef struct STRU_LEAVEROOM_RS
//{
//    STRU_LEAVEROOM_RS()
//    {
//        m_nType = DEF_PACK_LEAVEROOM_RS;
//        m_UserID = 0;
//        memset(szUserName,0,MAX_SIZE);
//    }
//    PackType   m_nType;   //包类型
//    int m_UserID;
//    char szUserName[MAX_SIZE];
//} STRU_LEAVEROOM_RS;


#endif







