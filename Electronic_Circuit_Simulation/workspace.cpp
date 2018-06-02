#include "workspace.h"


workspace::workspace(QWidget *parent):
        QGraphicsView(parent)
{

}

void workspace::keyPressEvent(QKeyEvent *event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scalefactor = 1.25;
    if(event->key() == Qt::Key_Z){
        scale(scalefactor,scalefactor);
    }
    else if(event->key() == Qt::Key_X){
        scale(1/scalefactor,1/scalefactor);
    }

    QGraphicsView::keyPressEvent(event);
}


workspace::~workspace()
{

}
