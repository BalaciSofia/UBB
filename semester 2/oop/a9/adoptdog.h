#ifndef ADOPTDOG_H
#define ADOPTDOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "domain.h"

namespace Ui {
class adoptdog;
}

class adoptdog : public QDialog
{
    Q_OBJECT

public:
    explicit adoptdog(Dog dog,QWidget *parent = nullptr);
    ~adoptdog();

signals:
    void dogAdopted(Dog dog);

private slots:
    void onImageDownloaded(QNetworkReply* reply);
    void onAdoptClicked();
    void onNotAdoptClicked();

private:
    Ui::adoptdog *ui;
    Dog dog;
    QNetworkAccessManager* networkManager;
};

#endif // ADOPTDOG_H
