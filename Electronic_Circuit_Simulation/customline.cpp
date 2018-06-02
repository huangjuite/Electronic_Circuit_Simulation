#include "customline.h"

customLine::customLine(QGraphicsItem *nd,QGraphicsItem *component):
    Electronic_Component(),QGraphicsLineItem(NULL)
{
    newN = dynamic_cast<node*> (nd);
    compo = dynamic_cast<Linear_Component *>(component);
    QPen p(Qt::blue,3);
    compPos = compo->getPinPos(newN);
    QPointF pos = newN->getPinPos(compo);
    this->setLine(pos.x(),pos.y(),compPos->x(),compPos->y());
    this->setPen(p);
    this->setFlag(ItemIsSelectable,true);
    connect(newN,SIGNAL(posChange()),this,SLOT(connectionMove()));
    connect(newN,SIGNAL(die()),this,SLOT(on_die()));
    connect(compo,SIGNAL(posChange()),this,SLOT(connectionMove()));
    connect(compo,SIGNAL(rotationChange()),this,SLOT(connectionMove()));
    connect(compo,SIGNAL(die()),this,SLOT(on_die()));
}

customLine::~customLine()
{
    if(newN!=NULL){
        newN->cutConnection(compo);
    }
    if(compo!=NULL){
        compo->cutConnection(newN);
    }
}

void customLine::connectionMove()
{
    compPos = compo->getPinPos(newN);
    QPointF p = newN->getPinPos(compo);
    this->setLine(p.x(),p.y(),compPos->x(),compPos->y());
}

void customLine::on_die()
{
    delete this;
}
