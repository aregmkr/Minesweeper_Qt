#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include "board.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start_game(int rows, int cols, int width, int heigth, int mines);
private slots:
    void handle_easy();
    void handle_medium();
    void handle_expert();
    void handle_home();

private:
    QWidget* menu_screen;
    QPushButton* easy;
    QPushButton* medium;
    QPushButton* expert;
    Board* game_board;
    QStackedWidget* widget_manager;

};
#endif // MAINWINDOW_H
