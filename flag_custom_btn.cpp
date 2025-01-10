#include "flag_custom_btn.h"

Flag_Custom_Btn::Flag_Custom_Btn(QWidget *parent) : QPushButton(parent) {

}

void Flag_Custom_Btn::mousePressEvent(QMouseEvent *event)  {
    if (event->button() == Qt::RightButton) {
        emit rightClicked();
    } else {
        QPushButton::mousePressEvent(event);
    }
}
