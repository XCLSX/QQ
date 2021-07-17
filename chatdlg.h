#ifndef CHATDLG_H
#define CHATDLG_H

#include <QWidget>
#include <Packdef.h>
#include <QFileDialog>
#include <QThread>
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
    void SendFile(char *);
signals:
    void SIG_ADDITEM(char*,int);
    void SIG_THREAD_WORK(char *,int,int);
private slots:
    void on_pb_send_clicked();

    void on_pb_sendFile_clicked();
private:
    Ui::ChatDlg *ui;
    int m_userid;
    STRU_USER_INFO* m_charUserInfo;
    char *m_UserItem;
    map<QString,STRU_FILE_INFO*> map_Md5ToFile;
    QThread myThread;
};

#endif // CHATDLG_H
