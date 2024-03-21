#ifndef TEST_WIN_H
#define TEST_WIN_H

#include <QDialog>
#include "answer_win.h"

//QT_BEGIN_NAMESPACE
namespace Ui {
class test_win;
}
//QT_END_NAMESPACE

class test_win : public QDialog
{
    Q_OBJECT

public:
    test_win(QWidget *parent = nullptr);
    ~test_win();

private slots:
    void on_close_win_butt_clicked();

    void on_view_answer_butt_clicked();

private:
    Ui::test_win *ui;
    answer_win *window;

};

#endif // TEST_WIN_H
