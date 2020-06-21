#pragma once

#include <QGraphicsView>
#include <QDateTime>

class Plot : public QGraphicsView
{
    Q_OBJECT

    static constexpr int countMax = 60;

public:
    Plot(QWidget *parent = nullptr);

    void clear();
    void appendValue(long value);
    void update();

    void setStepLevel(int stepLevel = 1000);
    void setSuffix(const QString suffix);

private:
    std::list<long> values;
    long vMinPlot;
    long vMaxPlot;
    long vDispPlot;

    int stepLevel;
    QString suffix;

    QPen penGrid;
    QPen penPlot;

    void initPens();
    void clearScene();
    void calcSizePlot();
    void paintGrid();
    void paintPlot();

    QPointF getPos(int time, long value) const;
    qreal getX(int time) const;
    qreal getY(long value) const;

    QString textValue(long value) const;
    QString textSuffix(int level) const;
};

