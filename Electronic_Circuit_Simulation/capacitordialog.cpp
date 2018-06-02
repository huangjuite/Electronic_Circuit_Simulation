#include "capacitordialog.h"
#include "ui_capacitordialog.h"

capacitorDialog::capacitorDialog(QWidget *parent, double &Cvalue) :
    QDialog(parent),
    ui(new Ui::capacitorDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(" ");
    ui->comboBox->addItem("μ");
    ui->comboBox->addItem("p");
    capacitance = &Cvalue;
    if(capacitance!=NULL){
        if(*capacitance>1){
           ui->lineEdit->setText(QString::number(*capacitance,'f',3));
           ui->comboBox->setCurrentIndex(0);
        }
        else if(*capacitance>1e-6){
            ui->lineEdit->setText(QString::number(*capacitance*1e6,'f',3));
            ui->comboBox->setCurrentIndex(1);
        }
        else{
            ui->lineEdit->setText(QString::number(*capacitance*1e12,'f',3));
            ui->comboBox->setCurrentIndex(2);
        }
    }
    else{
        *capacitance = 0;
    }

}

capacitorDialog::~capacitorDialog()
{
    delete ui;
}
void capacitorDialog::accept()
{
    *capacitance = ui->lineEdit->text().toDouble();
    if(ui->comboBox->currentIndex()==0){
        *capacitance *= 1;
    }
    else if(ui->comboBox->currentIndex() == 1){
        *capacitance *= 1e-6;
    }
    else if(ui->comboBox->currentIndex() == 2){
        *capacitance *= 1e-12;
    }
    QDialog::accept();
    delete this;
}

void capacitorDialog::reject()
{
    QDialog::reject();
    delete this;
}


void capacitorDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key_W){
        reject();
    }
    else if(event->key() == Qt::EnterKeyDone){
        accept();
    }

    QDialog::keyPressEvent(event);
}




