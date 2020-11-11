//
// Created by nicolas on 05/11/2020.
//

#include <header/MaterialWidget.h>
#include <QSqlQueryModel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <QSqlError>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QLineEdit>
#include <QtSql/QSqlQuery>

MaterialWidget::MaterialWidget(QWidget *parent) :
        QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    m_Model = new QSqlQueryModel(this);

    auto table = new QTableView(this);
    table->setModel(m_Model);

    auto dropping_label = new QLabel("Dropping", this);
    dropping_field = new QLineEdit(this);
    auto find_button = new QPushButton("Find", this);

    connect(find_button, &QPushButton::clicked, this, &MaterialWidget::find_event);

    auto back_button = new QPushButton("Close", this);
    connect(back_button, &QPushButton::clicked, [this](){
        emit close_signal();
    });

    layout->addWidget(table);
    layout->addWidget(dropping_label);
    layout->addWidget(dropping_field);
    layout->addWidget(find_button);
    layout->addWidget(back_button);
    setLayout(layout);
}

void MaterialWidget::find_event()
{
    auto text = dropping_field->text();
    QSqlQuery q;
    q.prepare("SELECT element, PDK, KNK, ph_conc, d.target FROM target_elements "
              "INNER JOIN dropping d on target_elements.target = d.target "
              "WHERE dropping = :text");
    q.bindValue(":text", text);
    q.exec();
    m_Model->setQuery(q);
    qDebug() << m_Model->lastError().text();
}
