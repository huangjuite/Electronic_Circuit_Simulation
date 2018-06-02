#include "scopegraphicsview.h"


scopeGraphicsView::scopeGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{
    pen.push_back(QPen(QColor("red"),2));
    pen.push_back(QPen(QColor("orange"),2));
    pen.push_back(QPen(QColor("yellow"),2));
    pen.push_back(QPen(QColor("green"),2));
    pen.push_back(QPen(QColor("blue"),2));
    pen.push_back(QPen(QColor("purple"),2));
    node_list.clear();
    scene = new QGraphicsScene();
    this->setScene(scene);
    pixmap = new QPixmap(this->geometry().width(),this->geometry().height());
    painter = new QPainter(pixmap);
    pixmap2 = new QPixmap(this->geometry().width(),this->geometry().height());
    painter2 = new QPainter(pixmap);
    item = new QGraphicsPixmapItem();
    scene->addItem(item);
}


void scopeGraphicsView::reset()
{
    node_list.clear();
    delete painter;
    delete pixmap;
    pixmap = new QPixmap(this->geometry().width(),this->geometry().height());
    painter = new QPainter(pixmap);
    pixmap->fill(Qt::white);
    scene->update();
}

void scopeGraphicsView::addComponent(Electronic_Component *ec)
{
    node *n = dynamic_cast<node *> (ec);
    if(n){
        node_list.push_back(n);
    }
}

void scopeGraphicsView::dropComponent(Electronic_Component *ec)
{
    node *n = dynamic_cast<node *> (ec);
    if(n){
        for(unsigned long i=0;i<node_list.size();i++){
            if(n == node_list[i]){
                node_list.erase(node_list.begin()+i);
                break;
            }
        }
    }
}

void scopeGraphicsView::draw(double scale,double step,double t0)
{
    sc = scale;
    st = step;
    ts = t0;
    delete painter;
    delete pixmap;
    pixmap = new QPixmap(this->geometry().width(),this->geometry().height());
    painter = new QPainter(pixmap);
    pixmap->fill(Qt::white);
    if(node_list.size()>0){
        for(unsigned long i=0;i<node_list.size();i++){
            std::vector<QPointF> pixData = node_list[i]->getPixData(scale,step,this->geometry().width(),t0);
            painter->setPen(pen[i%pen.size()]);
            for(unsigned long k=1;k<pixData.size();k++){
                painter->drawLine(pixData[k-1].x(),(pixData[k-1].y()*(-1)+this->geometry().height()/2),pixData[k].x(),(pixData[k].y()*(-1)+this->geometry().height()/2));
            }
        }
        QPen p;
        p.setStyle(Qt::DashLine);
        p.setColor(Qt::black);
        p.setWidth(1);
        painter->setPen(p);
        painter->drawLine(0,this->geometry().height()/2,this->geometry().width(),this->geometry().height()/2);
    }

    item->setPixmap(*pixmap);
    scene->update();
}

scopeGraphicsView::~scopeGraphicsView()
{
    delete painter;
    delete pixmap;
    delete item;
    delete scene;
}

void scopeGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    delete painter2;
    delete pixmap2;
    pixmap2 = new QPixmap(this->geometry().width(),this->geometry().height());
    painter2 = new QPainter(pixmap2);
    painter2->drawPixmap(0,0,*pixmap);
    std::vector<QPointF> value;
    for(unsigned long i=0;i<node_list.size();i++){
        std::vector<QPointF> pixData = node_list[i]->getPixData(sc,st,this->geometry().width(),ts);
        value.push_back(pixData[event->x()]);
        QPen p = pen[i%pen.size()];
        p.setStyle(Qt::DashLine);
        p.setWidth(1);
        painter2->setPen(p);
        painter2->drawLine(event->x(),0,event->x(),this->geometry().height());
        painter2->drawLine(0,value.back().y()*(-1)+this->geometry().height()/2,this->geometry().width(),value.back().y()*(-1)+this->geometry().height()/2);
    }
    item->setPixmap(*pixmap2);
    emit refreshText(value);
}



void scopeGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    std::vector<QPointF> value;
    value.clear();
    emit refreshText(value);
    item->setPixmap(*pixmap);
}



