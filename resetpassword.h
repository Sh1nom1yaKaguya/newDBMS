#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QWidget>

namespace Ui {
class resetpassword;
}

class resetpassword : public QWidget {
    Q_OBJECT

public:

    explicit resetpassword(QWidget *parent = nullptr);
    ~resetpassword();

private slots:

    void on_modifyButton_clicked();

    void on_exitButton_clicked();

private:

    Ui::resetpassword *ui;
    QString path;

    bool checkLog(QString,
                  QString,
                  QString);
    void getDbList();
};

#endif // RESETPASSWORD_H
