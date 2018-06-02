#ifndef RESISTORDIALOG_H
#define RESISTORDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class resistorDialog;
}

class resistorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit resistorDialog(QWidget *parent,double&);
    ~resistorDialog();
    double *resistance;
    void accept();
    void reject();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::resistorDialog *ui;
};

#endif // RESISTORDIALOG_H
