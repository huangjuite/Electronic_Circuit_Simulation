#include "resistordialog.h"
#include "ui_resistordialog.h"

resistorDialog::resistorDialog(QWidget *parent,double &Rvalue) :
    QDialog(parent),
    ui(new Ui::resistorDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("resistor");
    ui->comboBox->addItem(" ");
    ui->comboBox->addItem("K");
    ui->comboBox->addItem("M");
    resistance = &Rvalue;
    if(resistance!=NULL){
        if(*resistance<1e3){
           ui->lineEdit->setText(QString::number(*resistance,'f',3));
           ui->comboBox->setCurrentIndex(0);
        }
        else if(*resistance<1e6){
            ui->lineEdit->setText(QString::number(*resistance/1e3,'f',3));
            ui->comboBox->setCurrentIndex(1);
        }
        else{
            ui->lineEdit->setText(QString::number(*resistance/1e6,'f',3));
            ui->comboBox->setCurrentIndex(2);
        }
    }
    else{
        *resistance = 0;
    }

}

resistorDialog::~resistorDialog()
{
    delete ui;
}

void resistorDialog::accept()
{
    *resistance = ui->lineEdit->text().toDouble();
    if(ui->comboBox->currentIndex()==0){
        *resistance *= 1;
    }
    else if(ui->comboBox->currentIndex() == 1){
        *resistance *= 1e3;
    }
    else if(ui->comboBox->currentIndex() == 2){
        *resistance *= 1e6;
    }
    QDialog::accept();
    delete this;
}

void resistorDialog::reject()
{
    QDialog::reject();
    delete this;
}

void resistorDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key_W){
        reject();
    }
    else if(event->key() == Qt::EnterKeyDone){
        accept();
    }

    QDialog::keyPressEvent(event);
}



