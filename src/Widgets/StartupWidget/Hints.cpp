//
// Created by artem on 26.12.2020.
//

#include "QVBoxLayout"
#include "QLabel"
#include "QStringList"

#include "Hints.h"
#include "../../helper.h"

namespace DbNodes::Widgets::StartupWidget {

    Hints::Hints(QWidget *parent): DbNodes::Abstract::DrawableWidget(parent)
    {
        setStyleSheet(Helper::getStyleFromFile("startupWidget"));

        initUi();
        adjustSize();

        show();
    }

    void Hints::initUi()
    {
        auto* vb = new QVBoxLayout(this);

        #if TARGET_OS_MAC
        auto file = ":/content/startup_macos";
        #else
        auto file = ":/content/startup";
        #endif

        auto content = Helper::getfileContent(file).split("\n");

        foreach (QString line, content) {
            vb->addWidget(new QLabel(line, this));
        }

        setLayout(vb);
    }
}