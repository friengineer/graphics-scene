#include <GL/glu.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <string>
#include <QImage>
#include "SceneWidget.h"

// structure containing material properties
typedef struct materialStruct{
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

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
  { 0, 0.4, 0, 1},
  { 0, 0, 0, 1},
  { 0, 0, 0, 1},
  0
};

static materialStruct black = {
  { 0, 0, 0, 1},
  { 0, 0, 0, 1},
  { 0, 0, 0, 1},
  0
};

static materialStruct brown = {
  { 0.36, 0.25, 0.2, 1},
  { 0.36, 0.25, 0.2, 1},
  { 0, 0, 0, 1},
  0
};

static materialStruct white = {
  { 1, 1, 1, 1},
  { 1, 1, 1, 1},
  { 0, 0, 0, 1},
  0
};

static materialStruct yellow = {
  {1, 1, 0, 1},
  {1, 1, 0, 1},
  {0, 0, 0, 1},
  0
};

static materialStruct red = {
  {1, 0, 0, 1},
  {1, 0, 0, 1},
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
  _angle(0),
  _direction(-1),
  _speed(1),
  _xView(1),
  _yView(1),
  _marc("Marc_Dekamps.ppm"),
  _world("Mercator-projection.ppm"){}

// initialises widget by setting the background colour
void SceneWidget::initializeGL(){
  glClearColor(0, 0, 0.15, 0);
}

// called when widget is resized with specified width and height
void SceneWidget::resizeGL(int w, int h){
	// set viewport to entire widget
	glViewport(0, 0, w, h);

  // enable lighting, light and texturing
	glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  // set viewable area
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15, 15, -15, 15, -15, 15);
}

// create floor
void SceneWidget::floor(){
  materialStruct* material = &green;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  glNormal3f(0,1,0);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, 10);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 0, -10);
  glVertex3f(-10, 0, -10);
  glEnd();
}

// create an open grave
void SceneWidget::openGrave(){
  materialStruct* material = &graveMaterial;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // draw side of grave, repeat
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

  // draw angel's body
  glPushMatrix();
  glTranslatef(0, 0, -6);
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1, 8, 10, 10);
  glPopMatrix();

  // draw lid of grave
  glPushMatrix();
  glTranslatef(0, 2.5, -1.5);
  glRotatef(45, 0, 1, 0);
  glScalef(5, 0.5, 8);
  glutSolidCube(1);
  glPopMatrix();

  // draw angel's head
  glPushMatrix();
  glTranslatef(0, 8, -6);
  GLUquadric *head = gluNewQuadric();
  gluQuadricDrawStyle(head, GLU_FILL);
  gluSphere(head, 1, 40, 40);
  gluDeleteQuadric(head);
  glPopMatrix();

  material = &black;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // draw black inside of grave
  glPushMatrix();
  glTranslatef(0, 1.1, 0);
  glScalef(5, 0, 8);
  glutSolidCube(1);
  glPopMatrix();
}

// create a cuboid gravestone
void SceneWidget::gravestone(){
  // define normals for each face
  GLfloat normals[][3] = {{1, 0, 0},
                          {-1, 0, 0},
                          {0, 0, 1},
                          {0, 0, -1},
                          {0, 1, 0},
                          {0, -1, 0}};

  materialStruct* material = &graveMaterial;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // assign normal for face and draw face, repeat for all faces
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

// create a cross gravestone
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

// create a tree
void SceneWidget::tree(){
  materialStruct* material = &brown;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // draw trunk
  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  glutSolidCone(1, 8, 10, 10);
  glPopMatrix();

  glTranslatef(0, 5, 0);

  // draw branch, repeat
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

// create body
void SceneWidget::body(){
  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;

  glPushMatrix();
  GLUquadric *body = gluNewQuadric();
  glRotatef(90, 1, 0, 0);
  gluCylinder(body, radius, radius, 3, 40, 40);
  gluDeleteQuadric(body);

  GLUquadric *top = gluNewQuadric();
  gluDisk(top, 0, radius, 40, 40);
  gluDeleteQuadric(top);

  glTranslatef(0, 0, 3);
  GLUquadric *bottom = gluNewQuadric();
  gluDisk(bottom, 0, radius, 40, 40);
  gluDeleteQuadric(bottom);
  glPopMatrix();
}

// create a map
void SceneWidget::map(){
  // define normal for map
  GLfloat normal[] = {0, 0, 1};

  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // allocate space for map texture, bind to it, load it in and define parameters
  GLuint earth;
  glGenTextures(1, &earth);
  glBindTexture(GL_TEXTURE_2D, earth);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _world.Width(), _world.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _world.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // draw textured map
  glNormal3fv(normal);
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);
  glVertex3f(-1.5, -1, 0);
  glTexCoord2f(1, 0);
  glVertex3f(1.5, -1, 0);
  glTexCoord2f(1, 1);
  glVertex3f(1.5, 1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.5, 1, 0);
  glEnd();

  // bind to default texture and delete texture
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &earth);

  // set material for back of map
  material = &goldMaterials;

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);

  // draw back of map
  glPushMatrix();
  glTranslatef(0, 0, -0.005);

  glNormal3fv(normal);
  glBegin(GL_POLYGON);
  glTexCoord2f(0, 0);
  glVertex3f(-1.5, -1, 0);
  glTexCoord2f(1, 0);
  glVertex3f(1.5, -1, 0);
  glTexCoord2f(1, 1);
  glVertex3f(1.5, 1, 0);
  glTexCoord2f(0, 1);
  glVertex3f(-1.5, 1, 0);
  glEnd();
  glPopMatrix();

  glEnable(GL_LIGHTING);
}

