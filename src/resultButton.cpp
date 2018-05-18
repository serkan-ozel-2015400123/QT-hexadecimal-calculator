#include "resultButton.h"
#include <climits>
resultButton::resultButton(QWidget * parent) : QPushButton(parent)
{

}


int resultButton::result;
int resultButton::number1;
int resultButton::number2;
int resultButton::operation;

void resultButton::calculate(){


    if(this->operation == 0){
        this->result = this->number1 + this->number2;
    }else if(this->operation == 1){ // no chance of reaching the limit
        this->result = this->number1 - this->number2;
    }else if(this->operation == 2){
        if(this->number1 * this->number2 > 0 && this->number1 * this->number2 <= INT_MAX){
            this->result = this->number1 * this->number2;
        }else{
            emit intLimit();
        }
    }else if(this->operation == 3){

        if (this->number2!=0){
            this->result = this->number1 / this->number2;
        }else{
            emit divisionByZero();
        }


    }
    emit calculated();
}
void resultButton::setNumberOne(int value){
    number1=value;
}
void resultButton::setNumberTwo(int value){
    number2= value;
}
void resultButton::setOperation(int index){
    operation = index;
    QString op;
    switch (index) {
    case 0:
        op = QString("Sum");
        break;
    case 1:
        op = QString("Subtract");
        break;
    case 2:
        op = QString("Multiply");
        break;
    case 3:
        op = QString("Divide");
        break;
    }
}
void resultButton::resetVariables(){
    operation=0;
    number1=0;
    number2=0;
    result=0;
}
