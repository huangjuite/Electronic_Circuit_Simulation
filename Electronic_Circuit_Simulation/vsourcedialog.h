#ifndef VSOURCEDIALOG_H
#define VSOURCEDIALOG_H

#include <QDialog>
#include "vsource.h"
#include <complex>

class vsource;

namespace Ui {
class vsourceDialog;
}

class vsourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit vsourceDialog(vsource *vsIN);
    ~vsourceDialog();
    void accept();
    void reject();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void keyPressEvent(QKeyEvent *);
private:
    Ui::vsourceDialog *ui;
    vsource *vs;
};

#endif // VSOURCEDIALOG_H
