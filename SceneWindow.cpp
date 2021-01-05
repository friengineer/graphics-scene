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
	controlsLayout = new QBoxLayout(QBoxLayout::TopToBottom);

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
	controlsLayout->addWidget(transparencySlider);

	directionButton = new QPushButton(tr("Change direction of ghost"));
	controlsLayout->addWidget(directionButton);

	QLabel *speedText = new QLabel(tr("Speed of ghost"));
	controlsLayout->addWidget(speedText);

	speedDial = new QDial;
	speedDial->setRange(10, 60);
	speedDial->setValue(10);
	speedDial->setNotchesVisible(true);
	controlsLayout->addWidget(speedDial);

	QLabel *horizontalText = new QLabel(tr("Horizontal view"));
	controlsLayout->addWidget(horizontalText);

	xViewSlider = new QSlider(Qt::Horizontal);
	xViewSlider->setRange(-100, 100);
	xViewSlider->setValue(100);
	xViewSlider->setTickPosition(QSlider::TicksBelow);
	controlsLayout->addWidget(xViewSlider);

	QLabel *verticalText = new QLabel(tr("Vertical view"));
	controlsLayout->addWidget(verticalText);

	yViewSlider = new QSlider(Qt::Horizontal);
	yViewSlider->setRange(1, 199);
	yViewSlider->setValue(100);
	yViewSlider->setTickPosition(QSlider::TicksBelow);
	controlsLayout->addWidget(yViewSlider);

	QLabel *gravestoneText = new QLabel(tr("Gravestone colour"));
	controlsLayout->addWidget(gravestoneText);

	QLabel *redText = new QLabel(tr("Red"));
	controlsLayout->addWidget(redText);

	redBox = new QDoubleSpinBox;
	redBox->setRange(0, 1);
	redBox->setSingleStep(0.1);
	redBox->setValue(0.2);
	controlsLayout->addWidget(redBox);

	QLabel *greenText = new QLabel(tr("Green"));
	controlsLayout->addWidget(greenText);

	greenBox = new QDoubleSpinBox;
	greenBox->setRange(0, 1);
	greenBox->setSingleStep(0.1);
	greenBox->setValue(0.2);
	controlsLayout->addWidget(greenBox);

	QLabel *blueText = new QLabel(tr("Blue"));
	controlsLayout->addWidget(blueText);

	blueBox = new QDoubleSpinBox;
	blueBox->setRange(0, 1);
	blueBox->setSingleStep(0.1);
	blueBox->setValue(0.2);
	controlsLayout->addWidget(blueBox);

	ptimer = new QTimer(this);
	ptimer->start(20);

	connect(transparencySlider, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateTransparency(int)));
	connect(directionButton, SIGNAL(clicked()), sceneWidget, SLOT(changeDirection()));
	connect(speedDial, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateSpeed(int)));
	connect(xViewSlider, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateHorizontalView(int)));
	connect(yViewSlider, SIGNAL(valueChanged(int)), sceneWidget, SLOT(updateVerticalView(int)));
	connect(redBox, SIGNAL(valueChanged(double)), sceneWidget, SLOT(updateRed(double)));
	connect(greenBox, SIGNAL(valueChanged(double)), sceneWidget, SLOT(updateGreen(double)));
	connect(blueBox, SIGNAL(valueChanged(double)), sceneWidget, SLOT(updateBlue(double)));
	connect(ptimer, SIGNAL(timeout()), sceneWidget, SLOT(updateAngle()));
}

// destructor
SceneWindow::~SceneWindow(){
	delete ptimer;
	delete blueBox;
	delete greenBox;
	delete redBox;
	delete yViewSlider;
	delete xViewSlider;
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

	xViewSlider->setMinimum(-100);
	xViewSlider->setMaximum(100);

	yViewSlider->setMinimum(1);
	yViewSlider->setMaximum(199);

	// now force refresh
	controlsWidget->update();
	update();
}
