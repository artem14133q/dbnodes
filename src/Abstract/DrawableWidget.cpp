//
// Created by artem on 19.12.2020.
//

#include "DrawableWidget.h"
#include "QStyleOption"
#include "QPainter"
#include "QStyle"

namespace DbNodes::Abstract {

    DrawableWidget::DrawableWidget(QWidget *parent) : QWidget(parent) {}

    void DrawableWidget::paintEvent(QPaintEvent *)
    {
        QPainter p(this);
        QStyleOption opt;

        #if QT_VERSION_MAJOR == 6
        opt.initFrom(this);
        #else
        opt.init(this);
        #endif

        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

}