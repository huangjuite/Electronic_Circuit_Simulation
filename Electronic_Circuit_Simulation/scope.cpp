#include "scope.h"
#include "ui_scope.h"

scope::scope(QWidget *parent):
    QDialog(parent),
    ui(new Ui::scope)
{
    ui->setupUi(this);
    status = close;
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(reDraw()));
    connect(ui->verticalSlider,SIGNAL(valueChanged(int)),this,SLOT(reDraw()));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(reDraw()));
    connect(ui->graphicsView,SIGNAL(refreshText(std::vector<QPointF>)),this,SLOT(updateText(std::vector<QPointF>)));
    ui->lableSpace->hide();
    ui->label_v0->setStyleSheet("QLabel { color : red; }");
    ui->label_v1->setStyleSheet("QLabel { color : orange; }");
    ui->label_v2->setStyleSheet("QLabel { color : yellow; }");
    ui->label_v3->setStyleSheet("QLabel { color : green; }");
    ui->label_v4->setStyleSheet("QLabel { color : blue; }");
    ui->label_v5->setStyleSheet("QLabel { color : purple; }");
    lable_list.push_back(ui->label_v0);
    lable_list.push_back(ui->label_v1);
    lable_list.push_back(ui->label_v2);
    lable_list.push_back(ui->label_v3);
    lable_list.push_back(ui->label_v4);
    lable_list.push_back(ui->label_v5);
}

scope::Status scope::get_status()
{
    return status;
}

void scope::setScope(std::vector<node*>nl,std::vector<vsource*>vl,std::vector<Linear_Component*>cl)
{
    minFreq = 1e9;
    node_list = nl;
    vsource_list = vl;
    for(unsigned long i=0;i<vl.size();i++){
        if(minFreq > vsource_list[i]->getFreq() && vsource_list[i]->getFreq()!=0){
            minFreq =  vsource_list[i]->getFreq();
        }
    }
    if(minFreq>=1e8) minFreq=100;
    comp_list = cl;
    for(unsigned long i=0;i<node_list.size();i++){
        connect(node_list[i],SIGNAL(drawthis(Electronic_Component *)),this,SLOT(drawNodeData(Electronic_Component*)));
        connect(node_list[i],SIGNAL(cancleDraw(Electronic_Component *)),this,SLOT(dropNodeData(Electronic_Component*)));
    }
    reDraw();
    status = open;
}

scope::~scope()
{
    delete ui;
}

void scope::updateText(std::vector<QPointF> value)
{
    if(value.size()>0){
        ui->label_time->setText("time : " + QString::number(value[0].x()*step+t0) + "s");
        for(unsigned long i=0;i<value.size();i++){
            lable_list[i]->setText(QString::number(value[i].y()/scale));
        }
    }
    else{
        ui->label_time->clear();
        for(unsigned long i=0;i<lable_list.size();i++){
            lable_list[i]->clear();
        }
    }
}

void scope::reject()
{
    for(unsigned long i=0;i<node_list.size();i++){
        disconnect(node_list[i],SIGNAL(drawthis(Electronic_Component *)),this,SLOT(drawNodeData(Electronic_Component *)));
        disconnect(node_list[i],SIGNAL(cancleDraw(Electronic_Component *)),this,SLOT(dropNodeData(Electronic_Component *)));
    }
    minFreq = 1e9;
    node_list.clear();
    vsource_list.clear();
    comp_list.clear();
    ui->graphicsView->reset();
    status = close;
    QDialog::reject();
}

void scope::reDraw()
{
    scale = pow(1.25,ui->verticalSlider->value());
    step = pow(2,ui->horizontalSlider->value())/minFreq / ui->graphicsView->geometry().width();
    t0 = ui->horizontalScrollBar->value()*step;
    ui->graphicsView->draw(scale,step,t0);
}

void scope::resizeEvent(QResizeEvent *event)
{
    reDraw();
    QDialog::resizeEvent(event);
}

void scope::drawNodeData(Electronic_Component *ec)
{
    ui->graphicsView->addComponent(ec);
    reDraw();
}

void scope::dropNodeData(Electronic_Component *ec)
{
    ui->graphicsView->dropComponent(ec);
    reDraw();
}
