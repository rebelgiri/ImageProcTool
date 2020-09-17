#include "mainwindow.h"

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
    ui->display_image->setMouseTracking(true);
    scene->installEventFilter(this);


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

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() ==  QEvent::GraphicsSceneMouseMove ) {
    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    QPointF img_coord_pt = mouseEvent->scenePos();

    double x = img_coord_pt.x();
    double y = img_coord_pt.y();

    //QColor color = QColor(image.toImage().pixel(x,y));
    //int average = (color.red()+color.green()+color.blue())/3;

    ui->lineEdit->setText(QString::number(x));
    ui->lineEdit_2->setText(QString::number(y));
   // ui->label_Value->setText(QString::number(average));

    return true;
  } else {
    return QObject::eventFilter(obj, event);
  }
}
