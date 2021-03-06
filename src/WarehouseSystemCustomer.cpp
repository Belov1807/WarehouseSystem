#include "WarehouseSystemCustomer.h"

WarehouseSystemCustomer::WarehouseSystemCustomer(QString _name , QString _inn, QString _phone, QString _address, int _id) :
    m_name(_name),
    m_inn(_inn),
    m_phone(_phone),
    m_address(_address),
    m_id(_id)
{
}

int WarehouseSystemCustomer::id() const
{
    return m_id;
}

QString WarehouseSystemCustomer::name() const
{
    return m_name;
}

QString WarehouseSystemCustomer::inn() const
{
    return m_inn;
}

QString WarehouseSystemCustomer::phone() const
{
    return m_phone;
}

QString WarehouseSystemCustomer::address() const
{
    return m_address;
}
