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
	void updateTransparency(int value);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	void cube(bool shadow=false);
	void floor();
	void gravestone();
	void map();
	void ghost();
	void fog();

	void polygon(int, int, int, int);

	double _angle;
	float opacity;

	Image marc;
	Image world;

	QImage* fogTexture;
	unsigned int fogTextureWidth;
  unsigned int fogTextureHeight;

	};

#endif
