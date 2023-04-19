#ifndef ABDUZHALILOV3D_H
#define ABDUZHALILOV3D_H

#include <QDragEnterEvent>
#include <QFile>
#include <QFileDialog>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPoint>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QtMath>

extern "C" {
#include "../MyString.h"
#include "../abdujaffine.h"
#include "../parce.h"
#include "../stack.h"
}

class Abduzhalilov3D : public QOpenGLWidget {
 public:
  Abduzhalilov3D(QWidget *parent = nullptr);
  Abduzhalilov3D();
  void objOpen(QString path);
  void myGlScaled(double scale);
  void myGlTranslatedX(double translateX);
  void myGlTranslateY(double translateY);
  void myGlTranslateZ(double translateZ);
  void myRotateX(double rotateX);
  void myRotateY(double rotateY);
  void myRotateZ(double rotateZ);
  void ChangeLineWidth(double x);
  void ChangePeakWidth(double x);
  void ChangeEdgeColor(double x, double y, double z);
  void ChangeDotColor(double x, double y, double z);
  void ChangeTypeEdge(int m);
  void ChangeTypeDot(int n);
  void ChangeTypeProject(int p);
  void ChangeBackground(double x, double y, double z);
  void CentralOrParallel(int variaty);
  int GetVertexCount() { return vertexcount; }
  int GetIndexCount() { return indexcount; }
  int GetDotType() { return dot_line; }
  double *GetVertexes() { return vertex_array2; }
  double *GetInitialVertexes() { return vertex_array; }

 private:
  double r_backgroundcolor, g_backgroundcolor, b_backgroundcolor;
  double r_edgecolor, g_edgecolor, b_edgecolor;
  double r_dotcolor, g_dotcolor, b_dotcolor;
  int ViewType;
  int dot_line;
  int dot_type;
  int type_project;
  double line_width;
  double peak_width;
  double myScale, myAngleX, myAngleY, myAngleZ;
  translated_cooord myTranslate;
  int vertexcount, indexcount;
  Vvalue xyz;
  int IndexesLength;
  double *vertex_array, *vertex_array2;
  unsigned int *indexes_array;
  double xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *);
  void mouseMoveEvent(QMouseEvent *);
  void wheelEvent(QWheelEvent *);
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
};

#endif  // ABDUZHALILOV3D_H
