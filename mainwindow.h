#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QToolTip>
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
#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>




using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void open_dir();
    bool eventFilter(QObject *obj, QEvent *event);
    void display_colors_on_text_edit_hsv_lab();
    void display_colors_on_text_edit_rgb_hsv();
    void display_colors_on_text_edit_rgb_lab();

private slots:
    void on_open_dir_clicked();
    void on_save_image_clicked();

    void on_pushButton_clicked();

    void on_rgb_color_values_returnPressed();

    void on_hsv_color_values_returnPressed();

    void on_lab_color_values_returnPressed();

private:
    Ui::MainWindow *ui;
    //QImage imdisplay;  //This will create QImage which is shown in Qt label
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    QString fileName;

};
#endif // MAINWINDOW_H
