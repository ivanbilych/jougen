#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <aboutWindow.hpp>
#include <ingridients.hpp>
#include <dishWindow.hpp>
#include <ingridientWindow.hpp>

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    enum InfoType {
        ITEM,
        FOOD,
        DISH,
        NONE
    };

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_listView_1_clicked(const QModelIndex& index);
    void on_listView_2_clicked(const QModelIndex& index);
    void on_listView_1_entered(const QModelIndex& index);
    void on_listView_2_entered(const QModelIndex& index);
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

public slots:
    void addNewItemObject(Item* item);
    void addNewFoodObject(Food* food);
    void addNewDishObject(Dish* dish);

signals:
    void newDishRequest(std::list<Item*>* itemList);

private:
    Ui::MainWindow* ui;
    InfoType infoWindowType {NONE};
    QStringList* itemStringList {};
    QStringList* dishStringList {};
    QStringListModel* itemListModel {};
    QStringListModel* dishListModel {};
    Ingridients* ingridients {};

    void editItem(QModelIndexList& selected);
    void editDish(QModelIndexList& selected);
    void displayListViewInfoItem(const QModelIndex& index);
    void displayListViewInfoDish(const QModelIndex& index);
    void redrawItemList(void);
    void redrawDishList(void);
};

QString priceToQString(uint64_t price);
QString massToQString(uint64_t mass);
QString fatsToQString(uint64_t fats);
QString proteinsToQString(uint64_t proteins);

#endif // MAINWINDOW_H
