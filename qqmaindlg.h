#ifndef QQMAINDLG_H
#define QQMAINDLG_H

#include <QDialog>
#include <Packdef.h>
#include <searchfrienddlg.h>
#include <QVBoxLayout>
#include <useritem.h>
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
    void AddUserItem(QWidget*item);

private slots:
    void SetInfo(STRU_USER_INFO* info);


    void on_pb_Search_clicked();

    void on_pb_icon_clicked();

private:


private:
    Ui::QQMainDlg *ui;
    SearchFriendDlg *m_SearchDlg;
    friend class CKernel;
    int m_userid;
    int icon_id;
    char szName[MAX_SIZE];
    char szFelling[MAX_SIZE];
    QVBoxLayout *m_layout;
};

#endif // QQMAINDLG_H
