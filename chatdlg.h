#ifndef CHATDLG_H
#define CHATDLG_H

#include <QWidget>
#include <Packdef.h>
//#include <qqmaindlg.h>
namespace Ui {
class ChatDlg;
}

class ChatDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDlg(QWidget *parent = nullptr);
    ~ChatDlg();
    void SetInfo(char *,int ,STRU_USER_INFO*);
    void AddMsg(char *);
signals:
    void SIG_ADDITEM(char*,int);
private slots:
    void on_pb_send_clicked();

private:
    Ui::ChatDlg *ui;
    int m_userid;
    STRU_USER_INFO* m_charUserInfo;
    char *m_UserItem;
};

#endif // CHATDLG_H
