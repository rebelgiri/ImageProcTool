#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QDir"
#include "QGraphicsPixmapItem"
#include "QTimer"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\core\core.hpp"
using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open_dir(QString fileName);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_open_dir_clicked();
    void on_save_image_clicked();

private:
    Ui::MainWindow *ui;
    //QImage imdisplay;  //This will create QImage which is shown in Qt label
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;

};
#endif // MAINWINDOW_H
