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

    prevBW = ui->checkBox_bw->isChecked();
    prevLevel = ui->doubleSpinBox_level->value();
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

        refreshImages();
        resetUI();

        processImage(image);

    }
}

void MainWindow::on_verticalSlider_zoom_valueChanged(int value)
{
    float valueF = value;
    float delta = (valueF / 100 - scale) + 2;
    scale += delta - 1;

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
    prevLevel = ui->doubleSpinBox_level->value();
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
    ui->doubleSpinBox_level->setEnabled(true);
    ui->label_amount->setEnabled(true);
    ui->textEdit_amount->setEnabled(true);
}

void MainWindow::processImage(QImage image)
{
    QPixmap imagePM;
    if (ui->checkBox_bw->isChecked())
        imagePM = convertPictureToBw(image);
    else
        imagePM = QPixmap::fromImage(image);

    float oneThird = image.width() / 3;
    Node first(QPointF(0, 0), QPointF(image.width(), oneThird));
    Node second(QPointF(0, oneThird), QPointF(image.width(), 2 * oneThird));
    Node third(QPointF(0, 2 * oneThird), QPointF(image.width(), image.height()));

    TriangleMaker tm(imagePM.toImage());

    int amount = 0;

    amount += processNode(&first, tm, ui->doubleSpinBox_level->value() * 100);
    amount += processNode(&second, tm, ui->doubleSpinBox_level->value() * 100);
    amount += processNode(&third, tm, ui->doubleSpinBox_level->value() * 100);

    ui->textEdit_amount->clear();
    ui->textEdit_amount->setText(QString::number(amount));

    drawNode(&first);
    drawNode(&second);
    drawNode(&third);


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
}

int MainWindow::processNode(Node *current, TriangleMaker tm, float norm)
{

    tm.getColors(current->topLeft, current->bottomRight);
    float area = findArea(*current);
    int output = 0;
    if (tm.acceptable(norm) || area <= ui->spinBox_size->value())
    {
        output++;
        current->color = tm.averageColor();
    }
    else
    {
        if ((current->bottomRight.y() - current->topLeft.y()) > (current->bottomRight.x() - current->topLeft.x())) // vertical ractangle
        {
            float onethird = (current->bottomRight.y() - current->topLeft.y()) / 3;

            current->first = new Node(current->topLeft, QPointF(current->bottomRight.x(), current->topLeft.y() + onethird));
            current->second = new Node(QPointF(current->topLeft.x(), current->topLeft.y() + onethird), QPointF(current->bottomRight.x(), current->topLeft.y() + 2 * onethird));
            current->third = new Node(QPointF(current->topLeft.x(), current->topLeft.y() + 2 * onethird), current->bottomRight);
        }
        else // horizontal rectangle
        {
            float onethird = (current->bottomRight.x() - current->topLeft.x()) / 3;

            current->first = new Node(QPointF(current->topLeft.x() + 2 * onethird, current->topLeft.y()), current->bottomRight);
            current->second = new Node(QPointF(current->topLeft.x() + onethird, current->topLeft.y()), QPointF(current->bottomRight.x() - onethird, current->bottomRight.y()));
            current->third = new Node(current->topLeft, QPointF(current->topLeft.x() + onethird, current->bottomRight.y()));
        }
        output += processNode(current->first, tm, ui->doubleSpinBox_level->value() * 100);
        output += processNode(current->second, tm, ui->doubleSpinBox_level->value() * 100);
        output += processNode(current->third, tm, ui->doubleSpinBox_level->value() * 100);
    }
    return output;
}

float MainWindow::findArea(Node rectangle)
{
    float a = rectangle.bottomRight.x() - rectangle.topLeft.x();
    float b = rectangle.bottomRight.y() - rectangle.topLeft.y();
    float area = a * b;
    return area;
}

void MainWindow::drawNode(Node *current)
{
    if (current->first != nullptr && current->second != nullptr)
    {
        drawNode(current->first);
        drawNode(current->second);
        drawNode(current->third);
        return;
    }

    QPolygonF temp;
    temp.append(current->topLeft);
    temp.append(QPointF(current->bottomRight.x(), current->topLeft.y()));
    temp.append(current->bottomRight);
    temp.append(QPointF(current->topLeft.x(), current->bottomRight.y()));
    QBrush regularBrush(current->color);
    QPen invisiblePen(Qt::transparent);
    recoveredScene->addPolygon(temp, invisiblePen, regularBrush);

    QBrush whiteBrush(Qt::darkGray);
    QPen pen(Qt::red);
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
        ui->doubleSpinBox_level->setValue(prevLevel);
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

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{

}

void MainWindow::on_doubleSpinBox_level_valueChanged(double arg1)
{
    if (arg1 != curLevel)
    {
        ui->pushButton_undo->setEnabled(true);

        prevLevel = curLevel;
        curLevel = arg1;
        prevSize = curSize;
        prevBW = ui->checkBox_bw->isChecked();

        QImage original(fileName);
        original = original.scaled(256, 256);
        processImage(original);
    }
}
