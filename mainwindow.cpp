#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menu_screen(new QWidget(this)),
    easy(new QPushButton("Beginner", this)),
    medium(new QPushButton("Intermediate", this)),
    expert(new QPushButton("Expert", this)),
    game_board(nullptr),
    widget_manager(new QStackedWidget(this))
{

    QVBoxLayout* difficultyLayout = new QVBoxLayout(menu_screen);
    difficultyLayout->addWidget(easy);
    difficultyLayout->addWidget(medium);
    difficultyLayout->addWidget(expert);
    menu_screen->setLayout(difficultyLayout);

    widget_manager->addWidget(menu_screen);
    setCentralWidget(widget_manager);

    connect(easy, &QPushButton::clicked, this, &MainWindow::handle_easy);
    connect(medium, &QPushButton::clicked, this, &MainWindow::handle_medium);
    connect(expert, &QPushButton::clicked, this, &MainWindow::handle_expert);

    this->resize(300, 150);
}

void MainWindow::handle_home() {
    widget_manager->setCurrentWidget(menu_screen);
    this->resize(300, 150);
    qDebug() << "Returned to menu";
}

MainWindow::~MainWindow() {
    if (game_board) {
        widget_manager->removeWidget(game_board);
        delete game_board;
        game_board = nullptr;
    }
}

void MainWindow::start_game(int rows, int cols, int width, int heigth, int mines) {
    this->resize(width, heigth);

    if (game_board) {
        widget_manager->removeWidget(game_board);
        delete game_board;
    }
    game_board = new Board(rows, cols, mines, this);
    connect(game_board, &Board::home_clicked, this, &MainWindow::handle_home);
    widget_manager->addWidget(game_board);
    widget_manager->setCurrentWidget(game_board);


}

void MainWindow::handle_easy()
{
    start_game(9, 9, 260, 310, 10);
}

void MainWindow::handle_medium()
{
    start_game(12, 12, 340, 400, 20);
}

void MainWindow::handle_expert()
{
    start_game(16, 16, 430, 500, 30);
}
