#ifndef NODE_H
#define NODE_H

#include "electronic_component.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <complex>
#include "linear_component.h"

class Linear_Component;

class node:public Electronic_Component,public QGraphicsPathItem
{
public:
    node();
    ~node();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void cutConnection(Linear_Component *);
    void checkConnection(Linear_Component *,QPointF pos);
    void checkConnection(Linear_Component *);
    std::vector<Linear_Component *> getConnectionList();
    bool isGround();
    void setGround(bool b = true,QPainterPath pa = QPainterPath());
    void addVoltage(std::complex<double> vol,double f);
    void resetVoltage();
    std::vector<double> getFreq();
    std::vector<std::complex<double>> getVoltage();
    bool connectWell();
    std::vector<QPointF> getPixData(double scale, double step, int number, double t0);
    void setIgnore(bool b = true);
    bool ignoreFlag();
    void copyNode(node *nd);
    void addPath(QGraphicsItem *tl);
    QPointF getPinPos(Linear_Component *);
private:
    QMap<int,QPointF> pinPos;
    std::vector<Linear_Component *> connection_list;
    std::vector<std::complex<double>> voltage;
    std::vector<double> frequency;
    QPainterPath gPath;
    QPainterPath interPath;
    bool ground;
    bool ignore;
};

#endif // NODE_H
