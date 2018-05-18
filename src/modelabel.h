#include <QLabel>
#ifndef MODELABEL_H
#define MODELABEL_H


class modeLabel: public QLabel
{
    Q_OBJECT

public:
    modeLabel(QWidget * parent=0);
    static bool showHex;
private slots:
    void toggle();
};

#endif // MODELABEL_H
