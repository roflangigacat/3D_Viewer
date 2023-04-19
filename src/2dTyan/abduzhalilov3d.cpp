#include "abduzhalilov3d.h"

Abduzhalilov3D::Abduzhalilov3D(QWidget *parent) : QOpenGLWidget(parent) {
  vertex_array = nullptr;
  indexes_array = nullptr;
  vertex_array2 = nullptr;
  myScale = 1, myAngleX = 0, myAngleY = 0, myAngleZ = 0, myTranslate.x = 0,
  myTranslate.y = 0, myTranslate.z = 0, r_backgroundcolor = 0,
  g_backgroundcolor = 0, b_backgroundcolor = 0, r_edgecolor = 1,
  g_edgecolor = 1, b_edgecolor = 1, r_dotcolor = 1, g_dotcolor = 1,
  b_dotcolor = 1, dot_line = 0, dot_type = 0, type_project = 0, line_width = 0,
  peak_width = 0, ViewType = 0;
}

void Abduzhalilov3D::objOpen(QString path) {
  if (vertex_array != nullptr && indexes_array != nullptr) {
    free(vertex_array);
    free(indexes_array);
    free(vertex_array2);
  }
  Stack_t *Vnum = NULL;
  Stack_t *Fnum = NULL;
  xyz = VvalueConstruct();
  int len = 0, len2 = 0;
  parsingFile(path.toStdString().data(), &Vnum, &Fnum, &xyz);
  vertexcount = getStackSize(Vnum);
  Data *arr = getAllValue(&Vnum, &len);
  Data *arr2 = getAllValue(&Fnum, &len2);
  IndexesLength = len2;
  indexcount = len2;
  vertex_array = getDataDouble(arr, len);
  vertex_array2 = getDataDouble(arr, len);
  indexes_array = getDataInt(arr2, len2);
  free(arr);
  free(arr2);
  StackDelete(&Vnum);
  StackDelete(&Fnum);
  update();
}

void Abduzhalilov3D::myGlScaled(double scale) { myScale = scale; }

void Abduzhalilov3D::myGlTranslatedX(double translateX) {
  myTranslate.x = translateX;
}

void Abduzhalilov3D::myGlTranslateY(double translateY) {
  myTranslate.y = translateY;
}

void Abduzhalilov3D::myGlTranslateZ(double translateZ) {
  myTranslate.z = translateZ;
}

void Abduzhalilov3D::myRotateX(double rotateX) { myAngleX = rotateX; }

void Abduzhalilov3D::myRotateY(double rotateY) { myAngleY = rotateY; }

void Abduzhalilov3D::myRotateZ(double rotateZ) { myAngleZ = rotateZ; }

void Abduzhalilov3D::ChangeLineWidth(double x) {
  line_width = x;
  update();
}

void Abduzhalilov3D::ChangePeakWidth(double x) {
  peak_width = x;
  update();
}

void Abduzhalilov3D::ChangeBackground(double x, double y, double z) {
  r_backgroundcolor = x;
  g_backgroundcolor = y;
  b_backgroundcolor = z;
  update();
}

void Abduzhalilov3D::CentralOrParallel(int variaty) { ViewType = variaty; }

void Abduzhalilov3D::ChangeEdgeColor(double x, double y, double z) {
  r_edgecolor = x;
  g_edgecolor = y;
  b_edgecolor = z;
  update();
}

void Abduzhalilov3D::ChangeDotColor(double x, double y, double z) {
  r_dotcolor = x;
  g_dotcolor = y;
  b_dotcolor = z;
  update();
}

void Abduzhalilov3D::ChangeTypeEdge(int m) {
  dot_line = m;
  update();
}

void Abduzhalilov3D::ChangeTypeDot(int n) {
  dot_type = n;
  update();
}

void Abduzhalilov3D::ChangeTypeProject(int p) {
  type_project = p;
  update();
}

void Abduzhalilov3D::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Abduzhalilov3D::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double first = -(double(this->height()) / double(this->width()));
  double second = double(this->height()) / double(this->width());
  double near = tan(10.0 * M_PI / 180.0 / 2);
  glOrtho(-1, 1, first, second, near, 999999999999);
}

void Abduzhalilov3D::paintGL() {
  glClearColor(r_backgroundcolor, g_backgroundcolor, b_backgroundcolor, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  if (indexes_array && vertex_array) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(10);
    glPointSize(peak_width);

    if (vertexcount > 999999) {
      myTranslate.y = -2;
      myTranslate.z = xyz.Z.Min * 3;
    }
    if (xyz.Z.Min > -50 && vertexcount < 999999) {
      myTranslate.z = xyz.Z.Min * 5;
    }
    if (xyz.Z.Min < -100) {
      myTranslate.z = xyz.Z.Min * 10;
    }
    if (xyz.Z.Min < -500) {
      myTranslate.z = xyz.Z.Min * 3;
    }
    float heapHeight = 1.0 / (tan(10.0 * M_PI / 180.0 / 2.0));
    double l = -(double(this->width()) / double(this->height())),
           r = double(this->width()) / double(this->height());
    if (ViewType == 0) {
      glFrustum(l, r, l, r, heapHeight, 999999999999);
    }
    AbduzhalilTransformations(vertex_array, vertex_array2, vertexcount, myScale,
                              myAngleX, myAngleY, myAngleZ, myTranslate);
    glVertexPointer(3, GL_DOUBLE, 0, vertex_array2);
    if (dot_line == 1) {
      glLineStipple(2, 0x00F0);
      glEnable(GL_LINE_STIPPLE);
    } else {
      glDisable(GL_LINE_STIPPLE);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glLineWidth(line_width);
    glColor3d(r_dotcolor, g_dotcolor, b_dotcolor);
    if (dot_type == 2) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, vertexcount);
      glDisable(GL_POINT_SMOOTH);
    } else if (dot_type == 1) {
      glDrawArrays(GL_POINTS, 0, vertexcount);
    }
    glColor3d(r_edgecolor, g_edgecolor, b_edgecolor);
    glDrawElements(GL_LINES, IndexesLength, GL_UNSIGNED_INT, indexes_array);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void Abduzhalilov3D::mousePressEvent(QMouseEvent *mo) {
  if (mo->buttons() == Qt::LeftButton) {
    mPos = mo->pos();
  }
  mo->accept();
}

void Abduzhalilov3D::mouseMoveEvent(QMouseEvent *mo) {
  if (mo->buttons() != Qt::LeftButton) return;
  myAngleX += 0.05 / M_PI * (mo->pos().y() - mPos.y());
  myAngleY += 0.05 / M_PI * (mo->pos().x() - mPos.x());
  mPos = mo->pos();
  update();
}

void Abduzhalilov3D::wheelEvent(QWheelEvent *scr) {
  if (scr->angleDelta().y() > 0) {
    myScale += 0.01;
  } else if (scr->angleDelta().y() < 0) {
    myScale -= 0.01;
  }
  update();
}
