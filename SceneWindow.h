#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>
#include <QDial>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QTimer>
#include <QBoxLayout>
#include "SceneWidget.h"

// window for scene
class SceneWindow: public QWidget{
	public:
		
	SceneWindow(QWidget *parent);
	~SceneWindow();

	// menu widgets
	QMenuBar *menuBar;
	QMenu *fileMenu;
	QAction *actionQuit;

	// widgets
	QBoxLayout *windowLayout;
	QBoxLayout *controlsLayout;
	SceneWidget *sceneWidget;
	QWidget *controlsWidget;
	QLabel *transparencyText;
	QSlider *transparencySlider;
	QPushButton *directionButton;
	QLabel *speedText;
	QDial *speedDial;
	QLabel *horizontalText;
	QSlider *xViewSlider;
	QLabel *verticalText;
	QSlider *yViewSlider;
	QLabel *gravestoneText;
	QLabel *redText;
	QDoubleSpinBox *redBox;
	QLabel *greenText;
	QDoubleSpinBox *greenBox;
	QLabel *blueText;
	QDoubleSpinBox *blueBox;
	QTimer *ptimer;

	void ResetInterface();
};

#endif
