//
// Created by nicolas on 05/11/2020.
//

#ifndef SQLQT_CONCENTRATIONWIDGET_H
#define SQLQT_CONCENTRATIONWIDGET_H

#include <header/MaterialWidget.h>

class QSqlQueryModel;

class ConcentrationWidget : public MaterialWidget
{
    Q_OBJECT

public:
    explicit ConcentrationWidget(QWidget* parent);

protected:
    virtual void find_event() override;
};


#endif //SQLQT_CONCENTRATIONWIDGET_H
