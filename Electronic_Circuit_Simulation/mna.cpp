#include "mna.h"

MNA::MNA()
{
    Asize = 0;
}

MNA::~MNA()
{

}

bool MNA::checkConnection(vector<node *> nl,vector<Linear_Component *> cl, vector<vsource *> vl)
{
    int ground=0;
    if(nl.size()>1 && cl.size()>0 && vl.size()>0){
        for(unsigned long i=0;i<cl.size();i++)
            if(!cl[i]->connectWell())   return false;
        for(unsigned long i=0;i<vl.size();i++)
            if(!vl[i]->connectWell())   return false;
        for(unsigned long i=0;i<nl.size();i++){
            if(!nl[i]->connectWell())
                return false;
            if(nl[i]->isGround()){
                ground++;
                if(ground==2)   return false;
            }
        }
        if(ground==0){
            return false;
        }

    }
    else{
        return false;
    }

    return true;
}

void MNA::clearResult(vector<node *> nl, vector<Linear_Component *> cl, vector<vsource *> vl)
{

    Asize = nl.size()-1+vl.size();
    for(unsigned long i=0;i<nl.size();i++){
        nl[i]->resetVoltage();
    }
    for(unsigned long i=0;i<vl.size();i++){
        vl[i]->resetCurrent();
    }

}

void MNA::setMatrix(vector<node *> nl, vector<Linear_Component *> cl,vsource * vl)
{
    for(unsigned long i=0;i<nl.size();i++)
    {
        if(nl[i]->isGround() || nl[i]->ignoreFlag()){
            nl.erase(nl.begin()+i);
            i--;
        }
    }
    Asize = nl.size()+1;
    double freq = vl->getFreq();
    complex<double> impedance;
    complex<double> one(1.0,0);

    A = new complex<double>*[Asize];
    for(int i=0;i<Asize;i++){
        A[i] = new complex<double>[Asize];
    }

    z = new complex<double>[Asize];
    x = new complex<double>[Asize];

    for(int i=0;i<Asize;i++){
        z[i].real(0);
        z[i].imag(0);
        x[i].real(0);
        x[i].imag(0);
        for(int k=0;k<Asize;k++){
            A[i][k].real(0);
            A[i][k].imag(0);
        }
    }

//Matrix G
    for(unsigned long i=0;i<cl.size();i++){
        Resistor *r = dynamic_cast<Resistor *> (cl[i]);
        capacitor *c = dynamic_cast<capacitor *> (cl[i]);
        inductor *l = dynamic_cast<inductor *> (cl[i]);
        if(r)
            impedance = r->get_impedance(freq);
        else if(c)
            impedance = c->get_impedance(freq);
        else if(l)
            impedance = l->get_impedance(freq);

        int a=-1,b=-1;
        for(unsigned long k=0;k<nl.size();k++){
            if(cl[i]->getPin0()==nl[k]){
                a = k;
            }
            else if(cl[i]->getPin1()==nl[k]){
                b = k;
            }
        }
        if(a!=-1)
            A[a][a] += one/impedance;
        if(b!=-1)
            A[b][b] += one/impedance;
        if(a!=-1 && b!=-1){
            A[a][b] += one/impedance;
            A[b][a] += one/impedance;
        }
    }

    for(int i=0;i<Asize;i++){
        for(int k=0;k<Asize;k++){
            A[i][k] *= (i==k)? (1):(-1);
        }
    }

//Matrix B,C
    for(unsigned long k=0;k<nl.size();k++){
        if(vl->getPinPos(nl[k]) == vl->getLeftPos()){
            A[nl.size()][k] = 1;
            A[k][nl.size()] = 1;
        }
        else if(vl->getPinPos(nl[k]) == vl->getRightPos()){
            A[nl.size()][k] = -1;
            A[k][nl.size()] = -1;
        }
    }


//Matrix Z;

    z[nl.size()] = vl->getVoltage();

}

void MNA::calculate(vector<node *> nl,vsource * vl)
{
    for(unsigned long i=0;i<nl.size();i++)
    {
        if(nl[i]->isGround() || nl[i]->ignoreFlag()){
            nl.erase(nl.begin()+i);
            i--;
        }
    }
    Asize = nl.size()+1;
    double freq = vl->getFreq();

    if(A){
        complex<double> *a = new complex<double>[Asize*Asize];
        for(long long i=0;i<Asize;i++){
            for(long long k=0;k<Asize;k++){
                a[i*Asize+k] = A[k][i];
            }
        }

        MatrixXcd Acm = Map<MatrixXcd>(a,Asize,Asize);
        VectorXcd Zv = Map<VectorXcd>(z,Asize);
        VectorXcd Xv = Acm.inverse()*Zv;


        for(unsigned long i=0;i<nl.size();i++){
            nl[i]->addVoltage(Xv(i),freq);
        }
        vl->setCurrent(Xv(nl.size()));

    }



    if(A){
        for(int i=0;i<Asize;i++){
            delete []A[i];
        }
        delete []A;
    }
    if(z){
        delete []z;
    }
    if(x){
        delete []x;
    }
}


