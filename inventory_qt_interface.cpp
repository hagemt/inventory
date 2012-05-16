#include "inventory_qt_interface.h"
#include "ui_inventory_qt_interface.h"

InventoryQtInterface::InventoryQtInterface(QWidget *parent)
{
	setWindowTitle(tr("%1 %2").arg(PRODUCT_NAME, VERSION_STRING));
}

InventoryQtInterface::~InventoryQtInterface()
{
	
}
