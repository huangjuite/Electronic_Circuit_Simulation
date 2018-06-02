#ifndef LINEAR_COMPONENT_H
#define LINEAR_COMPONENT_H

#include "electronic_component.h"
#include <iostream>
#include <cmath>
#include <complex>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <vector>
#include "node.h"
#include <map>
#include "customscene.h"

class node;
class customScene;

class Linear_Component : public Electronic_Component,public QGraphicsPixmapItem
{
public:
    enum type{R,C,L};
    Linear_Component(QPixmap);
    ~Linear_Component();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::complex<double> get_impedance(double f);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    bool CheckConnection(node *);
    bool CheckConnection(node *,QPointF pos);
    QPointF *getPinPos(node *);
    void cutConnection(node *);
    node *getPin0();
    node *getPin1();
    QPointF *getRightPos();
    QPointF *getLeftPos();
    bool connectWell();
    void shortComponent();
    void reconnectComponent();
protected:
    type comType;
private:
    int margin;
    void setPinPos();
    std::vector<node *> pin;
    const int Maxpin=2;
    QPointF *left;
    QPointF *right;
    std::map<int,QPointF *> pinPos;
    std::vector<Linear_Component *> transferCompo;
    std::vector<node *> tempNode;
};

#endif // LINEAR_COMPONENT_H
