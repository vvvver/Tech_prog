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
private slots:
    void on_task1_Button_clicked();

    void on_exit1_Button_clicked();

    void on_task2_Button_clicked();

    void on_exit_home_clicked();

    void on_exitButton_clicked();

    void on_stat_Button_clicked();

    void on_exit_Button_clicked();

    void on_submit_task1_button_clicked();

    void on_submit_task2_Button_clicked();

private:
    Ui::Navigation_page *ui;

//public slots:
  //  void slot();
};

#endif // NAVIGATION_PAGE_H
