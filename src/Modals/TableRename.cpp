//
// Created by artem on 26.12.2020.
//

#include "TableRename.h"
#include "QString"
#include "QLabel"
#include "QLineEdit"

namespace DbNodes::Modals {

    TableRename::TableRename(const Type& type, const QString &name, QWidget *parent)
        : Abstract::AbstractSettingModal(parent), tableName(name), type(type) {
        setFixedWidth(500);
        setWindowTitle(QString(getTitle()).arg(name));

        prepareWidget();

        show();
    }

    void TableRename::initSettingsUi() {
        nameLineEdit = createTextSetting("Name:", "name");

        // Create buttons

        createButton("Cancel", this, [this] {
            emit pushExit();
            exit();
        });

        createButton("Ok", this, [this] {
            confirm();
        });
    }

    QVariant TableRename::getDefaultSetting(const QString &name) {
        return tableName;
    }

    void TableRename::confirm() {
        emit pushConfirm(newSettingsMap.value("name").toString());

        enableConfirm(true);
        Abstract::AbstractSettingModal::confirm();
    }

    void TableRename::afterInitUi() {
        nameLineEdit->setFocus();
        nameLineEdit->selectAll();
    }

    QString TableRename::getTitle() {
        switch (type) {
            case rename:
                return "Rename table: %1";
            case create:
                return "Create table: %1";
        }
    }
}