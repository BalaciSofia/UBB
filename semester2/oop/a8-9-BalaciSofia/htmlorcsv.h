#ifndef HTMLORCSV_H
#define HTMLORCSV_H

#include <QDialog>

namespace Ui {
class htmlorcsv;
}

class htmlorcsv : public QDialog  // ✅ Inherit from QDialog
{
    Q_OBJECT

public:
    explicit htmlorcsv(QWidget *parent = nullptr);
    ~htmlorcsv();

    QString getChoice() const;  // ✅ Make this public

private slots:
    void on_htmlButton_clicked();
    void on_csvButton_clicked();

private:
    Ui::htmlorcsv *ui;
    QString selectedChoice;  // ✅ Now a member of the class
};

#endif // HTMLORCSV_H
