#ifndef INVENTORY_QT_INTERFACE_H
#define INVENTORY_QT_INTERFACE_H

#include <QMainWindow>

#include "inventory_constants.h"

namespace Ui {
    class InventoryQtInterface;
}

class InventoryQtInterface : public QMainWindow {
	Q_OBJECT
public:
	explicit InventoryQtInterface(QWidget *parent = 0);
	virtual ~InventoryQtInterface();
};

#endif /* INVENTORY_QT_INTERFACE_H */
