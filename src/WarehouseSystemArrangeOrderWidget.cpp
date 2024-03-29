#include "WarehouseSystemArrangeOrderWidget.h"
#include "ui_WarehouseSystemArrangeOrderWidget.h"

#include "WarehouseSystemOrder.h"
#include "WarehouseSystemDataManager.h"
#include "WarehouseSystemAddCustomerDialog.h"

WarehouseSystemArrangeOrderWidget::WarehouseSystemArrangeOrderWidget(QWidget *_parent) :
    QWidget(_parent),
    m_ui(new Ui::WarehouseSystemArrangeOrderWidget),
    m_dataManager(new WarehouseSystemDataManager),
    m_order(new WarehouseSystemOrder()),
    m_addCustomerDialog(nullptr)
{
    m_ui->setupUi(this);

    prepareConnections();
    prepareUi();
}

WarehouseSystemArrangeOrderWidget::~WarehouseSystemArrangeOrderWidget()
{
    delete m_ui;
    delete m_dataManager;
    delete m_order;
}
void WarehouseSystemArrangeOrderWidget::prepareConnections()
{
    connect(m_ui->cbProducts, SIGNAL(currentIndexChanged(int)), this, SLOT(changedProductSlot()));
    connect(m_ui->pbAddProduct, SIGNAL(clicked()), this, SLOT(addProductSlot()));
    connect(m_ui->sbProductsCount, SIGNAL(valueChanged(int)), this, SLOT(productsCountChangeSlot()));
    connect(m_ui->cbCustomers, SIGNAL(currentIndexChanged(int)), this, SLOT(changedCustomerSlot()));
    connect(m_ui->pbAddNewCustomer, SIGNAL(clicked()), this, SLOT(addCustomerDialogSlot()));

    connect(m_ui->pbClose, SIGNAL(clicked()), this, SLOT(closeSlot()));
    connect(m_ui->pbClose, SIGNAL(clicked()), this, SLOT(close()));
}


void WarehouseSystemArrangeOrderWidget::prepareUi()
{
    m_ui->sbProductsCount->setEnabled(false);
    m_ui->sbProductsCount->setValue(0);

    m_ui->lePositionCost->setReadOnly(true);
    m_ui->lePositionCost->setEnabled(false);

    m_ui->leTotalCost->setReadOnly(true);
    m_ui->leTotalCost->setEnabled(false);
    m_ui->lChangedProduct->setVisible(false);
    m_ui->pbAddProduct->setEnabled(false);

    m_ui->pbArrangeOrder->setEnabled(false);

    m_ui->cbProducts->addItem("<Выберите продукт из списка>");
    m_ui->cbCustomers->insertSeparator(m_ui->cbCustomers->count());

    foreach (auto idProduct, m_dataManager->idProductList())
    {
        QVariant idProductVariant = QVariant::fromValue(idProduct);
        m_ui->cbProducts->addItem(m_dataManager->nameProductById(idProduct), idProductVariant);
    }

    setItemCbCustomers();
    show();
}

void WarehouseSystemArrangeOrderWidget::changedProductSlot()
{
    int idCurrentProduct = m_ui->cbProducts->itemData(m_ui->cbProducts->currentIndex()).toInt();

    if (m_ui->cbProducts->currentIndex() != 0)
    {
        m_order->setChangedProduct(idCurrentProduct);
    }


    if (m_ui->cbProducts->currentIndex() != 0)
    {
        m_ui->sbProductsCount->setEnabled(true);

        m_order->setChangedProductCount(m_ui->sbProductsCount->text().toDouble());
        m_ui->lePositionCost->setText(QString::number(m_order->positionCost()));

        m_ui->sbProductsCount->setMaximum(m_dataManager->countProductById(idCurrentProduct));
        m_ui->lProductsCountUnit->setText(m_dataManager->unitOfMeasureProductById(idCurrentProduct));
    }
    else
    {
        m_ui->sbProductsCount->setEnabled(false);
        m_ui->lePositionCost->clear();
        m_ui->lePositionCost->setEnabled(false);
        m_ui->leTotalCost->setEnabled(false);
        m_ui->sbProductsCount->setValue(0);
        m_ui->pbAddProduct->setEnabled(false);
    }
}
void WarehouseSystemArrangeOrderWidget::productsCountChangeSlot()
{
    if (m_ui->cbProducts->currentIndex() != 0)
    {
        m_order->setChangedProductCount(m_ui->sbProductsCount->text().toDouble());
        m_ui->lePositionCost->setEnabled(true);
        m_ui->lePositionCost->setText(QString::number(m_order->positionCost()));

        if (m_ui->sbProductsCount->value() != 0)
        {
            m_ui->pbAddProduct->setEnabled(true);
        }
        else
        {
            m_ui->pbAddProduct->setEnabled(false);
        }
    }
}

void WarehouseSystemArrangeOrderWidget::addProductSlot()
{
    m_order->addPosition();

    m_ui->lChangedProduct->setVisible(true);
    m_ui->lChangedProduct->setText(m_order->infoProductsList());

    m_ui->cbProducts->removeItem(m_ui->cbProducts->currentIndex());
    m_ui->cbProducts->setCurrentIndex(0);

    m_ui->lePositionCost->setEnabled(false);
    m_ui->leTotalCost->setEnabled(true);
    m_ui->leTotalCost->setText(QString::number(m_order->totalCost()));
    m_ui->sbProductsCount->setValue(0);

    m_ui->sbProductsCount->setEnabled(false);
    m_ui->pbAddProduct->setEnabled(false);

    m_ui->pbArrangeOrder->setEnabled(true);
}

void WarehouseSystemArrangeOrderWidget::changedCustomerSlot()
{

}

void WarehouseSystemArrangeOrderWidget::addCustomerDialogSlot()
{
    if (m_addCustomerDialog == nullptr)
    {
        m_addCustomerDialog = new WarehouseSystemAddCustomerDialog();

        m_addCustomerDialog->show();
        connect(m_addCustomerDialog, SIGNAL(addCustomerToDBSignal()), this, SLOT(updateCbCustomerSlot()));
    }
    else if (m_addCustomerDialog != nullptr &&
             m_addCustomerDialog->isVisible() == false)
    {
        m_addCustomerDialog->close();
        delete m_addCustomerDialog;

        m_addCustomerDialog = new WarehouseSystemAddCustomerDialog();
        m_addCustomerDialog->show();
    }
}

void WarehouseSystemArrangeOrderWidget::updateCbCustomerSlot()
{
    delete m_dataManager;
    m_dataManager = new WarehouseSystemDataManager();
    m_ui->cbCustomers->clear();

    setItemCbCustomers();

    m_ui->cbCustomers->setCurrentIndex(m_ui->cbCustomers->count() -1);

    m_dataManager->customersCount();
}

void WarehouseSystemArrangeOrderWidget::closeSlot()
{
    emit closeEvent();
}

void WarehouseSystemArrangeOrderWidget::setItemCbCustomers()
{
    m_ui->cbCustomers->addItem("<Выберите покупателя из списка>");
    m_ui->cbCustomers->insertSeparator(m_ui->cbCustomers->count());

    foreach (auto idCustomer, m_dataManager->idCustomersList())
    {
        QVariant idCustomerVariant = QVariant::fromValue(idCustomer);
        m_ui->cbCustomers->addItem(m_dataManager->nameCustomerById(idCustomer), idCustomerVariant);
    }
}
