#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <string>
#include <QImage>
#include "SceneWidget.h"

// Setting up material properties
typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct redPlasticMaterials = {
  {0.3, 0.0, 0.0, 1.0},
  {0.6, 0.0, 0.0, 1.0},
  {0.8, 0.6, 0.6, 1.0},
  32.0
};

static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0
};

static materialStruct goldMaterials = {
  { 0.24725, 0.1995, 0.0745, 1.0},
  { 0.75164, 0.60648, 0.22648, 1.0},
  { 0.628281, 0.555802, 0.366065, 1.0},
  100
};

static materialStruct green = {
  { 0, 0.4, 0, 1.0},
  { 0, 0, 0, 1.0},
  { 0, 0, 0, 1.0},
  0
};

static materialStruct white = {
  { 1, 1, 1, 1.0},
  { 1, 1, 1, 1.0},
  { 0, 0, 0, 1.0},
  0
};

// constructor
SceneWidget::SceneWidget(QWidget *parent):QGLWidget(parent), _angle(0.0), opacity(0.5), marc("Marc_Dekamps.ppm"), world("Mercator-projection.ppm"){
  // const std::string& fogFile = "fog-overlay-free.jpg";
  // fogTexture = new QImage(QString(fogFile.c_str()));
  // fogTextureWidth = fogTexture->width();
  // fogTextureHeight = fogTexture->height();
}

void SceneWidget::initializeGL(){
	// set the widget background colour
	// glClearColor(0.3, 0.3, 0.3, 0.0);
  glClearColor(0, 0, 0.15, 0.0);
}

// called every time the widget is resized
void SceneWidget::resizeGL(int w, int h){
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glEnable(GL_LIGHTING); // enable lighting in general
  glEnable(GL_LIGHT0);   // each light source must also be enabled
  glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, marc.imageField());

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, marc.Width(), marc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, marc.imageField());
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world.Width(), world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world.imageField());

  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // glActiveTexture(GL_TEXTURE1);
  // glBindTexture(GL_TEXTURE_2D, world.imageField());
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world.Width(), world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world.imageField());
  //
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
}

void SceneWidget::floor(){
  materialStruct* material = &green;
  // GLfloat floor = -0.01;
  GLfloat floor = 0;
  // glColor3f(0,0.3,0);

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3f(0.,1.,0.);
  glBegin(GL_POLYGON);
    glVertex3f(-10.0, floor, 10.0);
    glVertex3f(10.0, floor, 10.0);
    glVertex3f(10.0, floor, -10.0);
    glVertex3f(-10.0, floor, -10.0);
  glEnd();
}

void SceneWidget::gravestone(){
  GLfloat normals[][3] = { {1., 0., 0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  // if (b_shadow == true){
  //       glDisable(GL_LIGHTING);
  //       glColor3f(0.,0.,0.);
  // }

  materialStruct* material = &redPlasticMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);



  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
  glVertex3f(0.75, 0, 0.25);
  glVertex3f(0.75, 0, -0.25);
  glVertex3f(0.75, 4, -0.25);
  glVertex3f(0.75, 4, 0.25);
  glEnd();

  // glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  // glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  // glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
  glVertex3f(-0.75, 0, -0.25);
  glVertex3f(0.75, 0, -0.25);
  glVertex3f(0.75, 4, -0.25);
  glVertex3f(-0.75, 4, -0.25);
  glEnd();

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
  glVertex3f(-0.75, 0, 0.25);
  glVertex3f(0.75, 0, 0.25);
  glVertex3f(0.75, 4, 0.25);
  glVertex3f(-0.75, 4, 0.25);
  glEnd();

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
  glVertex3f(-0.75, 0, 0.25);
  glVertex3f(-0.75, 0, -0.25);
  glVertex3f(-0.75, 4, -0.25);
  glVertex3f(-0.75, 4, 0.25);
  glEnd();

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
  glVertex3f(0.75, 4, 0.25);
  glVertex3f(0.75, 4, -0.25);
  glVertex3f(-0.75, 4, -0.25);
  glVertex3f(-0.75, 4, 0.25);
  glEnd();

  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
  glVertex3f(0.75, 0, 0.25);
  glVertex3f(0.75, 0, -0.25);
  glVertex3f(-0.75, 0, -0.25);
  glVertex3f(-0.75, 0, 0.25);
  glEnd();

  glEnable(GL_LIGHTING);
}

void SceneWidget::map(){
  // GLuint earth;
  // glGenTextures(1, &earth);
  // glActiveTexture(GL_TEXTURE1);
  // glBindTexture(GL_TEXTURE_2D, earth);

  GLfloat normal[] = {1, 0, 0};

  materialStruct* material = &goldMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normal);
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1.5, -1, 0);
  glTexCoord2f(1.0, 0.0);
  glVertex3f( 1.5, -1, 0);
  glTexCoord2f(1.0, 1.0);
  glVertex3f( 1.5,  1, 0);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-1.5,  1, 0);
  glEnd();

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world.Width(), world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world.imageField());

  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world.Width(), world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world.imageField());

  glEnable(GL_LIGHTING);
}

