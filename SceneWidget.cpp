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

static materialStruct black = {
  { 0, 0, 0, 1.0},
  { 0, 0, 0, 1.0},
  { 0, 0, 0, 1.0},
  0
};

static materialStruct brown = {
  { 0.36, 0.25, 0.2, 1.0},
  { 0.36, 0.25, 0.2, 1.0},
  { 0, 0, 0, 1.0},
  0
};

static materialStruct white = {
  { 1, 1, 1, 1.0},
  { 1, 1, 1, 1.0},
  { 0, 0, 0, 1.0},
  0
};

static materialStruct yellow = {
  {1, 1, 0.0, 1.0},
  {1, 1, 0.0, 1.0},
  {0, 0, 0, 1},
  0
};

static materialStruct red = {
  {1, 0.0, 0.0, 1.0},
  {1, 0.0, 0.0, 1.0},
  {0, 0, 0, 1},
  0
};

materialStruct graveMaterial = {
  { 0.2, 0.2, 0.2, 1},
  { 0.2, 0.2, 0.2, 1},
  { 1, 1, 1, 1},
  32
};

materialStruct grey = {
  { 1, 1, 1, 0.5},
  { 0, 0, 0, 0.5},
  { 0, 0, 0, 0.5},
  0
};

// constructor
SceneWidget::SceneWidget(QWidget *parent):QGLWidget(parent),
  _angle(0.0),
  direction(-1),
  speed(1),
  xView(1),
  yView(1),
  marc("Marc_Dekamps.ppm"),
  world("Mercator-projection.ppm"){
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

void SceneWidget::openGrave(){
  materialStruct* material = &graveMaterial;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glPushMatrix();
  glTranslatef(0, 1, 4);
  glScalef(5, 3, 0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 1, -4);
  glScalef(5, 3, 0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2.25, 1, 0);
  glScalef(0.5, 3, 8);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2.25, 1, 0);
  glScalef(0.5, 3, 8);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -6);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1, 8, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 2.5, -1.5);
  glRotatef(45, 0, 1, 0);
  glScalef(5, 0.5, 8);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 8, -6);
  GLUquadric *head = gluNewQuadric();
  gluQuadricDrawStyle(head, GLU_FILL);
  gluSphere(head, 1, 10, 10);
  gluDeleteQuadric(head);
  glPopMatrix();

  material = &black;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glPushMatrix();
  glTranslatef(0, 1.1, 0);
  glScalef(5, 0, 8);
  glutSolidCube(1);
  glPopMatrix();
}

void SceneWidget::gravestone(){
  GLfloat normals[][3] = { {1., 0., 0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  materialStruct* material = &graveMaterial;

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

void SceneWidget::crossGravestone(){
  materialStruct* material = &graveMaterial;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glPushMatrix();
  glTranslatef(0, 2, 0);
  glScalef(0.5, 4, 0.5);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 2.5, 0);
  glScalef(1.5, 1, 0.5);
  glutSolidCube(1);
  glPopMatrix();
}

void SceneWidget::tree(){
  materialStruct* material = &brown;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1, 8, 10, 10);
  glPopMatrix();

  glTranslatef(0, 5, 0);

  glPushMatrix();
  glRotatef(-45, 1, 1, 0);
  glutSolidCone(0.25, 2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-135, 0, 1, 0);
  glRotatef(-60, 1, 0, 0);
  glutSolidCone(0.25, 4, 10, 10);

  glTranslatef(0, 0, 2);
  glRotatef(45, 1, 0, 0);
  glutSolidCone(0.0625, 2, 10, 10);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(0.125, 1.5, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-225, 0, 1, 0);
  glRotatef(-55, 1, 0, 0);
  glutSolidCone(0.25, 4, 10, 10);

  glTranslatef(0, 0, 2);
  glRotatef(45, 0, 1, 0);
  glutSolidCone(0.0625, 2, 10, 10);
  glRotatef(-90, 0, 1, 0);
  glutSolidCone(0.125, 1.5, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-315, 0, 1, 0);
  glRotatef(-49, 1, 0, 0);
  glutSolidCone(0.25, 4, 10, 10);

  glTranslatef(0, 0, 2);
  glRotatef(-20, 1, 1, 0);
  glutSolidCone(0.0625, 2, 10, 10);
  glRotatef(45, 0, 1, 0);
  glutSolidCone(0.125, 1.5, 10, 10);
  glPopMatrix();
}

void SceneWidget::map(){
  GLfloat normal[] = {1, 0, 0};

  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // material = &goldMaterials;
  //
  // glMaterialfv(GL_BACK, GL_AMBIENT, material->ambient);
  // glMaterialfv(GL_BACK, GL_DIFFUSE, material->diffuse);
  // glMaterialfv(GL_BACK, GL_SPECULAR, material->specular);
  // glMaterialf(GL_BACK, GL_SHININESS, material->shininess);

  GLuint earth;
  glGenTextures(1, &earth);
  glBindTexture(GL_TEXTURE_2D, earth);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, world.Width(), world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, world.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &earth);

  glEnable(GL_LIGHTING);
}

