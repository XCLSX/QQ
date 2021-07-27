#ifndef CHATDLG_H
#define CHATDLG_H

#include <QWidget>
#include <Packdef.h>
#include <QFileDialog>
#include <QThread>
#include <QVBoxLayout>
#include <fileitem.h>
#include <mutex>
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
    void AcceptFile(char *);
    void GetFile(char *);
signals:
    void SIG_ADDITEM(char*,int,QString str);
    void SIG_THREAD_WORK(STRU_FILE_INFO *,int,int);
    void SIG_VALCHANGE(int);
    void SIG_WORK_GETFILE(STRU_FILE_INFO*,char *);
private slots:
    void on_pb_send_clicked();

    void on_pb_sendFile_clicked();
    void on_pushButton_clicked();
    void slot_FileSendSuss(STRU_FILE_INFO*info);
    void on_pushButton_2_clicked();

private:
    Ui::ChatDlg *ui;
    list<FileItem*> m_filels;
    int m_userid;
    STRU_USER_INFO* m_charUserInfo;
    char *m_UserItem;
    map<QString,STRU_FILE_INFO*> map_Md5ToFile;
    map<QString,QThread*> map_Md5Tothread;
    QVBoxLayout *m_layout;
    int fileTask_num;
    mutex mtx;
};

#endif // CHATDLG_H
