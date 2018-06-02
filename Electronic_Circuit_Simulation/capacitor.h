#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "linear_component.h"
#include "capacitordialog.h"

class capacitor:public Linear_Component
{
public:
    capacitor(QPixmap);
    capacitor(const capacitor &);
    ~capacitor();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    std::complex<double> get_impedance(double f);
private:
    capacitorDialog *Dialog;
    double capacitance;
};

#endif // CAPACITOR_H
