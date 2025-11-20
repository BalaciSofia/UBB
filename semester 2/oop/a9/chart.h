#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <map>

class chart : public QWidget
{
    Q_OBJECT
public:
    explicit chart(std::map<QString, int> breedCounts, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::map<QString, int> breedCounts;
};

#endif // CHARTT_H
