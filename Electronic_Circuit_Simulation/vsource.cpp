#include "vsource.h"

vsource::vsource(QPixmap pix):
    Linear_Component(pix)
{
    freq = 0;
    mode = DC;
    phi = 0;
    amp = 0;
}

vsource::~vsource(){

}

vsource::vsource(const vsource &r):
    Linear_Component(r.pixmap())
{

}

void vsource::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Dialog = new vsourceDialog(this);
    Dialog->show();

    QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

void vsource::setVoltage(type m,double f, double a, double p)
{
    mode = m;
    freq = f;
    phi = p;
    amp = a;
}

void vsource::calculate()
{
    voltage.real(amp * cos(phi));
    voltage.imag(amp * sin(phi));
}

vsource::type vsource::getType()
{
    return mode;
}

double vsource::getFreq()
{
    return freq;
}

double vsource::getAmp()
{
    return amp;
}

double vsource::getPhi()
{
    return phi;
}

void vsource::resetCurrent()
{
    current.real(0);
    current.imag(0);
}

std::complex<double> vsource::getCurrent()
{
    return current;
}

void vsource::setCurrent(std::complex<double> cur)
{
    current.real(cur.real());
    current.imag(cur.imag());
}

std::complex<double> vsource::getVoltage()
{
    calculate();
    return voltage;
}

