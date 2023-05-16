#ifndef DELETETABLE_H
#define DELETETABLE_H

#include <QWidget>

namespace Ui {
class deletetable;
}

class deletetable : public QWidget {
    Q_OBJECT

public:

    explicit deletetable(QWidget *parent = nullptr);
    ~deletetable();

private slots:

    void on_deleButton_clicked();

    void on_quitButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::deletetable *ui;
};

#endif // DELETETABLE_H
