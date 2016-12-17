#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>

#include "configurationpage.h"
#include "generalform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create configuration pages
    pages.append(new GeneralForm());

    // Create interface components
    QListWidget *listWidget = new QListWidget();
    QStackedWidget *stackedWidget = new QStackedWidget();

    // Add pages to configuration window
    foreach(ConfigurationPage *page, pages)
    {
        listWidget->addItem(page->title());
        stackedWidget->addWidget(page);
    }
    stackedWidget->setCurrentIndex(0);

    // Lay out main window
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(listWidget);
    layout->addWidget(stackedWidget);

    // Create new central widget
    QWidget *window = new QWidget();
    window->setLayout(layout);

    // Set the new central widget
    setCentralWidget(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}