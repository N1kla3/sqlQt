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
#include <QtSql/QSqlQuery>

DateDropWidget::DateDropWidget(QWidget *parent)
        : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    m_Model = new QSqlQueryModel(this);

    auto table = new QTableView(this);
    table->setModel(m_Model);

    auto date_label = new QLabel("Date", this);
    auto date_field = new QDateEdit(this);
    auto find_button = new QPushButton("Find", this);

    connect(find_button, &QPushButton::clicked, this, [date_field, this](){
        auto text = date_field->text();
        QSqlQuery q;
        q.prepare("SELECT dropping FROM dropping WHERE mdate < STR_TO_DATE(:text, '%d/%m/%Y')");
        q.bindValue(":text", text);
        q.exec();
        qDebug() << q.lastError().text();
        m_Model->setQuery(q);
    });

    auto back_button = new QPushButton("Close", this);
    connect(back_button, &QPushButton::clicked, [this](){
        emit close_signal();
    });

    layout->addWidget(table);
    layout->addWidget(date_label);
    layout->addWidget(date_field);
    layout->addWidget(find_button);
    layout->addWidget(back_button);
    setLayout(layout);
}
