#ifndef DISHWINDOW_H
#define DISHWINDOW_H

#include <dish.hpp>
#include <food.hpp>
#include <item.hpp>

#include <QDialog>
#include <QStringListModel>

namespace Ui {
    class DishWindow;
}

class DishWindow : public QDialog {
    Q_OBJECT

public:
    explicit DishWindow(QWidget* parent = 0);
    explicit DishWindow(Dish* dish, QWidget* parent = 0);
    ~DishWindow();

signals:
    void itemObjectReady(Dish* dish);

private slots:
    void on_buttonBox_1_accepted();
    void on_buttonBox_1_rejected();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();

public slots:
    void fillItemList(std::list<Item*>* itemsList);

private:
    Ui::DishWindow* ui;
    QStringList* foodStringList {};
    QStringListModel* itemListModel {};
    Dish* dish {};
    std::list<Item*>* avaliableItemsList;
    std::list<Food*> dishFoodList;
    bool editMode {false};
    uint64_t oldAmountOfPeople {};

    Dish* createNewDish(void);
    void applyStats(Dish* dish);
};

#endif // DISHWINDOW_H
