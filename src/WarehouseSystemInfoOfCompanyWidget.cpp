#include "WarehouseSystemInfoOfCompanyWidget.h"
#include "ui_WarehouseSystemInfoOfCompanyWidget.h"

WarehouseSystemInfoOfCompanyWidget::WarehouseSystemInfoOfCompanyWidget(QWidget *_parent) :
    QWidget(_parent),
    m_ui(new Ui::WarehouseSystemInfoOfCompanyWidget)
{
    m_ui->setupUi(this);

    prepareConnections();
    show();
}

WarehouseSystemInfoOfCompanyWidget::~WarehouseSystemInfoOfCompanyWidget()
{
    delete m_ui;
}

void WarehouseSystemInfoOfCompanyWidget::closeSlot()
{
    emit closeEvent();
}

void WarehouseSystemInfoOfCompanyWidget::prepareConnections()
{
    connect(m_ui->pbClose, SIGNAL(clicked()), this, SLOT(closeSlot()));
    connect(m_ui->pbClose, SIGNAL(clicked()), this, SLOT(close()));
}
