#ifndef WAREHOUSESYSTEMORDER_H
#define WAREHOUSESYSTEMORDER_H

#include <QList>

class WarehouseSystemProduct;
class WarehouseSystemCustomer;
class WarehouseSystemOrderOnePosition;

/*!
 * \brief Класс заказа.
 */
class WarehouseSystemOrder
{
public:
    /*!
     * \brief Конструктор.
     * \param _id - ижентификатор.
     * \param _customer - покупатель.
     */
    WarehouseSystemOrder(int _id = int(), WarehouseSystemCustomer *_customer = nullptr);

    /*!
     * \brief Установлевает выбранную продукцию.
     * \param _changedProduct - выбранная продукция.
     */
    void setChangedProduct(WarehouseSystemProduct *_changedProduct);

    /*!
     * \brief Устанавливает количество выбранной продукции.
     * \param _changedCountProduct - количество выбранной продукции.
     */
    void setChangedProductCount(double _changedCountProduct);
    /*!
     * \brief Возвращает количество выбранной продукции.
     * \return количество выбранной продукции.
     */
    double changedCountProduct() const;

    /*!
     * \brief Возвращает описание списка продуктов.
     * \return - описание списка продуктов.
     */
    QString infoProductsList() const;

    /*!
     * \brief Добавляет позицию.
     */
    void addPosition();

    /*!
     * \brief Возвращает общую стоимость заказа.
     * \return общая стоимость заказа.
     */
    double totalCost() const;

private:
    /*!
     * \brief Идетинфикатор.
     */
    int m_id;

    /*!
     * \brief Покупатель.
     */
    WarehouseSystemCustomer *m_customer;

    /*!
     * \brief Позиция заказа.
     */
    WarehouseSystemOrderOnePosition *m_orderPosition;

    /*!
     * \brief Список позиций.
     */
    QList<WarehouseSystemOrderOnePosition*> m_positionsList;
};


#endif // WAREHOUSESYSTEMORDER_H
