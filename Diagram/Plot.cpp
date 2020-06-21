#include "Plot.h"
#include "math.h"
#include <QGraphicsTextItem>

const int sizeTitle = 100;

Plot::Plot(QWidget *parent) :
    QGraphicsView(parent),
    stepLevel(1000),
    suffix()
{
    initPens();
    clear();
}

void Plot::clear()
{
    values.clear();
}

void Plot::appendValue(long value)
{
    if (values.empty()) {
        std::fill_n(std::back_inserter(values), countMax, value);
    } else {
        values.pop_front();
        values.push_back(value);
    }
}

void Plot::update()
{
    clearScene();
    calcSizePlot();
    paintGrid();
    paintPlot();
}

void Plot::setStepLevel(int stepLevel)
{
    this->stepLevel = stepLevel;
}

void Plot::setSuffix(const QString suffix)
{
    this->suffix = suffix;
}

void Plot::initPens()
{
    penGrid.setStyle(Qt::DashLine);
    penGrid.setColor(Qt::gray);

    penPlot.setStyle(Qt::SolidLine);
    penPlot.setWidth(2);
    penPlot.setColor(Qt::darkRed);
}

void Plot::clearScene()
{
    if (scene()) {
        delete scene();
    }
    setScene(new QGraphicsScene(this));
}

void Plot::calcSizePlot()
{
    auto vExtremum = std::minmax_element(values.begin(), values.end());
    auto vMin = *vExtremum.first;
    auto vMax = *vExtremum.second;
    auto vDisp = vMax - vMin;
    vMinPlot = vMin - vDisp / 10;
    vMaxPlot = vMax + vDisp / 10;
    vDispPlot = vMaxPlot - vMinPlot;
}

void Plot::paintGrid()
{
    long countLines = height() / 50;
    double stepLines = vDispPlot / countLines;
    if (stepLines > 0) {
        long value = (vMinPlot + stepLines);
        auto xMin = getX(0);
        auto xMax = getX(countMax);
        while (value < vMaxPlot) {
            auto y = getY(value);
            scene()->addLine(xMin, y, xMax, y, penGrid);
            QGraphicsTextItem *textItem = scene()->addText(textValue(value));
            textItem->setPos(xMax, y - 12);
            value += stepLines;
        }
    }
}

void Plot::paintPlot()
{
    auto iter = values.cbegin();
    int time = 0;
    QPointF pPrev = getPos(time, *iter);
    while (++iter != values.cend()) {
        QPointF p = getPos(++time, *iter);
        scene()->addLine(pPrev.x(), pPrev.y(), p.x(), p.y(), penPlot);
        pPrev = p;
    }
}

QPointF Plot::getPos(int time, long value) const
{
    return QPointF(getX(time), getY(value));
}

qreal Plot::getX(int time) const
{
    return time * (width() - sizeTitle) / countMax;
}

qreal Plot::getY(long value) const
{
    if (vDispPlot > 0) {
        return height() - ((value - vMinPlot) * height() / vDispPlot);
    }
    return height() / 2;
}

QString Plot::textValue(long value) const
{
    int level = 0;
    double v = value;
    while (long(v) / stepLevel > 0) {
        ++level;
        v = double(v) / stepLevel;
    }
    return QString("%1 %2%3")
            .arg(QString::number(v, 'f', level == 0 ? 0 : 2))
            .arg(textSuffix(level))
            .arg(suffix);
}

QString Plot::textSuffix(int level) const
{
    if (level == 1) return "к";
    if (level == 2) return "М";
    if (level == 3) return "Г";
    if (level == 4) return "Т";
    return QString();
}
