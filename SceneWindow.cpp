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

	QLabel *transparencyText = new QLabel(tr("Transparency level of fog"));
	controlsLayout->addWidget(transparencyText);

	transparencySlider = new QSlider(Qt::Horizontal);
	transparencySlider->setValue(50);
	transparencySlider->setTickPosition(QSlider::TicksBelow);
	// windowLayout->addWidget(transparencySlider);
	controlsLayout->addWidget(transparencySlider);

	directionButton = new QPushButton(tr("Change direction of ghost"));
	controlsLayout->addWidget(directionButton);

	QLabel *speedText = new QLabel(tr("Speed of ghost"));
	controlsLayout->addWidget(speedText);

	speedDial = new QDial;
	speedDial->setRange(10, 60);
	speedDial->setValue(10);
	speedDial->setNotchesVisible(true);
	// windowLayout->addWidget(speedDial);
	controlsLayout->addWidget(speedDial);

	// windowLayout->addLayout(controlsLayout);

	ptimer = new QTimer(this);
	ptimer->start(20);

	connect(transparencySlider, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateTransparency(int)));
	connect(directionButton, SIGNAL(clicked()), sceneWidget, SLOT(changeDirection()));
	connect(speedDial, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateSpeed(int)));
	connect(ptimer, SIGNAL(timeout()), sceneWidget, SLOT(updateAngle()));
}

// destructor
SceneWindow::~SceneWindow(){
	delete ptimer;
	delete speedDial;
	// delete speedText;
	delete directionButton;
	delete transparencySlider;
	// delete transparencyText;
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

	speedDial->setMinimum(10);
	speedDial->setMaximum(60);

	// now force refresh
	controlsWidget->update();
	update();
}
