//
// Created by nicolas on 08/10/2020.
//

#ifndef SQLQT_MAINWINDOW_H
#define SQLQT_MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    
private:
    void createButtons();
    void locateButtons();
    void connectButtons();

    void init();
    void createMainWidget();
    void createFactoryWindow();
    void createDroppingWindow();
    void createMaterialsWidget();
    void createConcentrationWidget();

    void switch_to_main();

    QStackedWidget* m_Widget;
    QWidget* m_MainWidget;

    QPushButton* m_EditFactory;
    QPushButton* m_EditDropping;
    QPushButton* m_WatchConcentration;
    QPushButton* m_WatchPDK;
    QPushButton* m_WatchDropFactory;
};

#endif //SQLQT_MAINWINDOW_H
