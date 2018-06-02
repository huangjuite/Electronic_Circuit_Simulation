#include "inductordialog.h"
#include "ui_inductordialog.h"


inductorDialog::inductorDialog(QWidget *parent, double &Ivalue) :
    QDialog(parent),
    ui(new Ui::inductorDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(" ");
    ui->comboBox->addItem("μ");
    ui->comboBox->addItem("p");
    inductance = &Ivalue;
    if(inductance!=NULL){
        if(*inductance>1){
           ui->lineEdit->setText(QString::number(*inductance,'f',3));
           ui->comboBox->setCurrentIndex(0);
        }
        else if(*inductance>1e-6){
            ui->lineEdit->setText(QString::number(*inductance*1e6,'f',3));
            ui->comboBox->setCurrentIndex(1);
        }
        else{
            ui->lineEdit->setText(QString::number(*inductance*1e12,'f',3));
            ui->comboBox->setCurrentIndex(2);
        }
    }
    else{
        *inductance = 0;
    }

}

inductorDialog::~inductorDialog()
{
    delete ui;
}
void inductorDialog::accept()
{
    *inductance = ui->lineEdit->text().toDouble();
    if(ui->comboBox->currentIndex()==0){
        *inductance *= 1;
    }
    else if(ui->comboBox->currentIndex() == 1){
        *inductance *= 1e-6;
    }
    else if(ui->comboBox->currentIndex() == 2){
        *inductance *= 1e-12;
    }
    QDialog::accept();
    delete this;
}

void inductorDialog::reject()
{
    QDialog::reject();
    delete this;
}


void inductorDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key_W){
        reject();
    }
    else if(event->key() == Qt::EnterKeyDone){
        accept();
    }

    QDialog::keyPressEvent(event);
}
