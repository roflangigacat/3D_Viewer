#include "mainwindow.h"

#include <QDebug>
#include <QMimeData>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  loadSettings();
  this->setAcceptDrops(true);
  this->setWindowTitle("3dViewer");
}

MainWindow::~MainWindow() {
  if (ui->SaveSettings->isChecked()) {
    saveSettings();
  }
  delete ui;
}

string MainWindow::extension(string filename) {
  int position = filename.find_last_of(".");
  string result = filename.substr(position + 1);
  return result;
}

void MainWindow::dropEvent(QDropEvent *p_event) {
  const QMimeData *mime(p_event->mimeData());
  QString stroka;
  for (int i = 0; i < mime->urls().size(); i++) {
    stroka = mime->urls().at(i).toString().replace("file://", "");
  }
  if (extension(stroka.toUtf8().constData()) == "obj") {
    ui->GLWidget->objOpen(stroka);
    ui->CountOfVertexes->setText(
        QString::number(ui->GLWidget->GetVertexCount()));
    ui->CountOfFacets->setText(QString::number(ui->GLWidget->GetIndexCount()));
    ui->FileName->setText(
        stroka.right(stroka.size() - stroka.lastIndexOf("/") - 1));
    ui->ErrorLabel->setText("");
  } else {
    ui->ErrorLabel->setText("Invalid file type. Needed: .obj");
  }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *p_event) {
  p_event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *p_event) {
  p_event->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *p_event) { p_event->accept(); }

void MainWindow::closeEvent(QCloseEvent *event) {
  if (ui->SaveSettings->isChecked()) {
    QMessageBox::information(this, tr("Сохранение настроек"),
                             tr("Сохранение настроек выполнено успешно"));
  }
}

void MainWindow::on_DownloadButton_clicked() {
  QString HomeDir = QDir::homePath();
  str = QFileDialog::getOpenFileName(this, "Choose file", HomeDir,
                                     "obj. files (*.obj)");
  ui->GLWidget->objOpen(str);
  ui->CountOfVertexes->setText(QString::number(ui->GLWidget->GetVertexCount()));
  ui->CountOfFacets->setText(QString::number(ui->GLWidget->GetIndexCount()));
  ui->FileName->setText(str.right(str.size() - str.lastIndexOf("/") - 1));
}

