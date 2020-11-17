//
// Created by nicolas on 03/11/2020.
//

#include "header/DropWidget.h"
#include <QSqlTableModel>
#include <QVBoxLayout>
#include <QDebug>
#include <QSqlQuery>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSqlError>
#include <QtWidgets/QDateEdit>

DropWidget::DropWidget(QWidget *parent)
        : QWidget(parent)
{
    m_Layout = new QVBoxLayout(this);

    m_Model = new QSqlTableModel(this);
    m_Model->setTable("dropping");
    m_Model->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_Model->select();
    m_Model->setHeaderData(0, Qt::Horizontal, tr("Dropping"));
    m_Model->setHeaderData(1, Qt::Horizontal, tr("Factory"));
    m_Model->setHeaderData(2, Qt::Horizontal, tr("Date"));

    qDebug() << m_Model->lastError().text();

    auto view = new QTableView(this);
    view->setModel(m_Model);

    m_Layout->addWidget(view);
    createAddWidget();
    createDelWidget();

    auto close_button = new QPushButton("Close", this);
    connect(close_button, &QPushButton::clicked, [this](){
        emit close_signal();
    });
    m_Layout->addWidget(close_button);

    setLayout(m_Layout);
}

void DropWidget::createAddWidget()
{
    auto widget = new QWidget(this);

    auto layout = new QHBoxLayout(widget);

    auto drop_label = new QLabel("Dropping", widget);
    auto drop_field = new QLineEdit(widget);
    auto factory_label = new QLabel("Factory", widget);
    auto factory_field = new QLineEdit(widget);
    auto data_field = new QDateEdit(this);
    auto add_button = new QPushButton("Add", widget);

    layout->addWidget(drop_label);
    layout->addWidget(drop_field);
    layout->addWidget(factory_label);
    layout->addWidget(factory_field);
    layout->addWidget(data_field);
    layout->addWidget(add_button);

    widget->setLayout(layout);

    if (m_Layout)
    {
        m_Layout->addWidget(widget);
    } else qDebug() << "layout failed";

    connect(add_button, &QPushButton::clicked, [drop_field, factory_field, data_field, this](){
        this->addToTable(drop_field->text(), factory_field->text(), data_field->date());
    });
}

void DropWidget::createDelWidget()
{
    auto widget = new QWidget(this);

    auto layout = new QHBoxLayout(widget);

    auto row_label = new QLabel("column", widget);
    auto row_field = new QLineEdit(widget);
    auto delete_button = new QPushButton("Delete Column", widget);

    layout->addWidget(row_label);
    layout->addWidget(row_field);
    layout->addWidget(delete_button);

    widget->setLayout(layout);

    if (m_Layout)
    {
        m_Layout->addWidget(widget);
    } else qDebug() << "layout failed";

    connect(delete_button, &QPushButton::clicked, [row_field, this](){
        this->deleteFromTable(row_field->text());
    });
}

void DropWidget::addToTable(const QString &dropping, const QString& factory, const QDate& date)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dropping VALUES (:dropping, :factory, :date)");
    query.bindValue(":dropping", dropping);
    query.bindValue(":factory", factory);
    query.bindValue(":date", date);
    query.exec();
    m_Model->select();
    qDebug() << query.lastError().text();
}

void DropWidget::deleteFromTable(const QString &row)
{
    m_Model->removeRows(row.toInt() - 1, 1);
    m_Model->select();
    qDebug() << m_Model->lastError().text();
}
