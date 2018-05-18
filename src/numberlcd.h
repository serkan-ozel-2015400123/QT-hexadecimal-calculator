#ifndef NUMBERLCD_H
#define NUMBERLCD_H


#include <QLCDNumber>

class QLCDNumber;

class numberlcd : public QLCDNumber
{
    Q_OBJECT

public:
    numberlcd(QWidget *parent = 0);

private slots:
    void myDisplay(int x); // x is a integer to be appended
};

#endif // NUMBERLCD_H
