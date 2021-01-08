#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "Image.h"

class SceneWidget: public QGLWidget{

	Q_OBJECT

	public:
		
	SceneWidget(QWidget *parent);

	public slots:

	void updateAngle();
	void changeDirection();
	void updateSpeed(int value);
	void updateTransparency(int value);
	void updateHorizontalView(int value);
	void updateVerticalView(int value);
	void updateRed(double);
	void updateGreen(double);
	void updateBlue(double);

	protected:

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	private:

	// widget methods
	void floor();
	void openGrave();
	void gravestone();
	void crossGravestone();
	void tree();
	void body();
	void map();
	void ghost();
	void petal();
	void flower();
	void bouquet();
	void fog();

	// global variables of widget
	double _angle;
	float _direction;
	float _speed;
	double _xView;
	double _yView;
	Image _marc;
	Image _world;
};

#endif
