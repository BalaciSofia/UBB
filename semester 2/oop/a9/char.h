#ifndef CHART_H
#define CHART_H

#include <QWidget>

namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr);
    ~char();

private:
    Ui::chart *ui;
};

#endif // CHART_H
