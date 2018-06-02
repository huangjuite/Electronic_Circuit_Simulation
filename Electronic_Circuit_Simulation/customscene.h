#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QPainter>
#include "node.h"
#include "customline.h"
#include <vector>
#include <QGraphicsView>

class node;
class Linear_Component;

class customScene:public QGraphicsScene
{
    Q_OBJECT
public:
    customScene(QGraphicsView *Gview);
    ~customScene();
    void connectItem(QGraphicsItem *item0,QGraphicsItem *item1);
    int getGridSize();
    bool itemTouch(QGraphicsItem *tl,QGraphicsItem *it);
private slots:
    void keyPressEvent(QKeyEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void addNode(node *);
    void removeNode(node *);
private:
    QPointF crossPos;
    QPointF nextPos;
    QGraphicsLineItem *tempLine;
    QGraphicsLineItem *crossLine1;
    QGraphicsLineItem *crossLine2;
    QPointF lastPoint;
    QGraphicsView *view;
    int gridSize;
    node *newNode;
    node *currentNode;
    node *currentNode1;
    bool wireMode;
    int mouseToggle;
    std::vector<QGraphicsLineItem *> lineContainer;
    QGraphicsPixmapItem *groundItem;
    bool groundMode;
    std::vector<QPointF> closePoint;
};

#endif // CUSTOMSCENE_H
