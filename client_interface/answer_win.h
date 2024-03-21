#ifndef ANSWER_WIN_H
#define ANSWER_WIN_H

#include <QDialog>

namespace Ui {
class answer_win;
}

class answer_win : public QDialog
{
    Q_OBJECT

public:
    explicit answer_win(QWidget *parent = nullptr);
    ~answer_win();

signals:
    void openTest();
private slots:
    void on_exit_butt_clicked();

    void on_cancel_butt_clicked();

private:
    Ui::answer_win *ui;

};

#endif // ANSWER_WIN_H
