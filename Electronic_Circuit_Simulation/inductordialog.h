#ifndef INDUCTORDIALOG_H
#define INDUCTORDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class inductorDialog;
}

class inductorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inductorDialog(QWidget *parent, double &);
    ~inductorDialog();
    double *inductance;
    void accept();
    void reject();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::inductorDialog *ui;
};

#endif // INDUCTORDIALOG_H
