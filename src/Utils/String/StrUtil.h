//
// Created by artem on 17.07.2021.
//

#ifndef DBNODES_STRUTIL_H
#define DBNODES_STRUTIL_H

#include "AbstractUtil.h"

namespace DbNodes::Utils::String {

    class StrUtil : public Utils::AbstractUtil
    {

    public:
        explicit StrUtil(QObject* object);

        static QString strLimit(const QString &string, int limit, const QString& replace = "...");
    };

}


#endif //DBNODES_STRUTIL_H
