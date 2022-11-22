#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Trianglemaker.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    originalScene = new QGraphicsScene(this);
    ui->graphicsView_original->setScene(originalScene);
    ui->graphicsView_original->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView_original->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    processedScene = new QGraphicsScene(this);
    ui->graphicsView_processed->setScene(processedScene);
    ui->graphicsView_processed->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView_processed->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    recoveredScene = new QGraphicsScene(this);
    ui->graphicsView_recovered->setScene(recoveredScene);
    ui->graphicsView_recovered->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView_recovered->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(ui->graphicsView_original->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_processed->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_processed->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_original->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_original->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_processed->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_processed->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_original->verticalScrollBar(), SLOT(setValue(int)));

    connect(ui->graphicsView_original->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_recovered->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_recovered->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_original->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_original->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_recovered->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphicsView_recovered->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->graphicsView_original->verticalScrollBar(), SLOT(setValue(int)));

    scale = 1;

    ui->lineEdit_zoom->setText(QString::number(scale));

    prevBW = ui->checkBox_bw->isChecked();
    ui->lineEdit_level->setText(QString::number(ui->horizontalSlider_level->value()) + "%");
    prevLevel = ui->horizontalSlider_level->value();
    curLevel = prevLevel;
    prevSize = ui->spinBox_size->value();
    curSize = prevSize;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_select_clicked()
{
    QString fileNameTemp = QFileDialog::getOpenFileName(this,"Open Image File",QDir::currentPath());

        if(!fileNameTemp.isEmpty())
        {
            QImage image(fileNameTemp);

            if(image.isNull())
            {
                QMessageBox::information(this,"Error","Error Displaying image");
                return;
            }
            fileName = fileNameTemp;

            image = image.scaled(256, 256);

            photoOriginal = QPixmap::fromImage(image);
            //photoProcessed = QPixmap::fromImage(image);
            //photoRecovered = QPixmap::fromImage(image);

            refreshImages();
            resetUI();

            QFile file(fileName);
            float size = file.size() / 1024;
            ui->lineEdit_original->setText(QString::number(size) + " KB");

            processImage(image);

            //ui->lineEdit_processed->setText(QString::number(size) + " KB"); // temp
            //ui->lineEdit_recovered->setText(QString::number(size) + " KB"); // temp

            QFileInfo fi(fileName);
            fileFormat = fi.suffix();
            ui->lineEdit_format->setText(fileFormat);

        }
}

void MainWindow::on_verticalSlider_zoom_valueChanged(int value)
{
    float valueF = value;
    float delta = (valueF / 100 - scale) + 2;
    scale += delta - 1;
    ui->lineEdit_zoom->setText(QString::number(scale));

    resetScale();

    ui->graphicsView_original->scale(scale, scale);
    ui->graphicsView_processed->scale(scale, scale);
    ui->graphicsView_recovered->scale(scale, scale);
}

void MainWindow::refreshImages()
{
    originalScene->clear();
    processedScene->clear();
    recoveredScene->clear();
    QGraphicsPixmapItem* item1 = new QGraphicsPixmapItem(photoOriginal);
    //QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(photoProcessed);
    //QGraphicsPixmapItem* item3 = new QGraphicsPixmapItem(photoRecovered);
    originalScene->addItem(item1);
    //processedScene->addItem(item2);
    //recoveredScene->addItem(item3);
    QRectF rect = originalScene->itemsBoundingRect();
    originalScene->setSceneRect(rect);
    processedScene->setSceneRect(rect);
    recoveredScene->setSceneRect(rect);
}

void MainWindow::resetScale()
{
    ui->graphicsView_original->resetTransform();
    ui->graphicsView_processed->resetTransform();
    ui->graphicsView_recovered->resetTransform();
}

