#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <Packdef.h>
#include <QPaintEvent>

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
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pb_register_clicked();

    void on_pb_login_clicked();

private:
    Ui::LoginDlg *ui;

};

#endif // LOGINDLG_H
