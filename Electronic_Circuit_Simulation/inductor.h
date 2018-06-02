#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "linear_component.h"
#include "inductordialog.h"

class inductor:public Linear_Component
{
public:
    inductor(QPixmap);
    inductor(const inductor &);
    ~inductor();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    std::complex<double> get_impedance(double f);
private:
    inductorDialog *Dialog;
    double inductance;
};

#endif // INDUCTOR_H
