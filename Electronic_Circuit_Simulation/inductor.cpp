#include "inductor.h"

inductor::inductor(QPixmap pix):
    Linear_Component(pix)
{
    comType = L;
    inductance = 0;
}

inductor::inductor(const inductor &l):
    Linear_Component(l.pixmap())
{

}

inductor::~inductor()
{

}

void inductor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Dialog = new inductorDialog(NULL,inductance);
    Dialog->show();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

std::complex<double> inductor::get_impedance(double f)
{
    std::complex<double> t;
    t.real(0);
    t.imag(2*M_PI*f*inductance);
    return t;
}
