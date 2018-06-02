#ifndef MNA_H
#define MNA_H

#include <vector>
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "node.h"
#include "vsource.h"
#include <Eigen/Eigen>
#include <Eigen/Eigenvalues>
#include <Eigen/LU>
#include <complex>

#include <QMessageBox>
#include <QString>

using namespace std;
using namespace Eigen;

class MNA:public QWidget
{
public:
    MNA();
    ~MNA();
    bool checkConnection(vector<node *> nl,vector<Linear_Component *> cl,vector<vsource *> vl);
    void clearResult(vector<node *> nl,vector<Linear_Component *> cl,vector<vsource *> vl);
    void setMatrix(vector<node *>nl,vector<Linear_Component *>cl,vsource *vl);
    void calculate(vector<node *>nl,vsource *vl);
private:
    int Asize;

    std::complex<double> **A;
    std::complex<double> *z;
    std::complex<double> *x;
};

#endif // MNA_H
