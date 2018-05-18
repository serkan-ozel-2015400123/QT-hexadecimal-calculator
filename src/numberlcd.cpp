#include "numberlcd.h"

numberlcd::numberlcd(QWidget *parent)
    : QLCDNumber(parent)
{

}
void numberlcd ::myDisplay(int x){
    QString a = QString::number(this->value()).append(QString(x));
    display(a);
}
