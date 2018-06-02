#include "customscene.h"
#include <QDebug>

customScene::customScene(QGraphicsView *Gview):
    QGraphicsScene(NULL)
{
    view = Gview;
    gridSize = 29;
    wireMode = false;
    mouseToggle = 0;
    newNode = NULL;
    QPen pen(Qt::DashLine);
    crossLine1 = new QGraphicsLineItem();
    crossLine1->setPen(pen);
    crossLine1->show();
    crossLine2 = new QGraphicsLineItem();
    crossLine2->setPen(pen);
    crossLine2->show();
    tempLine = new QGraphicsLineItem();
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    tempLine->setPen(pen);
    tempLine->show();
    QImage p(":/ground.png");
    groundItem = new QGraphicsPixmapItem;
    groundItem->setPixmap(QPixmap::fromImage(p));
    groundItem->setOffset(-groundItem->boundingRect().width()/2,-15);
    groundItem->show();
    groundItem->setFlag(QGraphicsItem::ItemIsMovable);
    groundMode = false;
}

customScene::~customScene()
{

}

void customScene::connectItem(QGraphicsItem *item0, QGraphicsItem *item1)
{
    currentNode = dynamic_cast<node *>(item0);
    currentNode1 = dynamic_cast<node *>(item1);
    if(currentNode && !currentNode1){
        Linear_Component *comp = dynamic_cast<Linear_Component *>(item1);
        if(comp && comp->CheckConnection(currentNode,nextPos)){
            nextPos = *comp->getPinPos(newNode);
            currentNode->checkConnection(comp,nextPos);
            customLine *line = new customLine(currentNode,comp);
            this->addItem(line);
        }
    }
    else if(!currentNode && currentNode1){
        Linear_Component *comp = dynamic_cast<Linear_Component *>(item0);
        if(comp && comp->CheckConnection(currentNode1,nextPos)){
            nextPos = *comp->getPinPos(newNode);
            currentNode1->checkConnection(comp,nextPos);
            customLine *line = new customLine(currentNode1,comp);
            this->addItem(line);
        }
    }
    else if(currentNode && currentNode1){
        emit removeNode(currentNode1);
        currentNode->copyNode(currentNode1);
        delete currentNode1;
    }
}

