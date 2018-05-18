#include "modelabel.h"

bool modeLabel::showHex;

modeLabel::modeLabel(QWidget* parent): QLabel(parent)
{
    setText("Mode: Decimal");
    showHex=false;

}
void modeLabel::toggle(){
    if(!showHex){
        setText(QString("Mode: Hexadecimal"));
    }else{
        setText(QString("Mode: Decimal"));
    }
    showHex = !showHex;
}
