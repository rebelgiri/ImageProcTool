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
    fileName = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath());
    open_dir();

}
void MainWindow::open_dir(){

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
    QPoint img_coord_pt_const = mouseEvent->screenPos();

    double x = img_coord_pt.x();
    double y = img_coord_pt.y();


    //QColor color = QColor(image.toImage().pixel(x,y));
    //int average = (color.red()+color.green()+color.blue())/3;

    //ui->lineEdit->setText(QString::number(x));
    //ui->lineEdit_2->setText(QString::number(y));
   // ui->label_Value->setText(QString::number(average));

    // RGB Color
    QRgb rgbValue = image.toImage().pixel(x,y);
    QString rgbValueToDisply = QString::number(qRed(rgbValue)) + " " +
                               QString::number(qGreen(rgbValue)) + " " +
                               QString::number(qBlue(rgbValue)) ;

    /*ui->rgb_color_values->setText(rgbValueToDisply);*/

    QToolTip::showText(img_coord_pt_const,rgbValueToDisply,this,rect());

    /*
    // HSV Color
    QString hsvValueToDisply = QString::number(color.hue()) + " " +
                               QString::number(color.saturation())+ " " +
                               QString::number(color.value()) ;
     ui->hsv_color_values->setText(hsvValueToDisply);*/

     // LAB Color Conversion

    return true;
  } else {
    return QObject::eventFilter(obj, event);
  }
}

void MainWindow::on_pushButton_clicked()
{
    // Save all the entries in CSV file

    QString csvFileName = "color_values.csv";

    /*QString csvFilePath = QFileDialog::getSaveFileName(
                    this,
                    tr("Save File"),
                    "",
                    tr("CSV (*.csv)" )
                    );*/



    QFile file(csvFileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        // We're going to streaming text to the file
        QTextStream stream(&file);

        stream << ui->rgb_color_values->text() << "," << ui->hsv_color_values->text()
               << "," << ui->lab_color_values->text() << "\n";



        file.close();

        QMessageBox::information(this, tr("Image Processing Tool"), tr("CVS File Saved"));
    }

}

void MainWindow::on_rgb_color_values_returnPressed()
{
    display_colors_on_text_edit_hsv_lab();
}

void MainWindow::on_hsv_color_values_returnPressed()
{
    display_colors_on_text_edit_rgb_lab();
}

void MainWindow::on_lab_color_values_returnPressed()
{
    display_colors_on_text_edit_rgb_hsv();
}

void MainWindow::display_colors_on_text_edit_hsv_lab()
{
    QString RGBValue = ui->rgb_color_values->text();

    const QRegExp rx(QLatin1Literal("[^0-9]+"));
    const auto&& parts = RGBValue.split(rx, QString::SkipEmptyParts);

    float r = parts[0].toInt() / 255.0f;
    float g = parts[1].toInt() / 255.0f;
    float b = parts[2].toInt() / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = max_f(r, g, b);
    float min = min_f(r, g, b);

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    unsigned char dst_h = (unsigned char)(h / 2);   // dst_h : 0-180
    unsigned char dst_s = (unsigned char)(s * 255); // dst_s : 0-255
    unsigned char dst_v = (unsigned char)(v * 255); // dst_v : 0-255

    QString hsvValueToDisply = QString::number(dst_h) + " " +
                               QString::number(dst_s) + " " +
                               QString::number(dst_v) ;

    ui->hsv_color_values->setText(hsvValueToDisply);

}
void MainWindow::display_colors_on_text_edit_rgb_hsv()
{

}
void MainWindow::display_colors_on_text_edit_rgb_lab()
{


}
