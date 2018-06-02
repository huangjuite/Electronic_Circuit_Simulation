#include "vsourcedialog.h"
#include "ui_vsourcedialog.h"

vsourceDialog::vsourceDialog(vsource *vsIN) :
    QDialog(NULL),
    ui(new Ui::vsourceDialog)
{
    ui->setupUi(this);
    vs = vsIN;
    ui->comboBox->addItem("DC");
    ui->comboBox->addItem("SINE");
    if(vs->getType()==vsource::DC){
        ui->comboBox->setCurrentIndex(0);
        ui->amp->setText(QString::number(vs->getAmp()));
        ui->freq->setText(QString::number(vs->getFreq()));
        ui->amp->setText(QString::number(vs->getAmp()));
        ui->phi->setText(QString::number(vs->getPhi()));
        ui->freq->hide();
        ui->phi->hide();
        ui->labelFreq->hide();
        ui->labelPhi->hide();
        ui->labelAmp->setText("DC Value[V] :");
    }
    else{
        ui->comboBox->setCurrentIndex(1);
        ui->freq->setText(QString::number(vs->getFreq()));
        ui->amp->setText(QString::number(vs->getAmp()));
        ui->phi->setText(QString::number(vs->getPhi()));

    }

}

vsourceDialog::~vsourceDialog()
{
    delete ui;
}

void vsourceDialog::accept()
{
    double f = ui->freq->text().toDouble();
    double a = ui->amp->text().toDouble();
    double p = ui->phi->text().toDouble();
    if(ui->comboBox->currentIndex() == 0){
        vs->setVoltage(vsource::DC,0,a,0);
    }
    else{
        vs->setVoltage(vsource::SINE,f,a,p);
    }

    QDialog::accept();
    delete this;
}

void vsourceDialog::reject()
{

    QDialog::reject();
    delete this;
}


void vsourceDialog::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->amp->setText(QString::number(vs->getAmp()));
        ui->freq->setText(QString::number(vs->getFreq()));
        ui->phi->setText(QString::number(vs->getPhi()));
        ui->freq->hide();
        ui->phi->hide();
        ui->labelFreq->hide();
        ui->labelPhi->hide();
        ui->labelAmp->setText("DC Value[V] :");
    }
    else{
        ui->freq->setText(QString::number(vs->getFreq()));
        ui->amp->setText(QString::number(vs->getAmp()));
        ui->phi->setText(QString::number(vs->getPhi()));
        ui->freq->show();
        ui->phi->show();
        ui->labelFreq->show();
        ui->labelPhi->show();
        ui->labelAmp->setText("Amplitude[V] :");
    }
}

void vsourceDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::Modifier::CTRL && event->key() == Qt::Key_W){
        reject();
    }
    else if(event->key() == Qt::EnterKeyDone){
        accept();
    }

    QDialog::keyPressEvent(event);
}
