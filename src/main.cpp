#include <QCoreApplication>
#include "RobotThread.h"

int main(int argc, char ** argv) {
	QCoreApplication app(argc, argv);

	RobotThread robot(argc, argv);
	robot.init();

	//connect(&app, SIGNAL(aboutToQuit()), &robot, SLOT(halt()));
	return app.exec();
}