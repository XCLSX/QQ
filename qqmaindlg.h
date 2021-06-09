#ifndef QQMAINDLG_H
#define QQMAINDLG_H

#include <QDialog>
#include <Packdef.h>

namespace Ui {
class QQMainDlg;
}

class QQMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QQMainDlg(QWidget *parent = nullptr);
    ~QQMainDlg();
    void SetInfo(STRU_USER_INFO& info);
private:
    Ui::QQMainDlg *ui;
};

#endif // QQMAINDLG_H
