#include <QLabel>

#ifndef OPERATIONLABEL_H
#define OPERATIONLABEL_H


class operationLabel: public QLabel
{
    Q_OBJECT

public:
    operationLabel(QWidget * parent=0);
private slots:
    void changeOp(int value);
    void resetOp();
};
#endif // OPERATIONLABEL_H
