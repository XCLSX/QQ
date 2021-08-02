#ifndef QQMAINDLG_H
#define QQMAINDLG_H

#include <QDialog>
#include <Packdef.h>
#include <searchfrienddlg.h>
#include <QVBoxLayout>
#include <useritem.h>
#include <groupitem.h>
#include <addfrienditem.h>
#include <userinfodlg.h>
#include <creategroupdlg.h>
#include <QCloseEvent>
#include <hotpointdlg.h>
class CKernel;
namespace Ui {
class QQMainDlg;
}

class QQMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QQMainDlg(QWidget *parent = nullptr);
    ~QQMainDlg();
    SearchFriendDlg *GetSearchDLg();
    void FreshFriendList(char *);
    void AddUserItem(QWidget*item);
    void UpdateFriendStatus(char *);
    void SetInfo(STRU_USER_INFO* info);
    void UpdateMsg(char *);
    void closeEvent(QCloseEvent *);
    UserItem *GetFriendItem(int fid);
    void AcceptFile(char *);
    void GetFile(char *);
    void DelFriend(char *);
    void UpdateUserInfo(char *);
    void CreateGroupRs(char *);
    void AddGroupInfo(char *);
    void GetGroupMsg(char*);
    void AddFriend(char *);
    HotPointDlg *GetHotDlg();
public slots:


private slots:

    void slot_UpdateMsgLayout(UserItem*,char*);
    void on_pb_Search_clicked();

    void on_pb_icon_clicked();

    void on_pb_Cgroup_clicked();

    void on_pb_HotLine_clicked();

private:


private:
    Ui::QQMainDlg *ui;
    SearchFriendDlg *m_SearchDlg;
    CreateGroupDlg * m_CgroupDlg;
    HotPointDlg *m_hotDlg;
    STRU_USER_INFO* m_userInfo;
    //friend class CKernel;

    list<UserItem*> m_Friendls;
    list<UserItem*> m_Msgls;
    list<GroupItem*> m_GroupMsgls;
    list<GroupItem*> m_Groupls;
    list<AddFriendItem*> m_Addfrils;
    UserInfoDlg * m_AlterInfoDlg;

    QVBoxLayout *m_Frilayout;
    QVBoxLayout *m_Msglayout;
    QVBoxLayout *m_Grouplayout;

};

#endif // QQMAINDLG_H
