#ifndef HOTPOINTITEM_H
#define HOTPOINTITEM_H

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QUrl>


namespace Ui {
class HotPointItem;
}

class HotPointItem : public QWidget
{
    Q_OBJECT

public:
    explicit HotPointItem(QWidget *parent = nullptr);
    ~HotPointItem();
    void SetInfo(int,QString,QString);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::HotPointItem *ui;
    QString m_title;
    QString m_url;
};

#endif // HOTPOINTITEM_H
