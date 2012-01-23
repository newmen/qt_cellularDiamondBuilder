#include "zslider.h"

ZSlider::ZSlider(QWidget *parent, int max_value) : QSlider(Qt::Vertical, parent) {
    setTickPosition(QSlider::TicksBothSides);
    setTickInterval(2);
    setSingleStep(1);
    setMinimum(0);
    setMaximum(max_value);
}
