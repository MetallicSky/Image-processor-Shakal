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

void TriangleMaker::getColors(QPointF topLeft, QPointF bottomRight)
{
    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;
    totalPixels = 0;
    highestAvg = 1;
    lowestAvg = 255;

    for (int y = topLeft.y(); y < bottomRight.y() && y < 256; y++) // from top to middle
        for (int x = topLeft.x(); x <= bottomRight.x() && x < 256; x++)
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
