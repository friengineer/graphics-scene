#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QDial>
#include <QSlider>
#include <QTimer>
#include <QBoxLayout>
#include "SceneWidget.h"

// window for the scene
class SceneWindow: public QWidget{
	public:
	SceneWindow(QWidget *parent);
	~SceneWindow();

	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *actionQuit;

	QBoxLayout *windowLayout;
	QBoxLayout *controlsLayout;
	SceneWidget *sceneWidget;
	QDial *speedDial;
	QSlider *transparencySlider;

	QTimer *ptimer;

	void ResetInterface();
};

#endif
