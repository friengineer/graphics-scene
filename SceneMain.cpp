#include <GL/glut.h>
#include <QApplication>
#include <QVBoxLayout>
#include "SceneWindow.h"

// main function to create the application and master widget
int main(int argc, char *argv[]){
	// initialise GLUT
	glutInit(&argc, argv);
	
	QApplication app(argc, argv);
  SceneWindow *window = new SceneWindow(NULL);
	window->resize(1500, 712);
	window->show();

	// start application
	app.exec();

	// release widget resources
	delete window;

	return 0;
}
