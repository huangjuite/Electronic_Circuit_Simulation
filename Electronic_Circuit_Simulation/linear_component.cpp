#include "linear_component.h"

Linear_Component::Linear_Component(QPixmap pix):
    Electronic_Component(),QGraphicsPixmapItem(pix)
{
    this->setFlag(ItemIsMovable,true);
    this->setFlag(ItemSendsScenePositionChanges,true);
    this->setFlag(ItemIsSelectable,true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);

    margin = 5;
    this->setOffset(-boundingRect().width()/2,-boundingRect().height()/2);
    right = new QPointF(this->pos().x()+this->boundingRect().width()/2-margin,this->pos().y());
    left =  new QPointF(this->pos().x()-this->boundingRect().width()/2+margin,this->pos().y());
}

Linear_Component::~Linear_Component()
{
    delete right;
    delete left;
}

void Linear_Component::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        setRotation(rotation()+90);
        if(rotation()==360){
            setRotation(0);
        }
        setPinPos();
        emit rotationChange();

    }
    QGraphicsPixmapItem::mousePressEvent(event);
}


QVariant Linear_Component::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange){
        setPinPos();
        emit posChange();
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                dynamic_cast<customScene*> (this->scene())){
            customScene* cS = dynamic_cast<customScene*> (this->scene());
            int gridSize = cS->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            return QPointF(xV, yV);
        }
        else
            return newPos;
    }

    return QGraphicsItem::itemChange(change, value);
}

bool Linear_Component::CheckConnection(node *nd)
{
    for(unsigned long i=0;i<pin.size();i++){
        if(nd->getID() == pin[i]->getID()){
           return false;
        }
    }
    if((int)pin.size() == Maxpin){
        return false;
    }

    if(pinPos.size()==0){
        pinPos[nd->getID()] = left;
    }
    else{
        QPointF *p = left;
        if(p == pinPos.at(pin[0]->getID())){
            pinPos[nd->getID()] = right;
        }
        else{
            pinPos[nd->getID()] = left;
        }
    }
    pin.push_back(nd);
    return true;
}

bool Linear_Component::CheckConnection(node *nd, QPointF pos)
{
    for(unsigned long i=0;i<pin.size();i++){
        if(nd->getID() == pin[i]->getID()){
           return false;
        }
    }
    if((int)pin.size() == Maxpin){
        return false;
    }

    if(pin.size()==1){
        if(pinPos.size()==0){
            pinPos[nd->getID()] = left;
        }
        else{
            QPointF *p = left;
            if(p == pinPos.at(pin[0]->getID())){
                pinPos[nd->getID()] = right;
            }
            else{
                pinPos[nd->getID()] = left;
            }
        }
    }
    else if((pos-*right).manhattanLength() < (pos-*left).manhattanLength()){
        pinPos[nd->getID()] = right;
    }
    else{
        pinPos[nd->getID()] = left;
    }


    pin.push_back(nd);
    return true;
}

QPointF *Linear_Component::getPinPos(node *nd)
{
    if(pinPos[nd->getID()]){
        return pinPos[nd->getID()];
    }
    return NULL;
}

void Linear_Component::cutConnection(node *nd)
{
    for(unsigned long i=0;i<pin.size();i++)
    {
        if(nd->getID() == pin[i]->getID()){
            //pinPos.erase(nd->getID());
            pin.erase(pin.begin()+i);
            i--;
        }
    }
}

node *Linear_Component::getPin0()
{
    return pin[0];
}

node *Linear_Component::getPin1()
{
    return pin[1];
}

QPointF *Linear_Component::getRightPos()
{
    return right;
}

QPointF *Linear_Component::getLeftPos()
{
    return left;
}

bool Linear_Component::connectWell()
{
    if(pin.size()==2){
        return true;
    }
    return false;
}

void Linear_Component::shortComponent()
{
    transferCompo.clear();
    tempNode.clear();
    tempNode.push_back(pin[0]);
    tempNode.push_back(pin[1]);
    pin[1]->setIgnore(true);
    std::vector<Linear_Component *> compoL;
    compoL = pin[1]->getConnectionList();
    if(pin[1]->isGround())
        pin[0]->setGround(true);
    for(unsigned long i=0;i<compoL.size();i++){
        if(compoL[i]!=this){
            compoL[i]->cutConnection(pin[1]);
            pin[1]->cutConnection(compoL[i]);
            compoL[i]->CheckConnection(pin[0]);
            pin[0]->checkConnection(compoL[i]);
            transferCompo.push_back(compoL[i]);
        }
    }

}

void Linear_Component::reconnectComponent()
{
    pin[0]=tempNode[0];
    pin[1]=tempNode[1];
    pin[1]->setIgnore(false);
    std::vector<Linear_Component *> compoL;
    compoL = pin[1]->getConnectionList();
    if(pin[0]->isGround()==false){
        if(pin[0]->getVoltage().size()>0){
            pin[1]->addVoltage(pin[0]->getVoltage().back(),pin[0]->getFreq().back());
        }
    }
    if(pin[1]->isGround()){
        pin[0]->setGround(false);
    }
    for(unsigned long i=0;i<transferCompo.size();i++){
        if(transferCompo[i]!=this){
            transferCompo[i]->cutConnection(pin[0]);
            transferCompo[i]->CheckConnection(pin[1]);
            pin[0]->cutConnection(transferCompo[i]);
            pin[1]->checkConnection(transferCompo[i]);
        }
    }

}

void Linear_Component::setPinPos()
{
    if(rotation()==90){
        *right = QPointF(this->pos().x(),this->pos().y()+this->boundingRect().width()/2-margin);
        *left =  QPointF(this->pos().x(),this->pos().y()-this->boundingRect().width()/2+margin);
    }else if(rotation()==180){
        *right = QPointF(this->pos().x()-this->boundingRect().width()/2+margin,this->pos().y());
        *left =  QPointF(this->pos().x()+this->boundingRect().width()/2-margin,this->pos().y());
    }
    else if(rotation()==270){
        *right = QPointF(this->pos().x(),this->pos().y()-this->boundingRect().width()/2+margin);
        *left =  QPointF(this->pos().x(),this->pos().y()+this->boundingRect().width()/2-margin);
    }
    else{
        *right = QPointF(this->pos().x()+this->boundingRect().width()/2-margin,this->pos().y());
        *left =  QPointF(this->pos().x()-this->boundingRect().width()/2+margin,this->pos().y());
    }
}

