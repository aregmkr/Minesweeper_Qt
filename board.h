#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "flag_custom_btn.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    Board(int x, int y, int mines, QWidget* parent = nullptr);
    ~Board();

signals:
    void home_clicked();

private:
    QGridLayout* cellss;
    int x;
    int y;
    int mines;
    QLabel* time;
    QLabel* emoji;
    QLabel* spended_time;
    QVBoxLayout* main_layout;
    QVector<QVector<Flag_Custom_Btn*>> matrix;
    QVector<QPair<int, int>> mines_index;
    QTimer* timer;
    int elapsed_time;
    QVector<QString> emojis;
    QPushButton *home;
private:
    void init();
    void setup();
    void connections();

    QPair<int, int> generate_rand_nums();

private slots:
    void handle_click(int row, int col);
    void update_time();
    void handle_home();
    void handle_flag(int i, int j);
private:
    bool check(int row, int col);
    void open_cells();
    void end();
    void open_surrounding_cells(int row, int col);
    int count_neighbours(int row, int col);
    void victory_check();

};

#endif // BOARD_H
