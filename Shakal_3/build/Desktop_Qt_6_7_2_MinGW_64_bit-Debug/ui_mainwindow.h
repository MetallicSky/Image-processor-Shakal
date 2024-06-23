/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView_processed;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_select;
    QCheckBox *checkBox_bw;
    QPushButton *pushButton_undo;
    QLabel *label_level;
    QDoubleSpinBox *doubleSpinBox_level;
    QLabel *label_zoom;
    QLabel *label_processed;
    QLabel *label_original;
    QLabel *label_recovered;
    QSlider *verticalSlider_zoom;
    QGraphicsView *graphicsView_original;
    QGraphicsView *graphicsView_recovered;
    QSpinBox *spinBox_size;
    QLabel *label_size;
    QTextEdit *textEdit_amount;
    QLabel *label_amount;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1095, 434);
        MainWindow->setMinimumSize(QSize(1095, 434));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView_processed = new QGraphicsView(centralwidget);
        graphicsView_processed->setObjectName("graphicsView_processed");
        graphicsView_processed->setGeometry(QRect(471, 30, 275, 275));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 136, 124));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_select = new QPushButton(verticalLayoutWidget);
        pushButton_select->setObjectName("pushButton_select");

        verticalLayout->addWidget(pushButton_select);

        checkBox_bw = new QCheckBox(verticalLayoutWidget);
        checkBox_bw->setObjectName("checkBox_bw");
        checkBox_bw->setEnabled(false);

        verticalLayout->addWidget(checkBox_bw);

        pushButton_undo = new QPushButton(verticalLayoutWidget);
        pushButton_undo->setObjectName("pushButton_undo");
        pushButton_undo->setEnabled(false);

        verticalLayout->addWidget(pushButton_undo);

        label_level = new QLabel(verticalLayoutWidget);
        label_level->setObjectName("label_level");
        label_level->setEnabled(false);

        verticalLayout->addWidget(label_level);

        doubleSpinBox_level = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox_level->setObjectName("doubleSpinBox_level");
        doubleSpinBox_level->setEnabled(false);
        doubleSpinBox_level->setMinimum(0.250000000000000);
        doubleSpinBox_level->setMaximum(0.900000000000000);
        doubleSpinBox_level->setSingleStep(0.050000000000000);
        doubleSpinBox_level->setValue(0.900000000000000);

        verticalLayout->addWidget(doubleSpinBox_level);

        label_zoom = new QLabel(centralwidget);
        label_zoom->setObjectName("label_zoom");
        label_zoom->setEnabled(false);
        label_zoom->setGeometry(QRect(150, 10, 31, 16));
        label_processed = new QLabel(centralwidget);
        label_processed->setObjectName("label_processed");
        label_processed->setGeometry(QRect(471, 0, 151, 20));
        label_original = new QLabel(centralwidget);
        label_original->setObjectName("label_original");
        label_original->setGeometry(QRect(182, 0, 121, 20));
        label_recovered = new QLabel(centralwidget);
        label_recovered->setObjectName("label_recovered");
        label_recovered->setGeometry(QRect(760, 0, 161, 20));
        verticalSlider_zoom = new QSlider(centralwidget);
        verticalSlider_zoom->setObjectName("verticalSlider_zoom");
        verticalSlider_zoom->setEnabled(false);
        verticalSlider_zoom->setGeometry(QRect(150, 30, 21, 160));
        verticalSlider_zoom->setMaximum(100);
        verticalSlider_zoom->setOrientation(Qt::Vertical);
        verticalSlider_zoom->setTickPosition(QSlider::TicksAbove);
        graphicsView_original = new QGraphicsView(centralwidget);
        graphicsView_original->setObjectName("graphicsView_original");
        graphicsView_original->setGeometry(QRect(182, 30, 275, 275));
        graphicsView_recovered = new QGraphicsView(centralwidget);
        graphicsView_recovered->setObjectName("graphicsView_recovered");
        graphicsView_recovered->setGeometry(QRect(760, 30, 275, 275));
        spinBox_size = new QSpinBox(centralwidget);
        spinBox_size->setObjectName("spinBox_size");
        spinBox_size->setEnabled(false);
        spinBox_size->setGeometry(QRect(100, 150, 42, 22));
        spinBox_size->setMinimum(1);
        spinBox_size->setMaximum(15);
        spinBox_size->setValue(1);
        label_size = new QLabel(centralwidget);
        label_size->setObjectName("label_size");
        label_size->setEnabled(false);
        label_size->setGeometry(QRect(20, 140, 71, 41));
        label_size->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_size->setWordWrap(true);
        textEdit_amount = new QTextEdit(centralwidget);
        textEdit_amount->setObjectName("textEdit_amount");
        textEdit_amount->setEnabled(false);
        textEdit_amount->setGeometry(QRect(620, 310, 121, 31));
        textEdit_amount->setReadOnly(true);
        label_amount = new QLabel(centralwidget);
        label_amount->setObjectName("label_amount");
        label_amount->setEnabled(false);
        label_amount->setGeometry(QRect(500, 310, 121, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1095, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Main window", nullptr));
        pushButton_select->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        checkBox_bw->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\275\320\276\321\205\321\200\320\276\320\274", nullptr));
        pushButton_undo->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        label_level->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\265\320\273 \320\275\320\276\321\200\320\274\321\213", nullptr));
        label_zoom->setText(QCoreApplication::translate("MainWindow", "\320\227\321\203\320\274", nullptr));
        label_processed->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\200\320\260\320\261\320\276\321\202\320\260\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_original->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\205\320\276\320\264\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_recovered->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\275\320\276\320\265 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        label_size->setText(QCoreApplication::translate("MainWindow", "\320\234\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\320\260\321\217 \320\277\320\273\320\276\321\211\320\260\320\264\321\214 \321\203\320\267\320\273\320\260", nullptr));
        label_amount->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\320\265\320\272\321\202\320\276\321\200\320\276\320\262:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