QPixmap MainWindow::convertPictureToBw(QImage image)
{

    QSize sizeImage = image.size();
    int width = sizeImage.width(), height = sizeImage.height();

    for (int i=0; i < width; i++)
        for (int j=0; j < height; j++)
        {
            QRgb color = image.pixel(i,j);
            int gray = qGray(color);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    return QPixmap::fromImage(image);
}

void MainWindow::resetUI()
{
    prevBW = ui->checkBox_bw->checkState();
    prevLevel = ui->horizontalSlider_level->value();
    curLevel = prevLevel;
    prevSize = ui->spinBox_size->value();
    curSize = prevSize;
    ui->label_size->setEnabled(true);
    ui->spinBox_size->setEnabled(true);
    ui->pushButton_undo->setEnabled(false);
    prevBW = false;
    ui->checkBox_bw->setChecked(false);
    ui->checkBox_bw->setEnabled(true);
    ui->pushButton_undo->setEnabled(false);
    ui->label_zoom->setEnabled(true);
    ui->verticalSlider_zoom->setEnabled(true);
    ui->label_level->setEnabled(true);
    ui->horizontalSlider_level->setEnabled(true);
    ui->lineEdit_level->setEnabled(true);
    ui->lineEdit_zoom->setEnabled(true);
    ui->lineEdit_format->setEnabled(true);
    ui->label_format->setEnabled(true);
}

void MainWindow::processImage(QImage image)
{
    QPixmap imagePM;
    if (ui->checkBox_bw->isChecked())
        imagePM = convertPictureToBw(image);
    else
        imagePM = QPixmap::fromImage(image);

    Node left(QPointF(0, image.height()), QPointF(image.width(), image.height()), QPointF(0, 0));
    Node right(QPointF(image.width(), 0), left.angle2, left.angle1);

    TriangleMaker tm(imagePM.toImage());

    processNode(&left, tm, ui->horizontalSlider_level->value());
    processNode(&right, tm, ui->horizontalSlider_level->value());

    drawNode(&left);
    drawNode(&right);


    QString fileName = "cache.png";
    QPixmap pixMap =  ui->graphicsView_processed->grab(ui->graphicsView_processed->sceneRect().toRect());
    pixMap.save(fileName);
    processedScene->clear();
    QGraphicsPixmapItem* item1 = new QGraphicsPixmapItem(fileName);
    processedScene->addItem(item1);
    QRectF rect = processedScene->itemsBoundingRect();
    processedScene->setSceneRect(rect);
    QFile file(fileName);
    file.remove();

    pixMap =  ui->graphicsView_recovered->grab(ui->graphicsView_recovered->sceneRect().toRect());
    pixMap.save(fileName);
    recoveredScene->clear();
    QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(fileName);
    recoveredScene->addItem(item2);
    recoveredScene->setSceneRect(rect);
    file.remove();

    /*
    QFile file1(fileName);
    file1.open(QIODevice::WriteOnly);
    imagePM.save(&file1, "JPG", 90);
    float size = file1.size() / 1024;
    file1.remove();
    ui->lineEdit_recovered->setText(QString::number(size) + " KB");
    */


}

void MainWindow::processNode(Node *current, TriangleMaker tm, float norm)
{
    QPolygonF temp;
    temp.append(current->rightAngle);
    temp.append(current->angle1);
    temp.append(current->angle2);
    tm.getColors(temp);
    float area = findArea(*current);
    if (tm.acceptable(norm) || area <= ui->spinBox_size->value())
        current->color = tm.averageColor();
    else
    {
        QPointF newR = (current->angle1 + current->angle2) / 2; // midpoint
        current->first = new Node(newR, current->rightAngle, current->angle1);
        current->second = new Node(newR, current->angle2, current->rightAngle);
        processNode(current->first, tm, norm);
        processNode(current->second, tm, norm);
    }
    return;
}

float MainWindow::findArea(Node triangle)
{
    float x1 = triangle.angle1.x();
    float x2 = triangle.angle2.x();
    float x3 = triangle.rightAngle.x();
    float y1 = triangle.angle1.y();
    float y2 = triangle.angle2.y();
    float y3 = triangle.rightAngle.y();

    float area = 0.5 * qFabs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

    return area;
}

void MainWindow::drawNode(Node *current)
{
    if (current->first != nullptr && current->second != nullptr)
    {
        drawNode(current->first);
        drawNode(current->second);
        return;
    }

    QPolygonF temp;
    temp.append(current->rightAngle);
    temp.append(current->angle1);
    temp.append(current->angle2);
    QBrush regularBrush(current->color);
    QPen invisiblePen(Qt::transparent);
    recoveredScene->addPolygon(temp, invisiblePen, regularBrush);

    QBrush whiteBrush(Qt::white);
    QPen pen(Qt::green);
    pen.setWidth(1);
    processedScene->addPolygon(temp, pen, whiteBrush);
    return;
}

void MainWindow::on_checkBox_bw_stateChanged(int arg1)
{
    ui->pushButton_undo->setEnabled(true);
    prevBW = !ui->checkBox_bw->isChecked();

    prevLevel = curLevel;
    prevSize = curSize;
    QImage original(fileName);
    original = original.scaled(256, 256);
    processImage(original);
}

void MainWindow::on_horizontalSlider_level_valueChanged(int value)
{
    ui->lineEdit_level->setText(QString::number(ui->horizontalSlider_level->value()) + "%");
}

void MainWindow::on_horizontalSlider_level_sliderReleased()
{
    if (ui->horizontalSlider_level->value() != curLevel)
    {
        ui->pushButton_undo->setEnabled(true);

        prevLevel = curLevel;
        curLevel = ui->horizontalSlider_level->value();
        prevSize = curSize;
        prevBW = ui->checkBox_bw->isChecked();

        QImage original(fileName);
        original = original.scaled(256, 256);
        processImage(original);
    }


}

void MainWindow::on_pushButton_undo_clicked()
{
    if (prevBW != ui->checkBox_bw->isChecked())
    {
        ui->checkBox_bw->setChecked(prevBW);
        prevBW = ui->checkBox_bw->isChecked();
    }
    else if (curLevel != prevLevel)
    {
        curLevel = prevLevel;
        ui->horizontalSlider_level->setValue(prevLevel);
        QImage original(fileName);
        original = original.scaled(256, 256);
        processImage(original);
    }
    else if (curSize != prevSize)
    {
        curSize = prevSize;
        ui->spinBox_size->setValue(prevSize);
        QImage original(fileName);
        original = original.scaled(256, 256);
        processImage(original);
    }
    ui->pushButton_undo->setEnabled(false);
}

void MainWindow::on_spinBox_size_valueChanged(int arg1)
{
    if (ui->spinBox_size->value() != curSize)
    {
        ui->pushButton_undo->setEnabled(true);

        prevBW = ui->checkBox_bw->isChecked();
        prevLevel = curLevel;
        prevSize = curSize;
        curSize = arg1;
        QImage original(fileName);
        original = original.scaled(256, 256);
        processImage(original);
    }

}