// create a ghost
void SceneWidget::ghost(){
  materialStruct* material = &white;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // allocate space for face texture, bind to it, load it in and define parameters
  GLuint face;
  glGenTextures(1, &face);
  glBindTexture(GL_TEXTURE_2D, face);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _marc.Width(), _marc.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _marc.imageField());

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  float radius = 1;

  // draw textured head
  glPushMatrix();
  GLUquadric *head = gluNewQuadric();
  gluQuadricDrawStyle(head, GLU_FILL);
  gluQuadricTexture(head, GL_TRUE);

  glRotatef(-90, 1, 0, 0);
  glRotatef(90, 0, 0, 1);
  glRotatef(2 * _angle, 0, 0, 1);

  gluSphere(head, radius, 40, 40);
  gluDeleteQuadric(head);
  glPopMatrix();

  // bind to default texture and delete texture
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &face);

  // draw body
  glPushMatrix();
  glTranslatef(0, -2 * radius, 0);
  this->body();
  glPopMatrix();

  // draw map
  glPushMatrix();
  glTranslatef(_direction * -2 * radius, -2 * radius, 0);
  glRotatef(_direction * 90, 0, 1, 0);
  glRotatef(-_angle, 0, 0, 1);
  this->map();
  glPopMatrix();

  glEnable(GL_LIGHTING);
}

// create a petal
void SceneWidget::petal(){
  materialStruct* material = &red;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;

  glPushMatrix();
  glScalef(0.3, 0.2, 0.1);

  GLUquadric *ovoid = gluNewQuadric();
  gluQuadricDrawStyle(ovoid, GLU_FILL);
  gluSphere(ovoid, radius, 10, 10);
  gluDeleteQuadric(ovoid);
  glPopMatrix();
}

// create a flower
void SceneWidget::flower(){
  materialStruct* material = &yellow;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  float radius = 1;

  // draw flower's centre
  glPushMatrix();
  glScalef(0.3, 0.2, 0.3);

  GLUquadric *centre = gluNewQuadric();
  gluQuadricDrawStyle(centre, GLU_FILL);
  gluSphere(centre, radius, 10, 10);
  gluDeleteQuadric(centre);
  glPopMatrix();

  // draw petals around flower's centre
  for(int i = 0; i < 8 ; i++){
    glPushMatrix();
    glRotatef(i * 45, 0, 1, 0);
    glTranslatef(-0.5, 0, 0);
    this->petal();
    glPopMatrix();
  }
}

// create bouquet of flowers
void SceneWidget::bouquet(){
  materialStruct* material = &whiteShinyMaterials;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // draw base
  glPushMatrix();
  glTranslatef(0, 2, 0);
  glRotatef(90, 1, 0, 0);
  glutSolidCone(0.5, 2, 10, 10);
  glPopMatrix();

  // draw a flower, repeat
  glPushMatrix();
  glTranslatef(0, 2.25, 0.25);
  glRotatef(25, 1, 0, 0);
  glRotatef(5 * _angle, 0, 1, 0);
  glScalef(0.5, 0.5, 0.5);
  this->flower();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.25, 2.25, -0.25);
  glRotatef(25, 0, 0, 1);
  glRotatef(5 * _angle, 0, 1, 0);
  glScalef(0.5, 0.5, 0.5);
  this->flower();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25, 2.25, -0.25);
  glRotatef(-25, 0, 0, 1);
  glRotatef(5 * _angle, 0, 1, 0);
  glScalef(0.5, 0.5, 0.5);
  this->flower();
  glPopMatrix();
}

