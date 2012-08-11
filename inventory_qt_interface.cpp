#include "inventory_qt_interface.h"
#include "ui_inventory_qt_interface.h"

InventoryQtInterface::InventoryQtInterface(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::InventoryQtInterface),
	settings(QSettings::IniFormat, QSettings::UserScope, COMPANY_NAME, PRODUCT_NAME)
{
	setWindowTitle(tr("%1 %2").arg(PRODUCT_NAME, VERSION_STRING));
}

InventoryQtInterface::~InventoryQtInterface()
{
	delete ui;
}

void InventoryQtInterface::changeEvent(QEvent *e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}
