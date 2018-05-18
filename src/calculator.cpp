#include "calculator.h"
#include "ui_calculator.h"
#include "mylcd.h"
#include "resultButton.h"
#include "modelabel.h"
#include "operationlabel.h"
#include <QApplication>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QMessageBox>
#include <QFont>

class values{
public:
    static int result;
    static int number1;
    static int number2;
};


int main(int argc,char* argv[]){



    QApplication app(argc,argv);
    QWidget window;
    QVBoxLayout mainLayout;
    QGridLayout numberGrid;
    QVBoxLayout operationLayout;
    QButtonGroup operationButtongroup;
    QButtonGroup numberButtongroup;
    QPushButton * operButtons[4]; // operations buttons of the calc
    QPushButton * modButton;
    QPushButton * clearButton;
    QPushButton * numberButtons[16];
    resultButton calculate;
    QHBoxLayout modeButtonModeLabel;
    modeLabel modeStatus;
    operationLabel operationStatus;
    mylcd screen1;
    mylcd screen2;
    mylcd result;
    QMessageBox * divisionByZeroMessageBox;
    QMessageBox * intLimitMessageBox;
    divisionByZeroMessageBox = new QMessageBox();
    intLimitMessageBox = new QMessageBox();
    divisionByZeroMessageBox->setText("You cannot divide a number by 0. The calculator will be reset.");
    intLimitMessageBox->setText("Cannot store this number: integer limit has exceeded");


    QFont f=calculate.font();
    f.setBold(true);
    f.setPixelSize(24);
    calculate.setFont(f);



    QStringList opStrings(QStringList() << QString("+") << QString("-") << QString("*") << QString("/"));
    // add operation buttons to widget
    for(int i=0;i<4;i++){
        operButtons[i] = new QPushButton(opStrings.at(i)); // 0 +,1 -,2 *, 3/
        operButtons[i]->setFont(f);
        operationLayout.addWidget(operButtons[i]);
        operationButtongroup.addButton(operButtons[i],i);
    }

    QStringList numberStrings(QStringList() << QString("0") << QString("1") << QString("2") << QString("3")<<QString("4") << QString("5") << QString("6") << QString("7")<<QString("8") << QString("9") << QString("A") << QString("B")<<QString("C") << QString("D") << QString("E") << QString("F"));
    // add number buttons to widget
    for(int i=0;i<16;i++){
        numberButtons[i] = new QPushButton(numberStrings.at(i)); // 0 +,1 -,2 *, 3/
        numberButtons[i]->setFont(f);
        numberGrid.addWidget(numberButtons[i],i/4+1,i%4+1);
        numberButtongroup.addButton(numberButtons[i],i);
    }

    clearButton = new QPushButton("C&lear");
    clearButton->setFont(f);
    modButton = new QPushButton("&Change Mode");
    modButton->setFont(f);
    modeStatus.setFont(f);
    operationStatus.setFont(f);
    screen1.setPalette(Qt::black);
    screen2.setPalette(Qt::black);
    result.setPalette(Qt::black);

    calculate.setText("=");
    modeButtonModeLabel.addWidget(modButton);
    modeButtonModeLabel.addWidget(&modeStatus);
    mainLayout.addWidget(&screen1);
    mainLayout.addWidget(&screen2);
    mainLayout.addWidget(&result);
    mainLayout.addLayout(&numberGrid);
    mainLayout.addLayout(&operationLayout);
    mainLayout.addLayout(&modeButtonModeLabel);


    screen1.setObjectName("screen1");
    screen2.setObjectName("screen2");
    screen2.state = 1; // Deactive
    screen1.state= 0;  // Active

    QObject::connect(&numberButtongroup,SIGNAL(buttonClicked(int)),&screen1,SLOT(mydisplay(int))); // This appends number to lcd

    QObject::connect(&numberButtongroup,SIGNAL(buttonClicked(int)),&screen2,SLOT(mydisplay(int))); // This appends number to lcd

    QObject::connect(modButton,SIGNAL(clicked()),&screen1,SLOT(toggleMode())); // Toggle mode between hex and decimal
    QObject::connect(modButton,SIGNAL(clicked()),&screen2,SLOT(toggleMode())); // lcds..
    QObject::connect(modButton,SIGNAL(clicked()),&result,SLOT(toggleMode()));
    QObject::connect(modButton,SIGNAL(clicked()),&modeStatus,SLOT(toggle())); // and the label changes
    QObject::connect(modButton,SIGNAL(clicked()),&calculate,SLOT(resetVariables())); // Also reset the variables inside calculate button
    QObject::connect(modButton,SIGNAL(clicked()),&operationStatus,SLOT(resetOp())); // change operation label to +

    QObject::connect(&operationButtongroup,SIGNAL(buttonClicked(int)),&screen1,SLOT(setDeactive())); // Transition between screen 1 to screen 2
    QObject::connect(&operationButtongroup,SIGNAL(buttonClicked(int)),&screen2,SLOT(setActive()));
    QObject::connect(&operationButtongroup,SIGNAL(buttonClicked(int)),&calculate,SLOT(setOperation(int))); // when a operation button is clicked set operation variable inside resultButton.cpp
    QObject::connect(&operationButtongroup,SIGNAL(buttonClicked(int)),&operationStatus,SLOT(changeOp(int))); // change current operator label


    QObject::connect(&calculate,SIGNAL(divisionByZero()),divisionByZeroMessageBox,SLOT(exec())); // if second number is 0 show a message
    QObject::connect(&calculate,SIGNAL(intLimit()),intLimitMessageBox,SLOT(exec())); // if result is bigger than 2147483647 show a message

    QObject::connect(&calculate,SIGNAL(clicked()),&calculate,SLOT(calculate())); // when = clicked trigger calculate inside itself

    QObject::connect(&calculate,SIGNAL(clicked()),&screen1,SLOT(clear())); // when = pressed lcd1 and lcd2 cleared
    QObject::connect(&calculate,SIGNAL(clicked()),&screen2,SLOT(clear()));

    QObject::connect(&calculate,SIGNAL(clicked()),&calculate,SLOT(resetVariables())); // when = pressed everthing is cleared
    QObject::connect(&calculate,SIGNAL(clicked()),&operationStatus,SLOT(resetOp())); // because operator is now + change label

    QObject::connect(&calculate,SIGNAL(calculated()),&result,SLOT(showResult())); // trigger for result lcd after calculation

    QObject::connect(clearButton,SIGNAL(clicked()),&screen1,SLOT(clear())); // Clear button clears three lcd's
    QObject::connect(clearButton,SIGNAL(clicked()),&screen2,SLOT(clear()));
    QObject::connect(clearButton,SIGNAL(clicked()),&result,SLOT(clear()));
    QObject::connect(clearButton,SIGNAL(clicked()),&calculate,SLOT(resetVariables())); // Clear also reset varaibles
    QObject::connect(clearButton,SIGNAL(clicked()),&operationStatus,SLOT(resetOp())); // and changes operation variable

    mainLayout.addWidget(&calculate);
    mainLayout.addWidget(clearButton);
    mainLayout.addWidget(&operationStatus);

    screen1.setStyleSheet("background-color:black;");
    screen2.setStyleSheet("background-color:black;");
    result.setStyleSheet("background-color:black;");

    window.setLayout(&mainLayout); // set layout of the QWidget as QVBoxLayout
    window.resize(500,750);
    window.show();

    return app.exec();

}
