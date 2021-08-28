//
// Created by artem on 26.12.2020.
//

#ifndef DBNODES_TABLERENAME_H
#define DBNODES_TABLERENAME_H

#include "AbstractSettingModal.h"

namespace DbNodes::Modals {

    class TableRename: public Abstract::AbstractSettingModal {
    Q_OBJECT

    public:
        enum Type {
            rename,
            create,
        };

    private:
        QLineEdit *nameLineEdit{};
        QString tableName;
        Type type;

    public:
         explicit TableRename(const Type& type, const QString& name, QWidget* parent = nullptr);

    protected:
        QString getTitle();

        void initSettingsUi() override;
        QVariant getDefaultSetting(const QString &name) override;

        void afterInitUi() override;

        void confirm() override;

    public: signals:

        void pushConfirm(const QString &name);
        void pushExit();
    };

}

#endif //DBNODES_TABLERENAME_H
