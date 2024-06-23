#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Trianglemaker.h"
#include <QMainWindow>
#include <QtMath>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_select_clicked();

    void on_verticalSlider_zoom_valueChanged(int value);

    void on_checkBox_bw_stateChanged(int arg1);

    void on_pushButton_undo_clicked();

    void on_spinBox_size_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_level_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;

    void refreshImages();
    void resetScale();
    QPixmap convertPictureToBw(QImage image);
    void resetUI();
    void processImage(QImage image);
    int processNode(Node *current, TriangleMaker tm, float norm);
    float findArea(Node triangle);
    void drawNode(Node *current);

    QString fileName;
    QString fileFormat;

    QGraphicsScene *originalScene;
    QGraphicsScene *processedScene;
    QGraphicsScene *recoveredScene;

    QPixmap photoOriginal;
    QPixmap photoProcessed;
    QPixmap photoRecovered;

    int prevLevel;
    int curLevel;
    int prevSize;
    int curSize;
    bool prevBW;

    float scale;

};
#endif // MAINWINDOW_H