void SceneWidget::ghost(){
  // GLuint face;
  // glGenTextures(1, &face);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, face);
  //
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, marc.Width(), marc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, marc.imageField());
  //
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;
  GLUquadric *head = gluNewQuadric();
  gluQuadricDrawStyle(head, GLU_FILL);
  // glBindTexture(GL_TEXTURE_2D, marc);
  gluQuadricTexture(head, GL_TRUE);
  // glutSolidSphere(radius, 10, 10);
  // glRasterPos2i(0,0);
  // glDrawPixels(marc.Width(),marc.Height(),GL_RGB, GL_UNSIGNED_BYTE,marc.imageField());
  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  glRotatef(90, 0, 0, 1);
  gluSphere(head, radius, 10, 10);
  glPopMatrix();
  gluDeleteQuadric(head);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, marc.Width(), marc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, marc.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glPushMatrix();
  glTranslatef(0, -2 * radius, 0);

  GLUquadric *body = gluNewQuadric();
  // glutSolidIcosahedron();
  glRotatef(90, 1, 0, 0);
  gluCylinder(body, radius, radius, 3, 10, 10);
  glPopMatrix();
  gluDeleteQuadric(body);

  glPushMatrix();
  glTranslatef(2 * radius, -2 * radius, 0);
  glRotatef(-90, 0, 1, 0);
  this->map();
  glPopMatrix();

  glEnable(GL_LIGHTING);
}

void SceneWidget::fog(){
  materialStruct grey = {
    { 1, 1, 1, opacity},
    { 0, 0, 0, opacity},
    { 0, 0, 0, opacity},
    0
  };

  GLfloat normals[][3] = { {1., 0., 0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  materialStruct* material = &grey;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normals[0]);
  // glColor3f(0.2, 0.2, 0.2);
  glBegin(GL_POLYGON);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 0, -10);
  glVertex3f(10, 1.0, -10);
  glVertex3f(10, 1.0, 10);
  glEnd();

  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, -10);
  glVertex3f(10, 0, -10);
  glVertex3f(10, 1.0, -10);
  glVertex3f(-10, 1.0, -10);
  glEnd();

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, 10);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 1.0, 10);
  glVertex3f(-10, 1.0, 10);
  glEnd();

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, 10);
  glVertex3f(-10, 0, -10);
  glVertex3f(-10, 1.0, -10);
  glVertex3f(-10, 1.0, 10);
  glEnd();

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
  glVertex3f(10, 1.0, 10);
  glVertex3f(10, 1.0, -10);
  glVertex3f(-10, 1.0, -10);
  glVertex3f(-10, 1.0, 10);
  glEnd();

  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 0, -10);
  glVertex3f(-10, 0, -10);
  glVertex3f(-10, 0, 10);
  glEnd();

  glEnable(GL_LIGHTING);
}

