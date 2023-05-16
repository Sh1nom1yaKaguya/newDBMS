#ifndef TABLEMANAGELOAD_H
#define TABLEMANAGELOAD_H

#include <QWidget>

namespace Ui {
class tablemanageload;
}

class tablemanageload : public QWidget {
    Q_OBJECT

public:

    explicit tablemanageload(QWidget *parent = nullptr);
    ~tablemanageload();

private slots:

    void on_updatetable_clicked();

    void on_deletetable_clicked();

    void on_creattable_clicked();

private:

    Ui::tablemanageload *ui;
};

#endif // TABLEMANAGELOAD_H