void customScene::keyPressEvent(QKeyEvent *event)
{
    /*
    if(event->key()==Qt::Key_L && this->selectedItems().size()==2){
        currentNode = dynamic_cast<node *>(this->selectedItems().front());
        currentNode1 = dynamic_cast<node *>(this->selectedItems().at(1));
        if(currentNode && !currentNode1){
            Linear_Component *comp = dynamic_cast<Linear_Component *>(this->selectedItems().at(1));
            if(comp && comp->CheckConnection(currentNode)){
                currentNode->checkConnection(comp);
                customLine *line = new customLine(currentNode,comp);
                this->addItem(line);
            }
        }
        else if(!currentNode && currentNode1){
            Linear_Component *comp = dynamic_cast<Linear_Component *>(this->selectedItems().at(0));
            if(comp && comp->CheckConnection(currentNode1)){
                currentNode1->checkConnection(comp);
                customLine *line = new customLine(currentNode1,comp);
                this->addItem(line);
            }
        }
    }
    */
    if(event->key()==Qt::Key_G){
        if(this->selectedItems().size()==1 && !wireMode && !groundMode){
            currentNode = dynamic_cast<node *>(this->selectedItems().front());
            if(currentNode){
                if(currentNode->isGround()){
                    groundMode = false;
                    currentNode->setGround(false);
                }
                else{
                    this->addItem(groundItem);
                    this->addItem(tempLine);
                    groundItem->setPos(crossPos);
                    groundMode = true;
                    closePoint.clear();
                    QPainterPath pa = currentNode->shape();
                    for(int i=0;i<100;i++){
                        closePoint.push_back(pa.pointAtPercent(qreal(i/100.0)));
                        closePoint.back() += currentNode->pos();
                    }
                }
            }
        }
    }
    else if(event->key()==Qt::Key_W){
        if(!wireMode){
            this->addItem(crossLine1);
            this->addItem(crossLine2);
            wireMode = true;
        }
        else{
            this->removeItem(tempLine);
            if(mouseToggle==1 && !newNode->shape().isEmpty()){
                emit addNode(newNode);
            }
            mouseToggle = 0;
            this->removeItem(crossLine1);
            this->removeItem(crossLine2);
            wireMode = false;
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void customScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen;
    pen.setColor(Qt::gray);
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top = int(rect.top()) - (int(rect.top()) % gridSize);
    QVector<QPointF> points;
    for (qreal x = left; x < rect.right(); x += gridSize){
        for (qreal y = top; y < rect.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}

void customScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF newPos = event->scenePos();
    crossPos.setX(round(newPos.x()/gridSize)*gridSize);
    crossPos.setY(round(newPos.y()/gridSize)*gridSize);
    if(abs(crossPos.x()-lastPoint.x()) > abs(crossPos.y()-lastPoint.y())){
        nextPos.setX(crossPos.x());
        nextPos.setY(lastPoint.y());
    }
    else{
        nextPos.setX(lastPoint.x());
        nextPos.setY(crossPos.y());
    }

    crossLine1->setLine(crossPos.x(),crossPos.y()-800,crossPos.x(),crossPos.y()+800);
    crossLine2->setLine(crossPos.x()-800,crossPos.y(),crossPos.x()+800,crossPos.y());

    if(wireMode){
        if(mouseToggle == 1){
            tempLine->setLine(lastPoint.x(),lastPoint.y(),nextPos.x(),nextPos.y());
        }
    }

    if(groundMode){
        groundItem->setPos(crossPos);
        QPointF p,cp(5000,5000);
        foreach (p, closePoint) {
            if(abs((p-crossPos).manhattanLength()) < abs((cp-crossPos).manhattanLength())){
                cp = p;
            }
        }
        tempLine->setLine(crossPos.x(),crossPos.y(),cp.x(),cp.y());
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    QGraphicsItem *t;

    if(event->button() == Qt::LeftButton && groundMode){
        QPainterPath pa = tempLine->shape();
        pa.translate(tempLine->pos()-groundItem->pos());
        pa = groundItem->shape() + pa;
        pa.translate(groundItem->pos()-currentNode->pos());
        currentNode->setGround(true,pa);
        this->removeItem(tempLine);
        this->removeItem(groundItem);
        closePoint.clear();
        groundMode = false;
    }

    if(event->button() == Qt::LeftButton && wireMode){
        if(mouseToggle == 0){
            newNode = new node;
            this->addItem(newNode);
            mouseToggle = 1;
            this->addItem(tempLine);
            tempLine->setLine(crossPos.x(),crossPos.y(),crossPos.x(),crossPos.y());
            foreach(t,this->items()){
                if(t && (t!=crossLine1) && (t!=crossLine2) && (t!=newNode) && (t!=tempLine)){
                    if(itemTouch(tempLine,t)){
                        node *nd = dynamic_cast<node *> (t);
                        if(nd){
                            delete newNode;
                            newNode = nd;
                        }
                        else{
                            connectItem(newNode,t);
                        }
                        break;
                    }
                }
            }
            lastPoint = crossPos;
        }
        else if(mouseToggle == 1){
            tempLine->setLine(nextPos.x(),nextPos.y(),nextPos.x(),nextPos.y());
            this->update();
            foreach(t,this->items()){
                if(t && (t!=crossLine1) && (t!=crossLine2) && (t!=newNode) && (t!=tempLine)){
                    if(itemTouch(tempLine,t)){
                        mouseToggle = 0;
                        node *nd = dynamic_cast<node *> (t);
                        if(nd){
                            this->removeItem(newNode);
                            connectItem(nd,newNode);
                            newNode = nd;
                        }
                        else{
                            connectItem(newNode,t);
                        }
                        break;
                    }
                }
            }

            tempLine->setLine(lastPoint.x(),lastPoint.y(),nextPos.x(),nextPos.y());
            newNode->addPath(tempLine);
            if(mouseToggle == 0){
                this->removeItem(tempLine);
                if(!newNode->shape().isEmpty()){
                    emit addNode(newNode);
                }
            }
            lastPoint = nextPos;
        }
    }
}

int customScene::getGridSize()
{
    return gridSize;
}

bool customScene::itemTouch(QGraphicsItem *tl, QGraphicsItem *it)
{
    QPainterPath path,itPath;
    path = tl->shape();
    path.translate(tl->pos()-it->pos());

    QTransform t;
    t.rotate(it->rotation());
    itPath = t.map(it->shape());

    if(itPath.contains(path))
        return true;

    return false;
}


