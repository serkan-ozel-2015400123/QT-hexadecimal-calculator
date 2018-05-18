#include <QPushButton>
#include <QString>

#ifndef RESULTBUTTON_H
#define RESULTBUTTON_H


class resultButton : public QPushButton
{
    Q_OBJECT
public:
    static int number1;
    static int number2;
    static int result;
    static int operation;
public:
    resultButton(QWidget* parent=0);

signals:
    void intLimit();
    void divisionByZero();
    void calculated();
private slots:
    void calculate();
    void setNumberOne(int value);
    void setNumberTwo(int value);
    void setOperation(int index);
    void resetVariables();

};

#endif // RESULTBUTTON_H
