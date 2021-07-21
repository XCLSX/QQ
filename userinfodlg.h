#ifndef USERINFODLG_H
#define USERINFODLG_H

#include <QWidget>
#include <Packdef.h>
namespace Ui {
class UserInfoDlg;
}

class UserInfoDlg : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfoDlg(STRU_USER_INFO*,QWidget *parent = nullptr);
    ~UserInfoDlg();

private slots:
    void on_pb_commi_clicked();

    void on_pb_cancel_clicked();

    void on_pb_yingyong_clicked();

private:
    STRU_USER_INFO*info;
    QString name;
    QString iconid;

    Ui::UserInfoDlg *ui;
};

#endif // USERINFODLG_H
