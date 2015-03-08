#include <QCoreApplication>
#include "RobotThread.h"

int main(int argc, char ** argv) {
	QCoreApplication app(argc, argv);
	const char * topic;
	if (argc == 2 && argv[1][0] == '/') {
		topic = argv[1];
	} else {
		topic = "/odom";
	}

	RobotThread robot(argc, argv, topic);

	return app.exec();
}