#ifndef SCOPEGRAPHICSVIEW_H
#define SCOPEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <vector>
#include "node.h"
#include "vsource.h"

class scopeGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit scopeGraphicsView(QWidget *parent = 0);
    void reset();
    void addComponent(Electronic_Component *);
    void dropComponent(Electronic_Component *);
    void draw(double scale,double step,double t0);
    ~scopeGraphicsView();
signals:
    void refreshText(std::vector<QPointF>);
private slots:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    double sc;
    double st;
    double ts;
    QPixmap *pixmap;
    QPainter *painter;
    QPixmap *pixmap2;
    QPainter *painter2;
    std::vector<QPen> pen;
    QGraphicsScene *scene;
    std::vector<node *>node_list;
    QGraphicsPixmapItem *item;

};

#endif // SCOPEGRAPHICSVIEW_H
