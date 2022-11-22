#ifndef TRIANGLEMAKER_H
#define TRIANGLEMAKER_H

#include <QImage>
#include <QPointF>
#include <QVector>
#include <QMap>


struct Node
{
    Node(QPointF ra, QPointF a1, QPointF a2)
    {
        rightAngle = ra;
        angle1 = a1;
        angle2 = a2;

        first = nullptr;
        second = nullptr;
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

    QPointF rightAngle;
    QPointF angle1;
    QPointF angle2;

    QColor color;
};

class TriangleMaker
{
public:
    TriangleMaker(QImage image);
    TriangleMaker();

    void setImage(QImage image);
    void getColors(QPolygonF area);
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
