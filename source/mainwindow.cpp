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
#include <header/DateDropWidget.h>

#include "header/FactoryWindow.h"


//***Constants***
constexpr int MAIN_WIDGET = 0;
constexpr int FACTORY_WIDGET = 1;
constexpr int DROPPING_WIDGET = 2;
constexpr int WATCH_DROP_WIDGET = 3;
constexpr int WATCH_CONC_WIDGET = 4;
constexpr int WATCH_PDK_WIDGET = 5;

constexpr int X_BUTTON_START = 100;
constexpr int Y_BUTTON_START = 100;

constexpr int BUTTON_W = 100;
constexpr int BUTTON_H = 100;

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


    m_EditFactory->setGeometry(X_BUTTON_START, Y_BUTTON_START, BUTTON_W, BUTTON_H);
    m_EditDropping->setGeometry(X_BUTTON_START + BUTTON_W, Y_BUTTON_START + BUTTON_H, BUTTON_W, BUTTON_H);
    m_WatchConcentration->setGeometry(X_BUTTON_START + 2*BUTTON_W, Y_BUTTON_START + 2*BUTTON_H, BUTTON_W, BUTTON_H);
    m_WatchPDK->setGeometry(X_BUTTON_START + 2*BUTTON_W, Y_BUTTON_START, BUTTON_W, BUTTON_H);
    m_WatchDropFactory->setGeometry(X_BUTTON_START, Y_BUTTON_START + 2*BUTTON_H, BUTTON_W, BUTTON_H);
}

void MainWindow::connectButtons()
{
    connect(m_EditFactory, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(FACTORY_WIDGET);
    });
    connect(m_EditDropping, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(DROPPING_WIDGET);
    });
    connect(m_WatchDropFactory, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(WATCH_DROP_WIDGET);
    });
    connect(m_WatchConcentration, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(WATCH_CONC_WIDGET);
    });
    connect(m_WatchPDK, &QPushButton::clicked, [this](){
        this->m_Widget->setCurrentIndex(WATCH_PDK_WIDGET);
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

void MainWindow::createDateDropWidget()
{
    auto window = new DateDropWidget(this);
    m_Widget->addWidget(window);
    connect(window, &DateDropWidget::close_signal, this, &MainWindow::switch_to_main);
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
    createDateDropWidget();
}

void MainWindow::switch_to_main()
{
    m_Widget->setCurrentIndex(MAIN_WIDGET);
}
