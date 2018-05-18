#include "operationlabel.h"

operationLabel::operationLabel(QWidget* parent): QLabel(parent)
{
        setText("Operation: +");
}

void operationLabel::changeOp(int value){
    if(value==0){
        setText("Operation: +");
    }else if(value==1){
        setText("Operation: -");
    }else if(value==2){
        setText("Operation: *");
    }else if(value==3){
        setText("Operation: /");
    }
}
void operationLabel::resetOp(){
    setText("Operation: +");
}
