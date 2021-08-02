#include "hotpointitem.h"
#include "ui_hotpointitem.h"

HotPointItem::HotPointItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotPointItem)
{
    ui->setupUi(this);

}

HotPointItem::~HotPointItem()
{
    delete ui;
}

void HotPointItem::SetInfo(int num, QString title, QString url)
{
    m_title = title;
    m_url = url;
    ui->lb_title->setText(title);
    char str[4] = {0};
    itoa(num,str,10);
    ui->lb_num->setText(QString(str));
}

void HotPointItem::mousePressEvent(QMouseEvent *event)
{
  if(event->button()== Qt::LeftButton)
  {
    QDesktopServices::openUrl(QUrl(m_url));
  }

}
