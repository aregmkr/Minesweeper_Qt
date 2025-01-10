#ifndef FLAG_CUSTOM_BTN_H
#define FLAG_CUSTOM_BTN_H

#include <QPushButton>
#include <QMouseEvent>

class Flag_Custom_Btn : public QPushButton {
    Q_OBJECT
public:
    explicit Flag_Custom_Btn(QWidget *parent = nullptr);
    ~Flag_Custom_Btn() {}
protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void rightClicked();
};

#endif // FLAG_CUSTOM_BTN_H
