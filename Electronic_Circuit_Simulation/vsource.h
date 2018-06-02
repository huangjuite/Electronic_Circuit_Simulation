#ifndef VSOURCE_H
#define VSOURCE_H

#include "linear_component.h"
#include "vsourcedialog.h"

class vsourceDialog;

class vsource:public Linear_Component
{
public:
    enum type{DC,SINE};
    vsource(QPixmap);
    ~vsource();
    vsource(const vsource &);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void setVoltage(type m,double f, double a, double p);
    std::complex<double> getVoltage();
    void calculate();
    vsource::type getType();
    double getFreq();
    double getAmp();
    double getPhi();
    void resetCurrent();
    std::complex<double> getCurrent();
    void setCurrent(std::complex<double> cur);
private:
    vsourceDialog *Dialog;
    type mode;
    double freq;
    double phi;
    double amp;
    std::complex<double> voltage;
    std::complex<double> current;

};

#endif // VSOURCE_H
