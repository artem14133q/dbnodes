//
// Created by artem on 25.06.2021.
//

#include "TableGeneratorUtil.h"
#include "../helper.h"

namespace DbNodes::Utils::TableGenerator {

    TableGeneratorUtil::TableGeneratorUtil(QWidget *parentWidget, const QString& name): AbstractUtil(parentWidget)
    {
        table = new Nodes::TableNode(parentWidget, name);
    }

    TableGeneratorUtil::TableGeneratorUtil(QWidget *parentWidget, Nodes::TablePtr& table):
    AbstractUtil(parentWidget), table(table) {}

    TableGeneratorUtil::TableGeneratorUtil(Nodes::TableNode *table):
    AbstractUtil(table), table(QPointer<Nodes::TableNode>(table)) {}

    TableGeneratorUtil *TableGeneratorUtil::makeTable(QWidget *parent, const QString& name)
    {
        return new TableGeneratorUtil(parent, name);
    }

    TableGeneratorUtil *TableGeneratorUtil::fillTable(QWidget *parent, Nodes::TablePtr& table)
    {
        return new TableGeneratorUtil(parent, table);
    }

    TableGeneratorUtil *TableGeneratorUtil::fillTable(Nodes::TableNode* table)
    {
        return new TableGeneratorUtil(table);
    }

    void TableGeneratorUtil::createColumn(
        const ColumnType &columnType,
        const QString &name,
        const QString& dbType,
        const bool isNull
    ) {
        auto databaseType = dbType == nullptr
                ? IndexTypesDictionary::getDictionary().value(determinateColumnType(columnType)).toString()
                : dbType;

        table->createColumn(Table::generateId(), name, columnType, databaseType, isNull);
    }

    IndexTypesDictionary::Type TableGeneratorUtil::determinateColumnType(const ColumnType &columnType)
    {
        if (columnType == ColumnType::PrimaryKey) {
            return (IndexTypesDictionary::Type) StandardTypes::Index;
        }

        if (columnType == ColumnType::ForeignKey) {
            return (IndexTypesDictionary::Type) StandardTypes::Foreign;
        }

        return (IndexTypesDictionary::Type) StandardTypes::Default;
    }

    TableGeneratorUtil *TableGeneratorUtil::createIndexColumn(const QString& name, bool isNull)
    {
        createColumn(ColumnType::PrimaryKey, name, nullptr, isNull);

        return this;
    }

    TableGeneratorUtil *TableGeneratorUtil::createForeignColumn(const QString& name, bool isNull)
    {
        createColumn(ColumnType::ForeignKey, name, nullptr, isNull);

        return this;
    }

    TableGeneratorUtil *TableGeneratorUtil::createDefaultColumn(const QString &name, const QString &dbType, bool isNull)
    {
        createColumn(ColumnType::Default, name, dbType, isNull);

        return this;
    }

    Nodes::TablePtr TableGeneratorUtil::getTable()
    {
        return table;
    }
}
