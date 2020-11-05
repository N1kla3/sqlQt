//
// Created by nicolas on 31/10/2020.
//

#ifndef SQLQT_FACTORYWINDOW_H
#define SQLQT_FACTORYWINDOW_H


#include <QWidget>
#include <QtWidgets/QBoxLayout>

class QSqlTableModel;

class FactoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FactoryWindow(QWidget* parent = nullptr);

signals:
    void close_signal();
private:
    void createAddWidg();
    void createDelWidg();

    void addToTable(const QString& id, const QString& name, const QString& drop);
    void deleteFromTable(const QString& column);

    QBoxLayout* m_Layout = nullptr;
    QSqlTableModel* m_Model = nullptr;
};


#endif //SQLQT_FACTORYWINDOW_H
