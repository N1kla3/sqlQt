//
// Created by nicolas on 05/11/2020.
//

#include "header/DateDropWidget.h"
#include <QSqlQueryModel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <QSqlError>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QLineEdit>
#include <QDateEdit>

DateDropWidget::DateDropWidget(QWidget *parent)
        : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    m_Model = new QSqlQueryModel(this);

    auto table = new QTableView(this);
    table->setModel(m_Model);

    auto dropping_label = new QLabel("Dropping", this);
    auto dropping_field = new QLineEdit(this);
    auto date_label = new QLabel("Date", this);
    auto date_field = new QDateEdit(this);
    auto find_button = new QPushButton("Find", this);

    connect(find_button, &QPushButton::clicked, this, [this](){
        m_Model->setQuery("SELECT * FROM dropping");
    });

    auto back_button = new QPushButton("Close", this);
    connect(back_button, &QPushButton::clicked, [this](){
        emit close_signal();
    });

    layout->addWidget(table);
    layout->addWidget(dropping_label);
    layout->addWidget(dropping_field);
    layout->addWidget(date_label);
    layout->addWidget(date_field);
    layout->addWidget(find_button);
    layout->addWidget(back_button);
    setLayout(layout);
}
