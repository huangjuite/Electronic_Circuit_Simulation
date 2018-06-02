#include "electronic_component.h"

Electronic_Component::Electronic_Component():
    QObject(NULL)
{
    count++;
    ID = count;
}

Electronic_Component::~Electronic_Component()
{
    emit die();
}

int Electronic_Component::getID()
{
    return ID;
}
