//
// Created by nicolas on 08/10/2020.
//

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QPushButton>
#include <QTextStream>
#include <QRandomGenerator>
#include <header/mainwindow.h>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QStackedWidget>
#include <header/DropWidget.h>
#include <header/MaterialWidget.h>
#include <header/ConcentrationWidget.h>

#include "header/FactoryWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("first");
    db.setUserName("root");
    db.setPassword("Dsdjls02.");
    if (!db.open()){
        qDebug() << QObject::trUtf8("Database error connect") << db.lastError().text();
    }

    this->setFixedSize(500, 500);

    m_Widget = new QStackedWidget;
    init();
    setCentralWidget(m_Widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createButtons()
{
    m_EditFactory = new QPushButton("factory", m_MainWidget);
    m_EditDropping = new QPushButton("dropping", m_MainWidget);
    m_WatchConcentration = new QPushButton("Watch Conc", m_MainWidget);
    m_WatchPDK = new QPushButton("Watch Pdk", m_MainWidget);
    m_WatchDropFactory = new QPushButton("Watch Factory", m_MainWidget);
}

void MainWindow::locateButtons()
{
    constexpr int BUTTON_W = 100;
    constexpr int BUTTON_H = 100;

    m_EditFactory->setGeometry(100, 100, BUTTON_W, BUTTON_H);
    m_EditDropping->setGeometry(200, 200, BUTTON_W, BUTTON_H);
    m_WatchConcentration->setGeometry(300, 300, BUTTON_W, BUTTON_H);
    m_WatchPDK->setGeometry(300, 100, BUTTON_W, BUTTON_H);
    m_WatchDropFactory->setGeometry(100, 300, BUTTON_W, BUTTON_H);
}

void MainWindow::connectButtons()
{
    connect(m_EditFactory, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(1);
    });
    connect(m_EditDropping, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(2);
    });
    connect(m_WatchDropFactory, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(3);//TODO: magic numbers
    });
    connect(m_WatchConcentration, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(4);
    });
}

void MainWindow::createFactoryWindow()
{
    auto window = new FactoryWindow(this);
    m_Widget->addWidget(window);
    connect(window, &FactoryWindow::close_signal, this, &MainWindow::switch_to_main);
}

void MainWindow::createDroppingWindow()
{
    auto window = new DropWidget(this);
    m_Widget->addWidget(window);
    connect(window, &DropWidget::close_signal, this, &MainWindow::switch_to_main);
}

void MainWindow::createMaterialsWidget()
{
    auto window = new MaterialWidget(this);
    m_Widget->addWidget(window);
    connect(window, &MaterialWidget::close_signal, this, &MainWindow::switch_to_main);
}

void MainWindow::createConcentrationWidget()
{
    auto window = new ConcentrationWidget(this);
    m_Widget->addWidget(window);
    connect(window, &ConcentrationWidget::close_signal, this, &MainWindow::switch_to_main);
}

void MainWindow::createMainWidget()
{
    m_MainWidget = new QWidget;
    m_Widget->addWidget(m_MainWidget);

    createButtons();
    locateButtons();
    connectButtons();

}

void MainWindow::init()
{
    createMainWidget();
    createFactoryWindow();
    createDroppingWindow();
    createMaterialsWidget();
    createConcentrationWidget();
}

void MainWindow::switch_to_main()
{
    m_Widget->setCurrentIndex(0);
}
