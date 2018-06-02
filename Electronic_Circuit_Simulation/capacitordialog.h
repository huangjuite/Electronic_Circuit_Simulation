#ifndef CAPACITORDIALOG_H
#define CAPACITORDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class capacitorDialog;
}

class capacitorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit capacitorDialog(QWidget *parent , double &);
    ~capacitorDialog();
    double *capacitance;
    void accept();
    void reject();
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::capacitorDialog *ui;
};

#endif // CAPACITORDIALOG_H
