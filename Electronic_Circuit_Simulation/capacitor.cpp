#include "capacitor.h"

capacitor::capacitor(QPixmap pix):
    Linear_Component(pix)
{
    comType = C;
    capacitance = 0;
}

capacitor::capacitor(const capacitor &c):
    Linear_Component(c.pixmap())
{

}

capacitor::~capacitor()
{

}

void capacitor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Dialog = new capacitorDialog(NULL,capacitance);
    Dialog->show();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

std::complex<double> capacitor::get_impedance(double f)
{
    std::complex<double> t;
    t.real(0);
    t.imag(-1/(2*M_PI*f*capacitance));
    return t;
}
