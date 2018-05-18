#include "mylcd.h"
#include "resultButton.h"


mylcd::mylcd(QWidget * parent)
    : QLCDNumber(parent)
{


}

void mylcd::mydisplay(int value){



    int result = this->value();

    if(state == 0){
        if(this->mode() == Dec && value < 10){
            result= 10*this->value()+value;
        }else if(this->mode()== Hex){
            result= 16*this->value()+value;
        }
        display(result);

        if(this->objectName() == QString("screen1")){ // Propagate information for calculation
            resultButton::number1 = result;

        }else if(this->objectName() == QString("screen2")){
            resultButton::number2 = result;
        }


    }
}
void mylcd::toggleMode(){

    display(0);

    if(this->mode() == Dec){
        setHexMode();
    }else if(this->mode() == Hex){
        setDecMode();
    }

}
void mylcd::setActive(){
    state = 0;
}
void mylcd::setDeactive(){
    state = 1;
}
void mylcd::showResult(){
    display(resultButton::result);
}
void mylcd::clear(){
    display(0);
    if(this->objectName() == QString("screen1")){ // Propagate information for calculation
        state = 0;

    }else if(this->objectName() == QString("screen2")){
        state = 1;
    }
}