void SceneWidget::cube(bool b_shadow){
  // normals of the cube faces
  GLfloat normals[][3] = { {1., 0., 0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  if (b_shadow == true){
        glDisable(GL_LIGHTING);
        glColor3f(0.,0.,0.);
  }

  materialStruct* material = &goldMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
  glVertex3f( 1.0, -1.0,  1.0);
  glVertex3f( 1.0, -1.0, -1.0);
  glVertex3f( 1.0,  1.0, -1.0);
  glVertex3f( 1.0,  1.0,  1.0);
  glEnd();

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
  glVertex3f(-1.0, -1.0, -1.0);
  glVertex3f( 1.0, -1.0, -1.0);
  glVertex3f( 1.0,  1.0, -1.0);
  glVertex3f(-1.0,  1.0, -1.0);
  glEnd();

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
  glVertex3f(-1.0, -1.0, 1.0);
  glVertex3f( 1.0, -1.0, 1.0);
  glVertex3f( 1.0,  1.0, 1.0);
  glVertex3f(-1.0,  1.0, 1.0);
  glEnd();

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
  glVertex3f( -1.0, -1.0,  1.0);
  glVertex3f( -1.0, -1.0, -1.0);
  glVertex3f( -1.0,  1.0, -1.0);
  glVertex3f( -1.0,  1.0,  1.0);
  glEnd();

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
  glVertex3f(  1.0,  1.0,  1.0);
  glVertex3f(  1.0,  1.0, -1.0);
  glVertex3f( -1.0,  1.0, -1.0);
  glVertex3f( -1.0,  1.0,  1.0);
  glEnd();

  glNormal3fv(normals[5]);
  glBegin(GL_POLYGON);
  glVertex3f(  1.0,  -1.0,  1.0);
  glVertex3f(  1.0,  -1.0, -1.0);
  glVertex3f( -1.0,  -1.0, -1.0);
  glVertex3f( -1.0,  -1.0,  1.0);
  glEnd();

  glEnable(GL_LIGHTING);
}

void SceneWidget::updateAngle(){
  _angle += 1.0;
  this->repaint();
}

void SceneWidget::updateTransparency(int value){
  opacity = (float) value/100;
  this->repaint();
}

// called every time the widget needs painting
void SceneWidget::paintGL(){
	// clear the widget
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Position light
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat light_pos[] = {1.5, 7, 1., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,180.);

	GLfloat m[16];
	for (int i = 0; i < 16; i++){
    m[i] = 0.0;
  }

	m[0] = m[5] = m[10] = 1.0;
	m[7] = -1.0/light_pos[1];
	glPopMatrix();
	this->floor();

	// Done light

  // You must set the matrix mode to model view directly before enabling the depth test
  glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();

  glPushMatrix();
  glTranslatef(-9, 0, 4);
  this->gravestone();
  glTranslatef(2, 0, 0);
  this->gravestone();
  glTranslatef(2, 0, 0);
  this->gravestone();
  glTranslatef(2, 0, 0);
  this->gravestone();

  glTranslatef(0, 0, -5);
  this->gravestone();
  glTranslatef(-2, 0, 0);
  this->gravestone();
  glTranslatef(-2, 0, 0);
  this->gravestone();
  glTranslatef(-2, 0, 0);
  this->gravestone();


  glPopMatrix();

  glPushMatrix();
  glRotatef(-_angle, 0, 1, 0);
  glTranslatef(0, 10, -7);
  this->ghost();
  // this->map();
  glPopMatrix();

	// glPushMatrix();
	// glTranslatef(0.,2.,0.);
	// glRotatef(_angle, 0.,1., 0.);
  //
	// this->cube();
	// glTranslatef(0.,-2.,0);
  //
	// // Do the projective stuff
	// glPushMatrix();
	// glPushAttrib(GL_CURRENT_BIT);
  //
	// glTranslatef(light_pos[0],light_pos[1],light_pos[2]);
	// glMultMatrixf(m);
	// glTranslatef(-light_pos[0],-light_pos[1],-light_pos[2]);
  //
	// glColor3f(0.,0.,0.);
	// this->cube(true);
	// glPopMatrix();
	// glPopAttrib();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->fog();

  glLoadIdentity();
  gluLookAt(1.,1.,1., 0.0,0.0,0.0, 0.0,1.0,0.0);

	// flush to screen
	glFlush();
	}
