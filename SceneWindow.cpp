#include "SceneWindow.h"

// constructor
SceneWindow::SceneWindow(QWidget *parent):QWidget(parent){
	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu("&File");
	actionQuit = new QAction("&Quit", this);

	fileMenu->addAction(actionQuit);

	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	sceneWidget = new SceneWidget(this);
	windowLayout->addWidget(sceneWidget);

	transparencySlider = new QSlider(Qt::Horizontal);
	transparencySlider->setValue(50);
	windowLayout->addWidget(transparencySlider);

	speedDial = new QDial;
	windowLayout->addWidget(speedDial);

	ptimer = new QTimer(this);
	ptimer->start(20);

	connect(transparencySlider, SIGNAL(sliderMoved(int)), sceneWidget, SLOT(updateTransparency(int)));
	connect(ptimer, SIGNAL(timeout()), sceneWidget, SLOT(updateAngle()));
}

// destructor
SceneWindow::~SceneWindow(){
	delete ptimer;
	delete speedDial;
	delete transparencySlider;
	delete sceneWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
}

// reset interface elements
void SceneWindow::ResetInterface(){
	transparencySlider->setMinimum(0);
	transparencySlider->setMaximum(100);

	speedDial->setMinimum(1);
	speedDial->setMaximum(60);

	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);

	// now force refresh
	sceneWidget->update();
	update();
}
