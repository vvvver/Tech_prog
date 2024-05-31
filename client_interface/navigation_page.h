#ifndef NAVIGATION_PAGE_H
#define NAVIGATION_PAGE_H

#include <QWidget>

namespace Ui {
class Navigation_page;
}

class Navigation_page : public QWidget
{
    Q_OBJECT

public:
    explicit Navigation_page(QWidget *parent = nullptr);
    ~Navigation_page();

    QString userLog;
    QString graph;
private slots:
    // \brief слот реагирующий на открытие первого задания
    void on_task1_Button_clicked();

    // \brief слот реагирующий на выход из первого задания
    void on_exit1_Button_clicked();

    // \brief слот реагирующий на открытие второго задания
    void on_task2_Button_clicked();

    // \brief слот реагирующий на кнопку выхода к меню
    void on_exit_home_clicked();

    // \brief слот реагирующий на кнопку назад
    void on_exitButton_clicked();

    // \brief слот открывающий статистику
    void on_stat_Button_clicked();

    // \brief слот реагирующий на кнопку назад
    void on_exit_Button_clicked();

    // \brief слот реагирующий на открытие первого задания
    void on_submit_task1_button_clicked();

    // \brief слот реагирующий на открытие второго задания
    void on_submit_task2_Button_clicked();

private:
    Ui::Navigation_page *ui;

//public slots:
  //  void slot();
};

#endif // NAVIGATION_PAGE_H
