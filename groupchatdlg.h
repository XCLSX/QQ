#ifndef GROUPCHATDLG_H
#define GROUPCHATDLG_H

#include <QWidget>
#include <Packdef.h>
#include <QVBoxLayout>
#include <useritem.h>
//#include <groupitem.h>
namespace Ui {
class GroupChatDlg;
}

class GroupChatDlg : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChatDlg(char *item,int groupid,QWidget *parent = nullptr);
    ~GroupChatDlg();
    void setInfo(QString name,int m_groupid,list<STRU_USER_INFO*> ls);
    void AddMsg(int userid,QString msg);
    list<STRU_USER_INFO*>*GetLs();
private slots:
    void on_pb_send_clicked();
signals:
    void SIG_SENDMSG(char *,QString,int m_groupid);
private:
    char* m_item;
    int m_groupid;
    list<STRU_USER_INFO*> m_userls;
    Ui::GroupChatDlg *ui;
    QVBoxLayout *m_UserLayout;
    int m_userid;
};

#endif // GROUPCHATDLG_H
