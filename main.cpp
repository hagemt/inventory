#include <string>
#include <vector>

#include <QApplication>
#include <QString>

#include "tclap/CmdLine.h"

#include "inventory_constants.h"
#include "inventory_qt_interface.h"

struct {
	bool verbose_mode;
	std::vector<std::string> data_files;
} session_data;

void parse_args(int &argc, char *argv[]) {
	try {
		// Init the options object
		QString id = QObject::tr("%1 %2 core (%3)").arg(
						PRODUCT_NAME,
						VERSION_STRING,
						BUILD_HASH);
		TCLAP::CmdLine options(id.toStdString(), ' ', VERSION_STRING);
		TCLAP::SwitchArg verbose_switch("v", "verbose",
			"Enable loud output (all messages)", options, false);
		// We're allowed exactly one of these:
		TCLAP::UnlabeledMultiArg<std::string> remainder("files",
			"Names of data files to load", false,
			"data_file", "string (path)");
                options.add(remainder);
		// Parse all the options, and fill in session
		options.parse(argc, argv);
		session_data.verbose_mode = verbose_switch.getValue();
		session_data.data_files = remainder.getValue();
		// And catch all exceptions
	} catch (TCLAP::ArgException &e) {
		std::cerr << e.error() << std::endl;
	}
}

int main(int argc, char *argv[]) {
	parse_args(argc, argv);
	// Create an event loop and window
	QApplication application(argc, argv);
	setlocale(LC_NUMERIC, "C");
	InventoryQtInterface main_window;
	main_window.show();
	return application.exec();
}