void MainWindow::on_ScaleButton_valueChanged(double arg1) {
  ui->GLWidget->myGlScaled(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_RotationXButton_valueChanged(double arg1) {
  ui->GLWidget->myRotateX(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_RotationYButton_valueChanged(double arg1) {
  ui->GLWidget->myRotateY(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_MoveXButton_valueChanged(double arg1) {
  ui->GLWidget->myGlTranslatedX(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_MoveYButton_valueChanged(double arg1) {
  ui->GLWidget->myGlTranslateY(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_MoveZButton_valueChanged(double arg1) {
  ui->GLWidget->myGlTranslateZ(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_RotationZButton_valueChanged(double arg1) {
  ui->GLWidget->myRotateZ(arg1);
  ui->GLWidget->update();
}

void MainWindow::on_EdgeSizeButton_valueChanged(int value) {
  ui->GLWidget->ChangeLineWidth(value);
  update();
}

void MainWindow::on_PeakSizeButton_valueChanged(int value) {
  ui->GLWidget->ChangePeakWidth(value);
  update();
}

void MainWindow::on_BackgroundColorButton_currentTextChanged(
    const QString &arg1) {
  if (arg1 == "Черный") {
    ui->GLWidget->ChangeBackground(0, 0, 0);
  } else if (arg1 == "Красный") {
    ui->GLWidget->ChangeBackground(1, 0, 0);
  } else if (arg1 == "Зеленый") {
    ui->GLWidget->ChangeBackground(0, 1, 0);
  } else if (arg1 == "Синий") {
    ui->GLWidget->ChangeBackground(0, 0, 1);
  } else if (arg1 == "Белый") {
    ui->GLWidget->ChangeBackground(1, 1, 1);
  } else if (arg1 == "Желтый") {
    ui->GLWidget->ChangeBackground(1, 1, 0);
  } else if (arg1 == "Голубой") {
    ui->GLWidget->ChangeBackground(0, 0.75, 1);
  } else if (arg1 == "Фиолетовый") {
    ui->GLWidget->ChangeBackground(0.54, 0, 1);
  } else if (arg1 == "Розовый") {
    ui->GLWidget->ChangeBackground(1, 0.75, 0.79);
  } else if (arg1 == "Оранжевый") {
    ui->GLWidget->ChangeBackground(1, 0.4, 0);
  } else if (arg1 == "Бордовый") {
    ui->GLWidget->ChangeBackground(0.5, 0, 0);
  } else if (arg1 == "Серый") {
    ui->GLWidget->ChangeBackground(0.5, 0.5, 0.5);
  } else if (arg1 == "Кобальтовый") {
    ui->GLWidget->ChangeBackground(0, 0.08, 0.66);
  } else if (arg1 == "Веронский") {
    ui->GLWidget->ChangeBackground(0.46, 0.86, 0.46);
  } else if (arg1 == "Морской волны") {
    ui->GLWidget->ChangeBackground(0, 1, 1);
  } else if (arg1 == "Сольферино") {
    ui->GLWidget->ChangeBackground(0.98, 0.06, 0.75);
  }
  update();
}

void MainWindow::on_EdgeColorButton_currentTextChanged(const QString &arg1) {
  if (arg1 == "Белые") {
    ui->GLWidget->ChangeEdgeColor(1, 1, 1);
  } else if (arg1 == "Черные") {
    ui->GLWidget->ChangeEdgeColor(0, 0, 0);
  } else if (arg1 == "Красные") {
    ui->GLWidget->ChangeEdgeColor(1, 0, 0);
  } else if (arg1 == "Зеленые") {
    ui->GLWidget->ChangeEdgeColor(0, 1, 0);
  } else if (arg1 == "Синие") {
    ui->GLWidget->ChangeEdgeColor(0, 0, 1);
  } else if (arg1 == "Желтые") {
    ui->GLWidget->ChangeEdgeColor(1, 1, 0);
  } else if (arg1 == "Голубые") {
    ui->GLWidget->ChangeEdgeColor(0, 0.75, 1);
  } else if (arg1 == "Фиолетовые") {
    ui->GLWidget->ChangeEdgeColor(0.54, 0, 1);
  } else if (arg1 == "Розовые") {
    ui->GLWidget->ChangeEdgeColor(1, 0.75, 0.79);
  } else if (arg1 == "Оранжевые") {
    ui->GLWidget->ChangeEdgeColor(1, 0.4, 0);
  } else if (arg1 == "Бордовые") {
    ui->GLWidget->ChangeEdgeColor(0.5, 0, 0);
  } else if (arg1 == "Серые") {
    ui->GLWidget->ChangeEdgeColor(0.5, 0.5, 0.5);
  } else if (arg1 == "Кобальтовые") {
    ui->GLWidget->ChangeEdgeColor(0, 0.08, 0.66);
  } else if (arg1 == "Веронские") {
    ui->GLWidget->ChangeEdgeColor(0.46, 0.86, 0.46);
  } else if (arg1 == "Морской волны") {
    ui->GLWidget->ChangeEdgeColor(0, 1, 1);
  } else if (arg1 == "Сольферино") {
    ui->GLWidget->ChangeEdgeColor(0.98, 0.06, 0.75);
  }
}

void MainWindow::on_EdgeTypeButton_currentTextChanged(const QString &arg1) {
  if (arg1 == "Пунктирная") {
    ui->GLWidget->ChangeTypeEdge(1);
  } else if (arg1 == "Сплошная") {
    ui->GLWidget->ChangeTypeEdge(0);
  }
}

void MainWindow::on_PeakColorButton_currentTextChanged(const QString &arg1) {
  if (arg1 == "Белые") {
    ui->GLWidget->ChangeDotColor(1, 1, 1);
  } else if (arg1 == "Черные") {
    ui->GLWidget->ChangeDotColor(0, 0, 0);
  } else if (arg1 == "Красные") {
    ui->GLWidget->ChangeDotColor(1, 0, 0);
  } else if (arg1 == "Зеленые") {
    ui->GLWidget->ChangeDotColor(0, 1, 0);
  } else if (arg1 == "Синие") {
    ui->GLWidget->ChangeDotColor(0, 0, 1);
  } else if (arg1 == "Желтые") {
    ui->GLWidget->ChangeDotColor(1, 1, 0);
  } else if (arg1 == "Голубые") {
    ui->GLWidget->ChangeDotColor(0, 0.75, 1);
  } else if (arg1 == "Фиолетовые") {
    ui->GLWidget->ChangeDotColor(0.54, 0, 1);
  } else if (arg1 == "Розовые") {
    ui->GLWidget->ChangeDotColor(1, 0.75, 0.79);
  } else if (arg1 == "Оранжевые") {
    ui->GLWidget->ChangeDotColor(1, 0.4, 0);
  } else if (arg1 == "Бордовые") {
    ui->GLWidget->ChangeDotColor(0.5, 0, 0);
  } else if (arg1 == "Серые") {
    ui->GLWidget->ChangeDotColor(0.5, 0.5, 0.5);
  } else if (arg1 == "Кобальтовые") {
    ui->GLWidget->ChangeDotColor(0, 0.08, 0.66);
  } else if (arg1 == "Веронские") {
    ui->GLWidget->ChangeDotColor(0.46, 0.86, 0.46);
  } else if (arg1 == "Морской волны") {
    ui->GLWidget->ChangeDotColor(0, 1, 1);
  } else if (arg1 == "Сольферино") {
    ui->GLWidget->ChangeDotColor(0.98, 0.06, 0.75);
  }
}

void MainWindow::on_PeakColorType_currentTextChanged(const QString &arg1) {
  if (arg1 == "Круг") {
    ui->GLWidget->ChangeTypeDot(2);
  } else if (arg1 == "Квадрат") {
    ui->GLWidget->ChangeTypeDot(1);
  } else if (arg1 == "Отсутствует") {
    ui->GLWidget->ChangeTypeDot(0);
  }
}

void MainWindow::on_SaveButton_clicked() {
  QString file = QFileDialog::getSaveFileName(
      this, "Save as...", "3DViewer_picture", "BMP, JPEG (*.jpg *.jpeg *.bmp)");
  ui->GLWidget->grabFramebuffer().save(file);
}

void MainWindow::on_ProjectionButton_currentIndexChanged(int index) {
  if (ui->ProjectionButton->currentIndex() == 1) {
    ui->GLWidget->CentralOrParallel(1);
  } else if (ui->ProjectionButton->currentIndex() == 0) {
    ui->GLWidget->CentralOrParallel(0);
  }
  ui->GLWidget->update();
}

void MainWindow::saveSettings() {
  QSettings settings("School21", "Viewer3D");
  settings.beginGroup("Main");
  settings.setValue("ScaleModel", ui->ScaleButton->value());
  settings.setValue("TranslateX", ui->MoveXButton->value());
  settings.setValue("TranslateY", ui->MoveYButton->value());
  settings.setValue("TranslateZ", ui->MoveZButton->value());
  settings.setValue("RotateX", ui->RotationXButton->value());
  settings.setValue("RotateY", ui->RotationYButton->value());
  settings.setValue("RotateZ", ui->RotationZButton->value());
  settings.setValue("SizePoint", ui->PeakSizeButton->value());
  settings.setValue("SizeLine", ui->EdgeSizeButton->value());
  settings.setValue("PointType", ui->PeakColorType->currentIndex());
  settings.setValue("LineType", ui->EdgeTypeButton->currentIndex());
  settings.setValue("Projection", ui->ProjectionButton->currentIndex());
  settings.setValue("BackgraundColor",
                    ui->BackgroundColorButton->currentIndex());
  settings.setValue("LineColor", ui->EdgeColorButton->currentIndex());
  settings.setValue("PointColor", ui->PeakColorButton->currentIndex());
  settings.endGroup();
}

void MainWindow::loadSettings() {
  QSettings settings("School21", "Viewer3D");
  settings.beginGroup("Main");
  ui->ScaleButton->setValue(settings.value("ScaleModel").toDouble());
  ui->MoveXButton->setValue(settings.value("TranslateX").toDouble());
  ui->MoveYButton->setValue(settings.value("TranslateY").toDouble());
  ui->MoveZButton->setValue(settings.value("TranslateZ").toDouble());
  ui->RotationXButton->setValue(settings.value("RotateX").toDouble());
  ui->RotationYButton->setValue(settings.value("RotateY").toDouble());
  ui->RotationZButton->setValue(settings.value("RotateZ").toDouble());
  ui->PeakSizeButton->setValue(settings.value("SizePoint").toInt());
  ui->EdgeSizeButton->setValue(settings.value("SizeLine").toInt());
  ui->PeakColorType->setCurrentIndex(settings.value("PointType").toInt());
  ui->EdgeTypeButton->setCurrentIndex(settings.value("LineType").toInt());
  ui->ProjectionButton->setCurrentIndex(settings.value("Projection").toInt());
  ui->BackgroundColorButton->setCurrentIndex(
      settings.value("BackgraundColor").toInt());
  ui->EdgeColorButton->setCurrentIndex(settings.value("LineColor").toInt());
  ui->PeakColorButton->setCurrentIndex(settings.value("PointColor").toInt());
  settings.endGroup();
}

QString MainWindow::GetPath() {
  return QFileDialog::getExistingDirectory(
      ui->GLWidget, tr("Choose files"), QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_WriteGIFButton_clicked() {
  ui->WriteGIFButton->setDisabled(true);
  ui->WriteGIFButton->setText("Идет запись...");
  gifimage = new QGifImage();
  frame = 0;
  delay = new QTimer(this);
  connect(delay, SIGNAL(timeout()), this, SLOT(AddFrameGIF()));
  delay->start(100);
}

void MainWindow::AddFrameGIF() {
  frame++;
  gifimage->addFrame(ui->GLWidget->grabFramebuffer(), 100);
  if (frame == 50) {
    delay->stop();
    gifimage->save(GetPath() + "/mygif" + QTime::currentTime().toString() +
                   ".gif");
    delete gifimage;
    ui->WriteGIFButton->setEnabled(true);
    ui->WriteGIFButton->setText("Записать GIF");
  }
}
