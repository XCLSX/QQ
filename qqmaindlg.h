#ifndef QQMAINDLG_H
#define QQMAINDLG_H

#include <QDialog>

namespace Ui {
class QQMainDlg;
}

class QQMainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QQMainDlg(QWidget *parent = nullptr);
    ~QQMainDlg();

private:
    Ui::QQMainDlg *ui;
};

#endif // QQMAINDLG_H