// create fog cube
void SceneWidget::fog(){
  // define normals for each face
  GLfloat normals[][3] = {{1, 0, 0},
                          {-1, 0, 0},
                          {0, 0, 1},
                          {0, 0, -1},
                          {0, 1, 0},
                          {0, -1, 0}};

  materialStruct* material = &grey;

  glMaterialfv(GL_FRONT, GL_AMBIENT, material->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, material->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, material->specular);
  glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);

  // assign normal for face and draw face, repeat for all faces
  glNormal3fv(normals[0]);
  glBegin(GL_POLYGON);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 0, -10);
  glVertex3f(10, 1, -10);
  glVertex3f(10, 1, 10);
  glEnd();

  glNormal3fv(normals[3]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, -10);
  glVertex3f(10, 0, -10);
  glVertex3f(10, 1, -10);
  glVertex3f(-10, 1, -10);
  glEnd();

  glNormal3fv(normals[2]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, 10);
  glVertex3f(10, 0, 10);
  glVertex3f(10, 1, 10);
  glVertex3f(-10, 1, 10);
  glEnd();

  glNormal3fv(normals[1]);
  glBegin(GL_POLYGON);
  glVertex3f(-10, 0, 10);
  glVertex3f(-10, 0, -10);
  glVertex3f(-10, 1, -10);
  glVertex3f(-10, 1, 10);
  glEnd();

  glNormal3fv(normals[4]);
  glBegin(GL_POLYGON);
  glVertex3f(10, 1, 10);
  glVertex3f(10, 1, -10);
  glVertex3f(-10, 1, -10);
  glVertex3f(-10, 1, 10);
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

// update angle of scene
void SceneWidget::updateAngle(){
  _angle += _speed;
  this->repaint();
}

// update direction of ghost
void SceneWidget::changeDirection(){
  _direction *= -1;
}

// update speed of ghost
void SceneWidget::updateSpeed(int value){
  _speed = (float) value/10;
}

// update alpha components of grey material
void SceneWidget::updateTransparency(int value){
  grey.ambient[3] = (float) value/100;
  grey.diffuse[3] = (float) value/100;
  grey.specular[3] = (float) value/100;
  this->repaint();
}

// update x coordinate of camera position
void SceneWidget::updateHorizontalView(int value){
  _xView = (float) value/100;
  this->repaint();
}

// update y coordinate of camera position
void SceneWidget::updateVerticalView(int value){
  _yView = (float) value/100;
  this->repaint();
}

// update red grave material component
void SceneWidget::updateRed(double value){
  graveMaterial.ambient[0] = value;
  graveMaterial.diffuse[0] = value;
}

// update green grave material component
void SceneWidget::updateGreen(double value){
  graveMaterial.ambient[1] = value;
  graveMaterial.diffuse[1] = value;
}

// update blue grave material component
void SceneWidget::updateBlue(double value){
  graveMaterial.ambient[2] = value;
  graveMaterial.diffuse[2] = value;
}

// paint widget
void SceneWidget::paintGL(){
	// clear widget
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// position light
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  GLfloat lightPosition[] = {-100, 200, 100, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	// glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,180.);
	glPopMatrix();

  // draw floor
	this->floor();

  glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();

  // draw open grave
  glPushMatrix();
  glTranslatef(0, 0, 1);
  this->openGrave();
  glPopMatrix();

  // draw gravestones
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

  // draw trees
  glPushMatrix();
  glTranslatef(8, 0, -8);
  this->tree();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-8, 0, -8);
  glRotatef(90, 0, 1, 0);
  this->tree();
  glPopMatrix();

  // draw ghost
  glPushMatrix();
  glRotatef(_direction * _angle, 0, 1, 0);
  glTranslatef(0, 10, -7);
  this->ghost();
  glPopMatrix();

  // draw flying bouquet
  glPushMatrix();
  glTranslatef(0, 8, 0);
  glRotatef(_angle, 0, 0, 1);
  glTranslatef(0, 2, -3);
  this->bouquet();
  glPopMatrix();

  // draw bouquets
  glPushMatrix();
  glTranslatef(8, 0, 1.5);
  glRotatef(45, 1, 0, 0);
  this->bouquet();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-8, 0, 1.5);
  glRotatef(45, 1, 0, 0);
  this->bouquet();
  glPopMatrix();

  // enable blending to allow fog to be transparent and draw fog
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  this->fog();

  glLoadIdentity();
  // set view position
  gluLookAt(_xView,_yView,1, 0,0,0, 0,1,0);

	// flush to screen
	glFlush();
}
