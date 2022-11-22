#include "trianglemaker.h"

TriangleMaker::TriangleMaker(QImage image)
{
    setImage(image);
}

TriangleMaker::TriangleMaker()
{

}

void TriangleMaker::setImage(QImage image)
{
    this->image = image;
}

void TriangleMaker::getColors(QPolygonF area)
{
    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;
    totalPixels = 0;
    highestAvg = 1;
    lowestAvg = 255;

    QPointF top = area[0];
    QPointF bottom = area[0];
    QPointF middle;
    float leftmost = 255, rightmost = 0;

    for (int i = 0; i < area.count(); i++) // find out top & bottom points
    {
        if (area[i].y() < top.y())
            top = area[i];
        if (area[i].y() > bottom.y())
            bottom = area[i];
        if (area[i].x() > rightmost)
            rightmost = area[i].x();
        if (area[i].x() < leftmost)
            leftmost = area[i].x();
    }
    for (int i = 0; i < area.count(); i++) // find out middle point
        if (area[i].y() >= top.y() && area[i] != top)
            if (area[i].y() <= bottom.y() && area[i] != bottom)
            {
                middle = area[i];
                break;
            }

    for (int y = top.y(); y < middle.y() && y < 256; y++) // from top to middle
    {
        QLineF currentRow(QPointF(0, y), QPointF(1, y));
        QLineF a(top, bottom);
        QLineF b(top, middle);
        QPointF *leftX = new QPointF;
        QPointF *rightX = new QPointF;
        currentRow.intersects(a, leftX);
        currentRow.intersects(b, rightX);

        if (leftX->x() < leftmost)
            leftX->setX(leftmost);
        if (rightX->x() > rightmost)
            rightX->setX(rightmost);

        if (leftX->x() > rightX->x())
            std::swap(leftX, rightX);

        for (int x = leftX->x(); x <= rightX->x() && x < 256; x++)
        {
            QColor currentColor = image.pixelColor(x, y);
            totalRed+= currentColor.red();
            totalGreen+= currentColor.green();
            totalBlue+= currentColor.blue();

            float currentAvg = (currentColor.red() + currentColor.green() + currentColor.blue()) / 3;
            if (highestAvg < currentAvg)
                highestAvg = currentAvg;
            if (lowestAvg > currentAvg)
                lowestAvg = currentAvg;

            totalPixels++;
        }
        delete leftX;
        delete rightX;
    }

    for (int y = middle.y(); y < bottom.y() && y < 256; y++) // from middle to bottom
    {
        QLineF currentRow(QPointF(0, y), QPointF(1, y));
        QLineF a(top, bottom);
        QLineF b(middle, bottom);
        QPointF *leftX = new QPointF;
        QPointF *rightX = new QPointF;
        currentRow.intersects(a, leftX);
        currentRow.intersects(b, rightX);

        if (leftX->x() < leftmost)
            leftX->setX(leftmost);
        if (rightX->x() > rightmost)
            rightX->setX(rightmost);

        if (leftX->x() > rightX->x())
            std::swap(leftX, rightX);

        for (int x = leftX->x(); x <= rightX->x() && x < 256; x++)
        {
            QColor currentColor = image.pixelColor(x, y);
            totalRed+= currentColor.red();
            totalGreen+= currentColor.green();
            totalBlue+= currentColor.blue();

            float currentAvg = (currentColor.red() + currentColor.green() + currentColor.blue()) / 3;
            if (highestAvg < currentAvg)
                highestAvg = currentAvg;
            if (lowestAvg > currentAvg)
                lowestAvg = currentAvg;

            totalPixels++;
        }
        delete leftX;
        delete rightX;
    }
}

QColor TriangleMaker::averageColor()
{
    QColor output(qRgb(totalRed / totalPixels, totalGreen / totalPixels, totalBlue / totalPixels));
    return output ;
}

bool TriangleMaker::acceptable(float norm)
{
    norm /= 100;

    if (lowestAvg / highestAvg >= 1 - norm)
        return true;
    else
        return false;
}
