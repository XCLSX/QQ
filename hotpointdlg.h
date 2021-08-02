#ifndef HOTPOINTDLG_H
#define HOTPOINTDLG_H

#include <QWidget>
#include <hotpointitem.h>
#include <QVBoxLayout>
#include <Packdef.h>
namespace Ui {
class HotPointDlg;
}

class HotPointDlg : public QWidget
{
    Q_OBJECT

public:
    explicit HotPointDlg(QWidget *parent = nullptr);
    ~HotPointDlg();
    void InitInfo(char *);
private:
    Ui::HotPointDlg *ui;
    QVBoxLayout *m_layout;
    HotPointItem *m_hotItemarr[50];
};

#endif // HOTPOINTDLG_H
