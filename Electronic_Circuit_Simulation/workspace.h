#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QDebug>
#include <QKeyEvent>


class workspace:public QGraphicsView
{
public:
    workspace(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    ~workspace();
};

#endif // WORKSPACE_H
