#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBrush>
#include <QColorDialog>
#include <QDir>
#include <QDragEnterEvent>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSettings>

#include "qgifimage.h"

extern "C" {
#include "../MyString.h"
#include "../abdujaffine.h"
#include "../parce.h"
#include "../stack.h"
}

#include "abduzhalilov3d.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  string extension(string filename);
  QString str;
  QSettings *settings;
  void saveSettings();
  void loadSettings();
  QGifImage *gifimage;
  QTimer *delay;
  QString *path_to_save_gif;
  int frame = 0;
  QString GetPath();

 protected:
  void dropEvent(QDropEvent *);
  void dragEnterEvent(QDragEnterEvent *);
  void dragMoveEvent(QDragMoveEvent *);
  void dragLeaveEvent(QDragLeaveEvent *);
  void closeEvent(QCloseEvent *);

 private slots:
  void on_DownloadButton_clicked();
  void on_ScaleButton_valueChanged(double arg1);
  void on_RotationXButton_valueChanged(double arg1);
  void on_RotationYButton_valueChanged(double arg1);
  void on_MoveXButton_valueChanged(double arg1);
  void on_MoveYButton_valueChanged(double arg1);
  void on_MoveZButton_valueChanged(double arg1);
  void on_RotationZButton_valueChanged(double arg1);
  void on_EdgeSizeButton_valueChanged(int value);
  void on_BackgroundColorButton_currentTextChanged(const QString &arg1);
  void on_EdgeColorButton_currentTextChanged(const QString &arg1);
  void on_EdgeTypeButton_currentTextChanged(const QString &arg1);
  void on_PeakColorButton_currentTextChanged(const QString &arg1);
  void on_PeakSizeButton_valueChanged(int value);
  void on_PeakColorType_currentTextChanged(const QString &arg1);
  void on_SaveButton_clicked();
  void on_ProjectionButton_currentIndexChanged(int index);
  void on_WriteGIFButton_clicked();
  void AddFrameGIF();
};
#endif  // MAINWINDOW_H
