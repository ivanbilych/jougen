#ifndef NEWDISHWINDOW_H
#define NEWDISHWINDOW_H

#include <QDialog>
#include <QStringListModel>

#include <item.hpp>
#include <food.hpp>
#include <dish.hpp>

namespace Ui {
    class NewDishWindow;
}

class NewDishWindow : public QDialog {
    Q_OBJECT

public:
    explicit NewDishWindow(QWidget *parent = 0);
    ~NewDishWindow();

signals:
    void itemObjectReady(Dish *dish);

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();

public slots:
    void fillItemList(std::list<Item *> *itemsList);

private:
    Ui::NewDishWindow *ui;
    QStringList *foodStringList {};
    QStringListModel *itemListModel {};

    Dish* createNewDish(void);
};

#endif // NEWDISHWINDOW_H
