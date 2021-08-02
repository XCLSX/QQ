#include "hotpointdlg.h"
#include "ui_hotpointdlg.h"

HotPointDlg::HotPointDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotPointDlg)
{
    ui->setupUi(this);
    m_layout = new QVBoxLayout;
    ui->wid_hotline->setLayout(m_layout);
    for(int i=0;i<50;i++)
        m_hotItemarr[i] = new HotPointItem;
}

HotPointDlg::~HotPointDlg()
{
    delete ui;
}

void HotPointDlg::InitInfo(char *szbuf)
{
    STRU_GETHOTPOINT_RS *rs = (STRU_GETHOTPOINT_RS*)szbuf;

    for(int i=0;i<50;i++)
    {
        m_hotItemarr[i]->SetInfo(i+1,QString(rs->m_hotres[i].sz_title),QString(rs->m_hotres[i].sz_url));
        m_layout->addWidget(m_hotItemarr[i]);
        m_hotItemarr[i]->setVisible(true);
    }
    this->show();
}
