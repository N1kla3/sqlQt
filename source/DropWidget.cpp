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

DropWidget::DropWidget(QWidget *parent)
        : QWidget(parent)
{
    m_Layout = new QVBoxLayout(this);

    m_Model = new QSqlTableModel(this);
    m_Model->setTable("dropping");
    m_Model->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_Model->select();
    m_Model->setHeaderData(0, Qt::Horizontal, tr("Dropping"));
    m_Model->setHeaderData(1, Qt::Horizontal, tr("Target Index"));
    m_Model->setHeaderData(2, Qt::Horizontal, tr("Target Name"));
    m_Model->setHeaderData(3, Qt::Horizontal, tr("Target Meters"));

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
    auto index_label = new QLabel("Index", widget);
    auto index_field = new QLineEdit(widget);
    auto name_label = new QLabel("Name", widget);
    auto name_field= new QLineEdit(widget);
    auto meters_label = new QLabel("Meters", widget);
    auto meters_field= new QLineEdit(widget);
    auto add_button = new QPushButton("Add", widget);

    layout->addWidget(drop_label);
    layout->addWidget(drop_field);
    layout->addWidget(index_label);
    layout->addWidget(index_field);
    layout->addWidget(name_label);
    layout->addWidget(name_field);
    layout->addWidget(meters_label);
    layout->addWidget(meters_field);
    layout->addWidget(add_button);

    widget->setLayout(layout);

    if (m_Layout)
    {
        m_Layout->addWidget(widget);
    } else qDebug() << "layout failed";

    connect(add_button, &QPushButton::clicked, [drop_field, name_field, index_field, meters_field, this](){
        this->addToTable(drop_field->text(), index_field->text(), name_field->text(), meters_field->text());
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

void DropWidget::addToTable(const QString &dropping, const QString &index, const QString &name, const QString meters)
{
    QSqlQuery query;
    query.prepare("INSERT INTO dropping VALUES (:dropping, :index, :name, :meters)");
    query.bindValue(":dropping", dropping);
    query.bindValue(":index", index);
    query.bindValue(":name", name);
    query.bindValue(":meters", meters);
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
