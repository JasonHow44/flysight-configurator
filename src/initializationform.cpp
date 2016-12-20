#include "initializationform.h"
#include "ui_initializationform.h"

#include <QFileDialog>
#include <QFileInfo>

#include "configuration.h"

InitializationForm::InitializationForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::InitializationForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Do nothing");
    ui->modeComboBox->addItem("Test speech mode");
    ui->modeComboBox->addItem("Play file");
}

InitializationForm::~InitializationForm()
{
    delete ui;
}

void InitializationForm::setConfiguration(const Configuration &configuration)
{
    ui->modeComboBox->setCurrentIndex(configuration.initMode);
    ui->filenameEdit->setText(configuration.initFile);
}
