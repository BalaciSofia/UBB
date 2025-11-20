#include "adoptdog.h"
#include "ui_adoptdog.h"
#include "QMessageBox"
#include <iostream>
adoptdog::adoptdog(Dog dog,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::adoptdog)
    , dog(dog)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(dog.get_name())));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::number(dog.get_age())));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem(QString::fromStdString(dog.get_breed())));
    ui->labelDogImage->setScaledContents(true);
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &adoptdog::onImageDownloaded);
    QString photoPath = QString::fromStdString(dog.get_photograph());

    if (photoPath.startsWith("http")) {
        networkManager->get(QNetworkRequest(QUrl(photoPath)));
    } else {
        QPixmap pix;
        if (!pix.load(photoPath)) {
            ui->labelDogImage->setText("Image failed to load.");
        } else {
            ui->labelDogImage->setPixmap(pix.scaled(300, 200, Qt::KeepAspectRatio));
        }
    }

    // Connect buttons
    connect(ui->pushButtonAdopt, &QPushButton::clicked, this, &adoptdog::onAdoptClicked);
    connect(ui->pushButtonNotAdopt, &QPushButton::clicked, this, &adoptdog::onNotAdoptClicked);
}

void adoptdog::onImageDownloaded(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pix;
        if (pix.loadFromData(imageData)) {
            ui->labelDogImage->setPixmap(pix.scaled(300, 200, Qt::KeepAspectRatio));
        } else {
            ui->labelDogImage->setText("Failed to parse image.");
        }
    } else {
        ui->labelDogImage->setText("Image failed to load.");
    }
    reply->deleteLater();
}


void adoptdog::onAdoptClicked()
{
    emit dogAdopted(dog);  // emit signal
    QMessageBox::information(this, "Adoption", "You adopted " + QString::fromStdString(dog.get_name()));
    accept();
}

void adoptdog::onNotAdoptClicked()
{
    done(2);
}

adoptdog::~adoptdog()
{
    delete ui;
}