void SceneWidget::ghost(){
  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  GLuint face;
  glGenTextures(1, &face);
  glBindTexture(GL_TEXTURE_2D, face);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, marc.Width(), marc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, marc.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  float radius = 1;

  glPushMatrix();
  GLUquadric *head = gluNewQuadric();
  gluQuadricDrawStyle(head, GLU_FILL);
  gluQuadricTexture(head, GL_TRUE);

  glRotatef(-90, 1, 0, 0);
  glRotatef(90, 0, 0, 1);
  glRotatef(2 * _angle, 0, 0, 1);
  gluSphere(head, radius, 10, 10);
  gluDeleteQuadric(head);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &face);

  glPushMatrix();
  glTranslatef(0, -2 * radius, 0);

  GLUquadric *body = gluNewQuadric();
  glRotatef(90, 1, 0, 0);
  gluCylinder(body, radius, radius, 3, 10, 10);
  gluDeleteQuadric(body);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(direction * -2 * radius, -2 * radius, 0);
  glRotatef(direction * 90, 0, 1, 0);
  glRotatef(-_angle, 0, 0, 1);
  this->map();
  glPopMatrix();

  glEnable(GL_LIGHTING);
}

void SceneWidget::petal(){
  materialStruct* material = &red;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;

  glPushMatrix();
  glScalef(0.3, 0.2, 0.1);

  GLUquadric *oblong = gluNewQuadric();
  gluQuadricDrawStyle(oblong, GLU_FILL);
  gluSphere(oblong, radius, 10, 10);
  gluDeleteQuadric(oblong);
  glPopMatrix();
}

void SceneWidget::flower(){
  materialStruct* material = &yellow;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;

  glPushMatrix();
  glScalef(0.3, 0.2, 0.3);

  GLUquadric *centre = gluNewQuadric();
  gluQuadricDrawStyle(centre, GLU_FILL);
  gluSphere(centre, radius, 10, 10);
  gluDeleteQuadric(centre);
  glPopMatrix();

  // create petals around flower's centre
  for(int i = 0; i < 8 ; i++){
    glPushMatrix();
    glRotatef(i * 45, 0, 1, 0);
    glTranslatef(-0.5, 0, 0);
    this->petal();
    glPopMatrix();
  }
}

void SceneWidget::bouquet(){
  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glPushMatrix();
  glTranslatef(0, 2, 0);
  glRotatef(90, 1, 0, 0);
  glutSolidCone(0.5, 2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25, 2.5, 0);
  glRotatef(25, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  this->flower();
  glPopMatrix();
}

void SceneWidget::fog(){
  GLfloat normals[][3] = { {1., 0., 0.}, {-1., 0., 0.}, {0., 0., 1.}, {0., 0., -1.}, {0, 1, 0}, {0, -1, 0} };

  materialStruct* material = &grey;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3fv(normals[0]);
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

void SceneWidget::updateAngle(){
  _angle += speed;
  this->repaint();
}

void SceneWidget::changeDirection(){
  direction *= -1;
}

void SceneWidget::updateSpeed(int value){
  speed = (float) value/10;
}

void SceneWidget::updateTransparency(int value){
  grey.ambient[3] = (float) value/100;
  grey.diffuse[3] = (float) value/100;
  grey.specular[3] = (float) value/100;
  this->repaint();
}

void SceneWidget::updateHorizontalView(int value){
  xView = (float) value/100;
  this->repaint();
}

void SceneWidget::updateVerticalView(int value){
  yView = (float) value/100;

  // if (xView > 0){
  //   xView = 2 - yView;
  // } else if (xView < 0) {
  //   xView = yView - 2;
  // }

  this->repaint();
}

void SceneWidget::updateRed(double value){
  graveMaterial.ambient[0] = value;
  graveMaterial.diffuse[0] = value;
}

void SceneWidget::updateGreen(double value){
  graveMaterial.ambient[1] = value;
  graveMaterial.diffuse[1] = value;
}

void SceneWidget::updateBlue(double value){
  graveMaterial.ambient[2] = value;
  graveMaterial.diffuse[2] = value;
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
	// GLfloat light_pos[] = {1.5, 7, 1., 1.};
  GLfloat light_pos[] = {-10, 20, 20, 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,180.);

	glPopMatrix();
	this->floor();

	// Done light

  // You must set the matrix mode to model view directly before enabling the depth test
  glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();

  glPushMatrix();
  glTranslatef(0, 0, 1);
  this->openGrave();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-8, 0, 1);
  this->gravestone();
  glTranslatef(2, 0, 0);
  this->crossGravestone();
  glTranslatef(2, 0, 0);
  this->gravestone();
  glTranslatef(0, 0, -5);
  this->crossGravestone();
  glTranslatef(-2, 0, 0);
  this->gravestone();
  glTranslatef(-2, 0, 0);
  this->crossGravestone();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(8, 0, 1);
  this->crossGravestone();
  glTranslatef(-2, 0, 0);
  this->gravestone();
  glTranslatef(-2, 0, -5);
  this->gravestone();
  glTranslatef(2, 0, 0);
  this->crossGravestone();
  glTranslatef(2, 0, 0);
  this->gravestone();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(8, 0, -8);
  this->tree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-8, 0, -8);
  glRotatef(90, 0, 1, 0);
  this->tree();
  glPopMatrix();

  glPushMatrix();
  glRotatef(direction * _angle, 0, 1, 0);
  glTranslatef(0, 10, -7);
  this->ghost();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 8, 0);
  this->bouquet();
  glPopMatrix();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->fog();

  glLoadIdentity();
  gluLookAt(xView,yView,1, 0.0,0.0,0.0, 0.0,1.0,0.0);
  // gluLookAt(0.1,1.9,0.1, 0.0,0.0,0.0, 0.0,1.0,0.0);

	// flush to screen
	glFlush();
	}
