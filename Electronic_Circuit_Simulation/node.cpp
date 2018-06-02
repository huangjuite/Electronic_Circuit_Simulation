#include "node.h"
#include <QDebug>

node::node():QGraphicsPathItem(NULL)
{
    this->show();
    this->setFlag(ItemIsSelectable,true);
    this->setFlag(ItemIsMovable,true);
    this->setFlag(ItemSendsScenePositionChanges,true);
    this->setPen(QPen(Qt::blue,3));
    this->setBrush(Qt::blue);
    ground = false;
    ignore = false;
}

node::~node()
{

}


QVariant node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSelectedChange){
        if(value.toBool() == true){
            if(!ground)
                emit drawthis(this);
        }
        else
            emit cancleDraw(this);
    }
    else if(change == ItemPositionChange){
        emit posChange();
        QPointF newPos = value.toPointF();
        if(QApplication::mouseButtons() == Qt::LeftButton &&
                dynamic_cast<customScene*> (this->scene())){
            customScene* cS = dynamic_cast<customScene*> (this->scene());
            int gridSize = cS->getGridSize();
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;

            QPointF offset = QPointF(xV-pos().x(),yV-pos().y());
            QMap<int, QPointF>::iterator it;
            it = pinPos.begin();
            while(it!=pinPos.end()){
                it.value() += offset;
                it++;
            }
            //gPath.translate(offset);
            //interPath.translate(offset);

            return QPointF(xV, yV);
        }
        else
            return newPos;
    }

    return QGraphicsPathItem::itemChange(change, value);
}

void node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsPathItem::mouseMoveEvent(event);
}

void node::cutConnection(Linear_Component *comp)
{
    for(unsigned long i=0;i<connection_list.size();i++)
    {
        if(comp->getID() == connection_list[i]->getID()){
            connection_list.erase(connection_list.begin()+i);
            i--;
        }
    }
}

void node::checkConnection(Linear_Component *comp,QPointF pos)
{
    Linear_Component *t;
    bool f = true;
    foreach(t,connection_list){
        if(t==comp){
            f = false;
            break;
        }
    }
    if(f){
        connection_list.push_back(comp);
        pinPos[comp->getID()] = pos;
    }
}

void node::checkConnection(Linear_Component * comp)
{
    Linear_Component *t;
    bool f = true;
    foreach(t,connection_list){
        if(t==comp){
            f = false;
            break;
        }
    }
    if(f){
        connection_list.push_back(comp);
    }
}

std::vector<Linear_Component *> node::getConnectionList()
{
    return connection_list;
}

bool node::isGround()
{
    return ground;
}

void node::setGround(bool b,QPainterPath pa)
{
    ground = b;
    if(ground){
        interPath = this->path().intersected(pa);
        this->setPath(this->path()+pa);
        gPath = pa;
    }
    else{
        gPath = this->path() - gPath + interPath;
        this->setPath(gPath);
    }
}

void node::addVoltage(std::complex<double> vol, double f)
{
    voltage.push_back(vol);
    frequency.push_back(f);
}

void node::resetVoltage()
{
    voltage.clear();
    voltage.clear();
    frequency.clear();
}

std::vector<double> node::getFreq()
{
    return frequency;
}

std::vector<std::complex<double>> node::getVoltage()
{
    return voltage;
}

bool node::connectWell()
{
    if(connection_list.size()>1)    return true;

    return false;
}

std::vector<QPointF> node::getPixData(double scale, double step, int number, double t0)
{
    std::vector<QPointF> pixData;

    for(int i=0;i<number;i++){
        double y = 0;
        double t = t0+step*i;
        for(unsigned long k=0;k<voltage.size();k++){
            double amp = sqrt(pow(voltage[k].real(),2)+pow(voltage[k].imag(),2));
            double omega = 2*M_PI*frequency[k];
            double phi = atan2(voltage[k].imag(),voltage[k].real())*180/M_PI;
            y += scale*(amp*cos((omega*t+phi-90)*M_PI/180.));
        }
        pixData.push_back(QPointF(i,y));
    }

    return pixData;
}

void node::setIgnore(bool b)
{
    ignore = b;
}

bool node::ignoreFlag()
{
    return ignore;
}

void node::copyNode(node *nd)
{
    foreach(Linear_Component *compo,nd->getConnectionList()){
        connection_list.push_back(compo);
    }
    foreach (double f, nd->getFreq()) {
        frequency.push_back(f);
    }
    foreach (std::complex<double> vol,nd->getVoltage()) {
        voltage.push_back(vol);
    }
    if(nd->isGround())
        ground = true;

    QPainterPath path;
    path = nd->shape();
    path.translate(nd->pos()-pos());

    path += this->path();
    this->setPath(path);
}

void node::addPath(QGraphicsItem *tl)
{
    QPainterPath path;
    path = tl->shape();
    path.translate(tl->pos()-pos());
    path += this->path();
    this->setPath(path);
}

QPointF node::getPinPos(Linear_Component *compo)
{
    return pinPos[compo->getID()];
}






