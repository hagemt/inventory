#ifndef INVENTORY_QT_INTERFACE_H
#define INVENTORY_QT_INTERFACE_H

#include <QEvent>
#include <QMainWindow>
#include <QSettings>

#include "inventory_constants.h"

namespace Ui {
    class InventoryQtInterface;
}

class InventoryQtInterface : public QMainWindow {
	Q_OBJECT
public:
	explicit InventoryQtInterface(QWidget *parent = 0);
	virtual ~InventoryQtInterface();
protected:
	void changeEvent(QEvent *e);
private:
	Ui::InventoryQtInterface *ui;
	QSettings settings;
};

#endif /* INVENTORY_QT_INTERFACE_H */
