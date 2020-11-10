//
// Created by nicolas on 03/11/2020.
//

#ifndef SQLQT_DROPWIDGET_H
#define SQLQT_DROPWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QSqlTableModel;

class DropWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DropWidget(QWidget* parent = nullptr);
signals:
    void close_signal();

private:
    void createAddWidget();
    void createDelWidget();

    void addToTable(const QString &dropping, const QString &target, const QString &location, const QString& factory);
    void deleteFromTable(const QString &row);

    QVBoxLayout* m_Layout = nullptr;
    QSqlTableModel* m_Model = nullptr;
};


#endif //SQLQT_DROPWIDGET_H
