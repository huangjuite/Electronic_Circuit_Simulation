#ifndef RESISTOR_H
#define RESISTOR_H

#include "linear_component.h"
#include "resistordialog.h"


class Resistor:public Linear_Component
{
public:
    Resistor(QPixmap);
    ~Resistor();
    Resistor(const Resistor &);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    std::complex<double> get_impedance(double f);
private:
    resistorDialog *Dialog;
    double resistance;

};


#endif // RESISTOR_H
