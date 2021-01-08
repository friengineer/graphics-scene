#include <GL/glut.h>
#include <QApplication>
#include <QVBoxLayout>
#include "SceneWindow.h"

// main function
int main(int argc, char *argv[]){
	// initialise GLUT
	glutInit(&argc, argv);

	// create application
	QApplication app(argc, argv);
	// create widget and set its size
  SceneWindow *window = new SceneWindow(NULL);
	window->resize(1500, 712);
	window->show();

	// start application
	app.exec();

	// release widget resources
	delete window;

	return 0;
}
