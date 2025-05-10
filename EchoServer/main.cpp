#include <QCoreApplication>
#include "EchoServer.h"
using namespace std;
int main(int argc,char *argv[]) {
	QCoreApplication a(argc,argv);
	EchoServer server;
	return a.exec();
}


