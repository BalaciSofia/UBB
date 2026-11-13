#ifndef DISPLAYDOGS_H
#define DISPLAYDOGS_H

#include <QWidget>

namespace Ui {
class displaydogs;
}

class displaydogs : public QWidget
{
    Q_OBJECT

public:
    explicit displaydogs(QWidget *parent = nullptr);
    ~displaydogs();

private:
    Ui::displaydogs *ui;
};

#endif // DISPLAYDOGS_H
