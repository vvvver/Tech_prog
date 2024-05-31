#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_reg.h"
#include "navigation_page.h"
//#include "func_for_client.h"
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    // \brief слот реагирующий на кнопку авторизации
    void on_authButton_clicked();

    // \brief слот реагирующий на кнопку регистрации
    void on_regButton_clicked();

private:

    QString userLog;
    Ui::MainWindow *ui;
    Dialog_reg *window;
    Navigation_page *nav_win;
signals:
    void open_nav();
};


#endif // MAINWINDOW_H
