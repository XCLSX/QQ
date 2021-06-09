#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <Packdef.h>
namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = nullptr);
    ~LoginDlg();
    Ui::LoginDlg * GetUi() const;
signals:
    void SIG_RegisterRq(char *,int);

    void SIG_LoginRq(char *,int);
private slots:
    void on_pb_register_clicked();

    void on_pb_login_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
