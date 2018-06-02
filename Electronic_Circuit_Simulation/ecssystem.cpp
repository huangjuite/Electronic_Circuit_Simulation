#include "ecssystem.h"
#include "ui_ecssystem.h"

int Electronic_Component::count = 0;

ECSsystem::ECSsystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ECSsystem)
{
    ui->setupUi(this);
    scene = new customScene(ui->workspaceView);
    ui->workspaceView->setScene(scene);
    connect(scene,SIGNAL(addNode(node*)),this,SLOT(addingNode(node*)));
    connect(scene,SIGNAL(removeNode(node*)),this,SLOT(removingNode(node*)));
    scopeDialog = new scope;
}

ECSsystem::~ECSsystem()
{
    delete ui;
}

void ECSsystem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace){
        for(unsigned long i=0;i<component_list.size();i++)
            if(component_list[i]->isSelected()){
                scene->removeItem(component_list[i]);
                delete component_list[i];
                component_list.erase(component_list.begin()+i);
                i--;
            }
        for(unsigned long i=0;i<node_list.size();i++)
            if(node_list[i]->isSelected()){
                scene->removeItem(node_list[i]);
                delete node_list[i];
                node_list.erase(node_list.begin()+i);
                i--;
            }
        for(unsigned long i=0;i<vsource_list.size();i++)
            if(vsource_list[i]->isSelected()){
                scene->removeItem(vsource_list[i]);
                delete vsource_list[i];
                vsource_list.erase(vsource_list.begin()+i);
                i--;
            }
        QGraphicsItem *temp;
        while(scene->selectedItems().size()>0){
            temp = scene->selectedItems().front()      ;
            scene->removeItem(scene->selectedItems().front());
            delete temp;
        }

        scene->update();
    }

}

void ECSsystem::on_OpenScopeButton_clicked()
{
    if(scopeDialog->get_status() == scope::close){
        if(calculator.checkConnection(node_list,component_list,vsource_list)){
            calculator.clearResult(node_list,component_list,vsource_list);
            for(unsigned long i=0;i<vsource_list.size();i++){
                for(unsigned long k=0;k<vsource_list.size();k++){
                    if(k!=i)    vsource_list[k]->shortComponent();
                }
                calculator.setMatrix(node_list,component_list,vsource_list[i]);
                calculator.calculate(node_list,vsource_list[i]);
                for(long long k=vsource_list.size()-1;k>=0;k--){
                    if(k!=i)    vsource_list[k]->reconnectComponent();
                }
            }


            scopeDialog->setScope(node_list,vsource_list,component_list);
            scopeDialog->show();
        }else{
            QMessageBox::critical(
                    this,
                    tr("Connection Error"),
                    tr("Please check coneection.") );
        }
    }

}



void ECSsystem::on_resistorButton_clicked()
{
    QImage image(":/resistor.png");
    Linear_Component *r = new Resistor(QPixmap::fromImage(image));
    component_list.push_back(r);
    scene->addItem(component_list.back());

    connect(component_list.back(),SIGNAL(posChange()),this,SLOT(objectMoving()));

    ui->lineEdit->setText("adding resistor"+QString::number(component_list.size()));

}

void ECSsystem::on_capacitorButton_clicked()
{
    QImage image(":/capacitor.png");
    Linear_Component *c = new capacitor(QPixmap::fromImage(image));
    component_list.push_back(c);
    scene->addItem(component_list.back());
    connect(component_list.back(),SIGNAL(posChange()),this,SLOT(objectMoving()));
    ui->lineEdit->setText("adding capacitor"+QString::number(component_list.size()));
}

void ECSsystem::on_inductorButton_clicked()
{
    QImage image(":/inductor.png");
    Linear_Component *l = new inductor(QPixmap::fromImage(image));
    component_list.push_back(l);
    scene->addItem(component_list.back());
    connect(component_list.back(),SIGNAL(posChange()),this,SLOT(objectMoving()));
    ui->lineEdit->setText("adding inductor"+QString::number(component_list.size()));
}

void ECSsystem::on_groundButton_clicked()
{
    node *n = new node();
    node_list.push_back(n);
    scene->addItem(node_list.back());

    ui->lineEdit->setText("adding node"+QString::number(node_list.size()));
}

void ECSsystem::addingNode(node *nd)
{
    node *t;
    bool f = true;
    foreach(t,node_list){
        if(t == nd){
            f = false;
            break;
        }
    }
    if(f){
        node_list.push_back(nd);
        scene->addItem(node_list.back());
        ui->lineEdit->setText("adding node"+QString::number(node_list.size()));
    }
}

void ECSsystem::removingNode(node *nd)
{
    node *t;
    int i=0;
    foreach(t,node_list){
        if(t == nd){
            node_list.erase(node_list.begin()+i);
            i--;
        }
        i++;
    }
}

void ECSsystem::on_vsourceButton_clicked()
{
    QImage image(":/vsource.png");
    vsource *v = new vsource(QPixmap::fromImage(image));
    vsource_list.push_back(v);
    scene->addItem(vsource_list.back());

    ui->lineEdit->setText("adding vsource"+QString::number(vsource_list.size()));
}

void ECSsystem::objectMoving()
{

    ui->lineEdit->setText("Moving");
}

void ECSsystem::on_clearButton_clicked()
{
    QGraphicsItem *temp;
    while(scene->items().size()>0){
        temp = scene->items().front();
        scene->removeItem(scene->items().front());
        delete temp;
    }

    vsource_list.clear();
    component_list.clear();
    node_list.clear();
}

