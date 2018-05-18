#ifndef MYLCD_H
#define MYLCD_H

#include <resultButton.h>
#include <QLCDNumber>



class mylcd : public QLCDNumber {
    Q_OBJECT
public:
    int state;
    mylcd(QWidget * parent =0);


private slots:
    void mydisplay(int value);
    void toggleMode();
    void setDeactive();
    void setActive();
    void showResult();
    void clear();
};


#endif // MYLCD_H
