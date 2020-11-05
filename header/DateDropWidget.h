//
// Created by nicolas on 05/11/2020.
//

#ifndef SQLQT_DATEDROPWIDGET_H
#define SQLQT_DATEDROPWIDGET_H

#include <QWidget>

class QSqlQueryModel;

class DateDropWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateDropWidget(QWidget* parent);
signals:
    void close_signal();

private:
    QSqlQueryModel* m_Model = nullptr;
};


#endif //SQLQT_DATEDROPWIDGET_H
