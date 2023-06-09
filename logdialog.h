#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog {
    Q_OBJECT

public:

    explicit LogDialog(QWidget *parent = nullptr);
    ~LogDialog();

    void showlog();

private slots:

    void on_pushButton_clicked();

private:

    Ui::LogDialog *ui;
};

#endif // LOGDIALOG_H
