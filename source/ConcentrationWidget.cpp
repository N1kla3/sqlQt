//
// Created by nicolas on 05/11/2020.
//

#include <header/ConcentrationWidget.h>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

ConcentrationWidget::ConcentrationWidget(QWidget *parent)
        :MaterialWidget(parent)
{

}

void ConcentrationWidget::find_event()
{
    auto text = dropping_field->text();
    QSqlQuery q;
    q.prepare("SELECT elements.element, concentration FROM elements "
               "INNER JOIN target_elements te on elements.element = te.element "
               "WHERE target IN (SELECT target FROM dropping "
               "WHERE dropping = :text) ");
    q.bindValue(":text", text);
    q.exec();
    m_Model->setQuery(q);

    qDebug() << q.lastError().text();
}
