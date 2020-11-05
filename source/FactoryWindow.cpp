//
// Created by nicolas on 31/10/2020.
//

#include "header/FactoryWindow.h"
#include <QWidget>
#include <QtSql/QSqlTableModel>
#include <QtWidgets/QTableView>
#include <QDebug>
#include <QSqlError>
#include <QtWidgets/QLabel>
#include <QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtSql/QSqlQuery>

FactoryWindow::FactoryWindow(QWidget *parent)
        : QWidget(parent)
{
    m_Layout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    m_Model = new QSqlTableModel(this);
    m_Model->setTable("factory");
    m_Model->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_Model->select();
    m_Model->setHeaderData(0, Qt::Horizontal, tr("id"));
    m_Model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    m_Model->setHeaderData(2, Qt::Horizontal, tr("Dropping"));

    qDebug() << m_Model->lastError().text();

    auto view = new QTableView(this);
    view->setModel(m_Model);

    m_Layout->addWidget(view);
    createAddWidg();
    createDelWidg();

    auto close_button = new QPushButton("Close", this);
    connect(close_button, &QPushButton::clicked, [this](){
        emit close_signal();
    });
    m_Layout->addWidget(close_button);

    setLayout(m_Layout);
}

void FactoryWindow::createAddWidg()
{
    auto widget = new QWidget(this);

    auto layout = new QHBoxLayout(widget);

    auto id_label = new QLabel("ID", widget);
    auto id_field = new QLineEdit(widget);
    id_field->setValidator(new QIntValidator(0,1111,this));
    auto name_label = new QLabel("Name", widget);
    auto name_field = new QLineEdit(widget);
    auto drop_label = new QLabel("Dropping", widget);
    auto drop_field= new QLineEdit(widget);
    auto add_button = new QPushButton("Add", widget);

    layout->addWidget(id_label);
    layout->addWidget(id_field);
    layout->addWidget(name_label);
    layout->addWidget(name_field);
    layout->addWidget(drop_label);
    layout->addWidget(drop_field);
    layout->addWidget(add_button);

    widget->setLayout(layout);

    if (m_Layout)
    {
        m_Layout->addWidget(widget);
    } else qDebug() << "layout failed";

    connect(add_button, &QPushButton::clicked, [id_field, name_field, drop_field, this](){
        auto id = id_field->text();
        auto name = name_field->text();
        auto drop = drop_field->text();
        this->addToTable(id_field->text(), name_field->text(), drop_field->text());
    });
}

void FactoryWindow::createDelWidg()
{
    auto widget = new QWidget(this);

    auto layout = new QHBoxLayout(widget);

    auto column_label = new QLabel("column", widget);
    auto column_field = new QLineEdit(widget);
    auto delete_button = new QPushButton("Delete Column", widget);

    layout->addWidget(column_label);
    layout->addWidget(column_field);
    layout->addWidget(delete_button);

    widget->setLayout(layout);

    if (m_Layout)
    {
        m_Layout->addWidget(widget);
    } else qDebug() << "layout failed";

    connect(delete_button, &QPushButton::clicked, [column_field, this](){
        this->deleteFromTable(column_field->text());
    });
}

void FactoryWindow::addToTable(const QString &id, const QString &name, const QString &drop)
{
   int new_id = id.toInt();
   QSqlQuery query;
   query.prepare("INSERT INTO factory VALUES (:id, :name, :drop)");
   query.bindValue(":id", new_id);
   query.bindValue(":name", name);
   query.bindValue(":drop", drop);
   query.exec();//TODO: add date
   m_Model->select();
   qDebug() << query.lastError().text();
}

void FactoryWindow::deleteFromTable(const QString &column)
{
    m_Model->removeRows(column.toInt() - 1, 1);//TODO: deletes identical :D
    m_Model->select();
    qDebug() << m_Model->lastError().text();
}
