#include "SceneWindow.h"

// constructor
SceneWindow::SceneWindow(QWidget *parent):QWidget(parent){
	menuBar = new QMenuBar(this);
	fileMenu = menuBar->addMenu("&File");
	actionQuit = new QAction("&Quit", this);

	fileMenu->addAction(actionQuit);

	// windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	windowLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	// need to create separate control widget
	controlsLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	sceneWidget = new SceneWidget(this);
	controlsWidget = new QWidget(this);
	controlsWidget->setLayout(controlsLayout);
	controlsWidget->setFixedWidth(200);

	windowLayout->addWidget(sceneWidget);
	windowLayout->addWidget(controlsWidget);

	transparencySlider = new QSlider(Qt::Horizontal);
	transparencySlider->setValue(50);
	// windowLayout->addWidget(transparencySlider);
	controlsLayout->addWidget(transparencySlider);

	speedDial = new QDial;
	// windowLayout->addWidget(speedDial);
	controlsLayout->addWidget(speedDial);

	// windowLayout->addLayout(controlsLayout);

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
	delete controlsWidget;
	delete sceneWidget;
	delete controlsLayout;
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
	controlsWidget->update();
	update();
}
