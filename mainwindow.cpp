#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_open_dir_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath());
    open_dir(fileName);

}
void MainWindow::open_dir(QString fileName){

    /*Mat img;
    img = imread(fileName.toUtf8().constData());
    cv::resize(img, img, Size(512, 384), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,COLOR_BGR2RGB); //Qt reads in RGB whereas CV in BGR
    //Converts the CV image into Qt standard format
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);*/

    /*QGraphicsScene scene;
    QGraphicsPixmapItem item(QPixmap::fromImage(imdisplay));
    scene.addItem(&item);
    ui->display_image->setScene(&scene);
    ui->display_image->show();
    */

    /*QGraphicsScene* scene = new QGraphicsScene();
    //QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(imdisplay));
    scene->addItem(item);
     ui->display_image->show();*/

    //ui->display_image->setPixmap(QPixmap::fromImage(imdisplay));//display the image in label that is created earlier



    imageObject = new QImage();
    imageObject->load(fileName);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->display_image->setScene(scene);


}




void MainWindow::on_save_image_clicked()
{
    QString imagePath = QFileDialog::getSaveFileName(
                    this,
                    tr("Save File"),
                    "",
                    tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                    );

    if(!image.toImage().isNull())
    {
        *imageObject = image.toImage();
        imageObject->save(imagePath);
    }
    else
    {
        QMessageBox::critical(
          this,
          tr("Image Processing Tool"),
          tr("No Image Save In The Image Viewer Windows") );
    }

}
