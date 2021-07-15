#ifndef QQMAINDLG_H
#define QQMAINDLG_H

#include <QDialog>
#include <Packdef.h>
#include <searchfrienddlg.h>
#include <QVBoxLayout>
#include <useritem.h>
#include <addfrienditem.h>
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
public slots:

    void slot_AddMsg(char *,int mode = 0);

private slots:


    void on_pb_Search_clicked();

    void on_pb_icon_clicked();

private:


private:
    Ui::QQMainDlg *ui;
    SearchFriendDlg *m_SearchDlg;
    STRU_USER_INFO* m_userInfo;
    //friend class CKernel;

    list<UserItem*> m_Friendls;
    list<UserItem*> m_Msgls;
    list<AddFriendItem*> m_Addfrils;

    QVBoxLayout *m_Frilayout;
    QVBoxLayout *m_Msglayout;

};

#endif // QQMAINDLG_H
