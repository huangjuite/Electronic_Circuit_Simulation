#ifndef ELECTRONIC_COMPONENT_H
#define ELECTRONIC_COMPONENT_H

#include<QDialog>
#include<QLayout>
#include <QKeyEvent>
#include <QWidget>
#include <QGraphicsItem>

class Electronic_Component:public QObject
{
    Q_OBJECT
public:
    Electronic_Component();
    ~Electronic_Component();
    static int count ;
    int getID();
signals:
    void die();
    void posChange();
    void rotationChange();
    void drawthis(Electronic_Component *);
    void cancleDraw(Electronic_Component *);
private:
    int ID;
};



#endif // ELECTRONIC_COMPONENT_H
