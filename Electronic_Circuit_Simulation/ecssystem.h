#ifndef ECSSYSTEM_H
#define ECSSYSTEM_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <vector>
#include <QMessageBox>

#include "scope.h"
#include "ecssystem.h"
#include "ui_ecssystem.h"
#include "electronic_component.h"
#include "inductor.h"
#include "capacitor.h"
#include "resistor.h"
#include "node.h"
#include "vsource.h"
#include "workspace.h"
#include "customscene.h"
#include "mna.h"


namespace Ui {
class ECSsystem;
}

class ECSsystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit ECSsystem(QWidget *parent = 0);
    ~ECSsystem();

    void keyPressEvent(QKeyEvent *event);
        


private slots:

    void on_OpenScopeButton_clicked();

    void on_resistorButton_clicked();

    void on_capacitorButton_clicked();

    void on_inductorButton_clicked();

    void on_clearButton_clicked();

    void on_groundButton_clicked();

    void addingNode(node *nd);

    void removingNode(node *nd);

    void objectMoving();

    void on_vsourceButton_clicked();

private:
    MNA calculator;
    Ui::ECSsystem *ui;
    scope *scopeDialog;
    customScene *scene;
    int mToggle = -1;

    std::vector<Linear_Component *> component_list;
    std::vector<node *> node_list;
    std::vector<vsource *> vsource_list;

};

#endif // ECSSYSTEM_H

