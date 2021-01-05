#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include "Image.h"

class SceneWidget: public QGLWidget{

	Q_OBJECT

	public:
	SceneWidget(QWidget *parent);

	public slots:
  // called by the timer in the main window
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
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	void floor();
	void openGrave();
	void gravestone();
	void crossGravestone();
	void tree();
	void map();
	void ghost();
	void petal();
	void flower();
	void bouquet();
	void fog();

	void polygon(int, int, int, int);

	double _angle;
	float direction;
	float speed;
	double xView;
	double yView;

	Image marc;
	Image world;

	QImage* fogTexture;
	unsigned int fogTextureWidth;
  unsigned int fogTextureHeight;

	};

#endif
