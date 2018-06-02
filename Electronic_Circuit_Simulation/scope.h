#ifndef SCOPE_H
#define SCOPE_H

#include <vector>
#include <QDialog>
#include "node.h"
#include "vsource.h"
#include "linear_component.h"
#include <QLabel>

namespace Ui {
class scope;
}

class scope : public QDialog
{
    Q_OBJECT

public:
    enum Status{open,close};
    explicit scope(QWidget *parent = 0);
    Status get_status();
    void setScope(std::vector<node*>nl,std::vector<vsource*>vl,std::vector<Linear_Component*>cl);
    ~scope();
public slots:
    void updateText(std::vector<QPointF> value);
    void reject();
    void drawNodeData(Electronic_Component *);
    void dropNodeData(Electronic_Component *);
    void reDraw();
    void resizeEvent(QResizeEvent *);
private:
    double minFreq;
    double scale;
    double t0;
    double step;
    std::vector<QLabel *> lable_list;
    std::vector<node *>node_list;
    std::vector<vsource *>vsource_list;
    std::vector<Linear_Component *>comp_list;
    Status status;
    Ui::scope *ui;
};

#endif // SCOPE_H
