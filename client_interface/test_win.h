#ifndef TEST_WIN_H
#define TEST_WIN_H

#include <QDialog>

namespace Ui {
class test_win;
}

class test_win : public QDialog
{
    Q_OBJECT

public:
    explicit test_win(QWidget *parent = nullptr);
    ~test_win();

private:
    Ui::test_win *ui;
};

#endif // TEST_WIN_H
