#include "board.h"
#include <QRandomGenerator>
#include <QPair>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>


Board::Board(int x, int y, int mines, QWidget* parent)
    :QWidget(parent),
    x(x),
    y(y),
    mines(mines),
    matrix(x, QVector<Flag_Custom_Btn *>(y, nullptr))
{
    init();
    setup();
    connections();
}

Board::~Board() {}

void Board::init() {
    home = new QPushButton(this);
    home->setText("Home");
    connect(home, &QPushButton::clicked, this, &Board::handle_home);

    emojis = { "1", "2", "3", "4", "5", "6", "7", "8" };
    main_layout = new QVBoxLayout();
    cellss = new QGridLayout();

    time = new QLabel("0", this);
    time->setAlignment(Qt::AlignLeft);

    emoji = new QLabel("😐", this);
    emoji->setAlignment(Qt::AlignCenter);

    spended_time = new QLabel("000", this);
    spended_time->setAlignment(Qt::AlignRight);

    timer = new QTimer(this);
    elapsed_time = 0;
    connect(timer, &QTimer::timeout, this, &Board::update_time);

    QHBoxLayout *top_layout = new QHBoxLayout();
    top_layout->addWidget(time, 1, Qt::AlignLeft);
    top_layout->addWidget(emoji, 1, Qt::AlignCenter);
    top_layout->addWidget(spended_time, 1, Qt::AlignRight);

    main_layout->addLayout(top_layout);
    main_layout->addLayout(cellss);
    main_layout->addWidget(home);

    setLayout(main_layout);

    timer->start(1000);
}

void Board::update_time() {
    ++elapsed_time;
    spended_time->setText(QString::asprintf("%03d", elapsed_time));
}

QPair<int, int> Board::generate_rand_nums() {
    QPair<int, int> nums;
    do {
        nums.first = QRandomGenerator::global()->bounded(0, x);
        nums.second = QRandomGenerator::global()->bounded(0, y);
    } while (mines_index.contains(nums));
    return nums;
}

void Board::setup()
{
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            Flag_Custom_Btn* btn = new Flag_Custom_Btn(this); // qaq
            btn->setFixedSize(25, 25);
            matrix[i][j] = btn;
            cellss->addWidget(matrix[i][j], i, j);
        }
    }

    for (int z = 0; z < mines; ++z) {
        QPair tmp = generate_rand_nums();
        mines_index.append(tmp);
        // matrix[tmp.first][tmp.second]->setText("*");
    }
}

bool Board::check(int row, int col) {
    for (int i = 0; i < mines_index.size(); ++i) {
        if (row == mines_index[i].first && col == mines_index[i].second) {
            return true;
        }
    }
    return false;
}

void Board::open_surrounding_cells(int row, int col)
{
    QSet<QPair<int, int>> visited;
    QPair<int, int> cell(row, col);

    if (visited.contains(cell)) {
        return;
    }
    visited.insert(cell);

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            int new_row = row + i;
            int new_col = col + j;
            if (new_row >= 0 && new_row < x && new_col >= 0 && new_col < y && matrix[new_row][new_col]->isEnabled()) {
                handle_click(new_row, new_col);
            }
        }
    }
}

int Board::count_neighbours(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            int new_row = row + i;
            int new_col = col + j;

            if (new_row >= 0 && new_row < x && new_col >= 0 && new_col < y) {
                if (check(new_row, new_col)) {
                    ++count;
                }
            }
        }
    }
    return count;
}

void Board::handle_click(int row, int col) {
    if (check(row, col) == true) {
        end();
    } else {
        int count = count_neighbours(row, col);
        emoji->setText("😊");
        matrix[row][col]->setEnabled(false);

        if (count > 0) {
            matrix[row][col]->setText(emojis[count - 1]);
        } else {
            matrix[row][col]->setText(" ");
            open_surrounding_cells(row, col);
        }
        victory_check();
    }
}

void Board::end() {
    emoji->setText("😔");
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (check(i, j)) {
                matrix[i][j]->setText("💣");
            }
            matrix[i][j]->setEnabled(false);
        }
    }
    timer->stop();
}

void Board::handle_home() {
    this->setFixedSize(300, 150);
    emit home_clicked();
    qDebug() << "its worked";
}

void Board::handle_flag(int i, int j) {
    matrix[i][j]->setText("F");
}

void Board::connections()
{
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            connect(matrix[i][j], &QPushButton::clicked, [this, i, j]() {
                handle_click(i, j);
            });
            connect(matrix[i][j], &Flag_Custom_Btn::rightClicked, [this, i, j]() {
                handle_flag(i, j);
            });
        }
    }
}

void Board::victory_check() {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (check(i, j) == false && matrix[i][j]->isEnabled()) {
                return;
            }
        }
    }
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (check(i, j)) {
                matrix[i][j]->setText("💣");
            }
            matrix[i][j]->setEnabled(false);
        }
    }
    emoji->setText("😎");
    timer->stop();
}
