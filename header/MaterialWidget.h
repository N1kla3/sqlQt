//
// Created by nicolas on 05/11/2020.
//

#ifndef SQLQT_MATERIALWIDGET_H
#define SQLQT_MATERIALWIDGET_H

#include <QWidget>

class QSqlQueryModel;

class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialWidget(QWidget* parent);
signals:
    void close_signal();

protected:
    virtual void find_event();
private:
    QSqlQueryModel* m_Model = nullptr;
};


#endif //SQLQT_MATERIALWIDGET_H
