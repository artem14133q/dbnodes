//
// Created by artem on 17.07.2021.
//

#include <QApplication>

#include "StrUtil.h"

namespace DbNodes::Utils::String {

    StrUtil::StrUtil(QObject *object) : Utils::AbstractUtil(object) {}

    QString StrUtil::strLimit(const QString &string, int limit, const QString& replace)
    {
        if (string.length() <= limit) {
            return string;
        }

        return string.mid(0, limit).append(replace);
    }

}
