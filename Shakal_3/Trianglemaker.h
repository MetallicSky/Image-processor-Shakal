#ifndef TRIANGLEMAKER_H
#define TRIANGLEMAKER_H

#include <QImage>
#include <QPointF>
#include <QVector>
#include <QMap>


struct Node
{
    Node(QPointF tl, QPointF br)
    {
        topLeft = tl;
        bottomRight = br;

        first = nullptr;
        second = nullptr;
        third = nullptr;
    }
    Node();
    ~Node()
    {
        if (first != nullptr)
            delete first;
        if (second != nullptr)
            delete second;
    }

    Node *first;
    Node *second;
    Node *third;

    QPointF topLeft;
    QPointF bottomRight;

    QColor color;
};

class TriangleMaker
{
public:
    TriangleMaker(QImage image);
    TriangleMaker();

    void setImage(QImage image);
    void getColors(QPointF topLeft, QPointF bottomRight);
    QColor averageColor();
    bool acceptable(float norm);
private:

    QImage image;
    float totalRed;
    float totalGreen;
    float totalBlue;
    float highestAvg;
    float lowestAvg;
    int totalPixels;


};

#endif // TRIANGLEMAKER_H
