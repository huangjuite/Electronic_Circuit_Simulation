#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include<QGraphicsLineItem>
#include"node.h"
#include"linear_component.h"
#include"electronic_component.h"
#include<QGraphicsSceneMouseEvent>
#include<QPen>

class node;
class Linear_Component;

class customLine:public Electronic_Component,public QGraphicsLineItem
{
    Q_OBJECT
public:
    customLine(QGraphicsItem *nd,QGraphicsItem *component);
    ~customLine();
public slots:
    void connectionMove();
    void on_die();
private:
    QPointF *compPos;
    node *newN;
    Linear_Component *compo;
};

#endif // CUSTOMLINE_H
