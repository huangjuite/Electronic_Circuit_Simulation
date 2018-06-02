#include "resistor.h"

Resistor::Resistor(QPixmap pix):
    Linear_Component(pix)
{
    comType = R;
    resistance = 0;
}

Resistor::~Resistor(){

}

Resistor::Resistor(const Resistor &r):
    Linear_Component(r.pixmap())
{

}

void Resistor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Dialog = new resistorDialog(NULL,resistance);
    Dialog->show();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

std::complex<double> Resistor::get_impedance(double f)
{
    std::complex<double> t;
    t.real(resistance);
    t.imag(0);
    return t;
}


