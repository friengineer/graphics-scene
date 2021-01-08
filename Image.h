#ifndef _IMAGE_
#define _IMAGE_

#include <string>
#include <QImage>
#include <GL/glu.h>

// image
class Image {
  public:

  Image(const std::string& fn);
  ~Image();

  // image bytes
  const GLubyte* imageField() const;

  // methods to return width and height of image
  unsigned int Width() const {return _width;}
  unsigned int Height() const {return _height;}

  private:

  Image(const Image&);

  // width and height of image
  unsigned int _width;
  unsigned int _height;

  // global variables
  QImage* p_qimage;
  GLubyte* _image;
};

#endif
