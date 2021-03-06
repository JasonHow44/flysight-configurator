/***************************************************************************
**                                                                        **
**  FlySight Configurator                                                 **
**  Copyright 2018 Michael Cooper                                         **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>. **
**                                                                        **
****************************************************************************
**  Contact: Michael Cooper                                               **
**  Website: http://flysight.ca/                                          **
****************************************************************************/

#include "rateform.h"
#include "ui_rateform.h"

#include "configuration.h"

RateForm::RateForm(QWidget *parent) :
    ConfigurationPage(parent),
    ui(new Ui::RateForm)
{
    ui->setupUi(this);

    ui->modeComboBox->addItem("Horizontal speed", Configuration::HorizontalSpeed);
    ui->modeComboBox->addItem("Vertical speed", Configuration::VerticalSpeed);
    ui->modeComboBox->addItem("Glide ratio", Configuration::GlideRatio);
    ui->modeComboBox->addItem("Inverse glide ratio", Configuration::InverseGlideRatio);
    ui->modeComboBox->addItem("Total speed", Configuration::TotalSpeed);
    ui->modeComboBox->addItem("Magnitude of tone value", Configuration::ValueMagnitude);
    ui->modeComboBox->addItem("Change in tone value", Configuration::ValueChange);
    ui->modeComboBox->addItem("Dive angle", Configuration::DiveAngle);

    connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SIGNAL(selectionChanged()));
}

RateForm::~RateForm()
{
    delete ui;
}

void RateForm::setConfiguration(
        const Configuration &configuration)
{
    int index = ui->modeComboBox->findData(configuration.rateMode);
    ui->modeComboBox->setCurrentIndex(index);

    ui->minimumValueEdit->setText(
                QString::number(configuration.minRateToUnits()));
    ui->maximumValueEdit->setText(
                QString::number(configuration.maxRateToUnits()));
    ui->minimumEdit->setText(
                QString::number(configuration.minRate / 100.));
    ui->maximumEdit->setText(
                QString::number(configuration.maxRate / 100.));
    ui->flatlineCheckBox->setChecked(configuration.flatline);

    QString unitText;
    switch(configuration.rateMode)
    {
    case Configuration::HorizontalSpeed:
    case Configuration::VerticalSpeed:
    case Configuration::TotalSpeed:
        ui->minimumLabel->setText(tr("Minimum speed (%1):").arg(configuration.speedUnits()));
        ui->maximumLabel->setText(tr("Maximum speed (%1):").arg(configuration.speedUnits()));
        break;
    case Configuration::GlideRatio:
    case Configuration::InverseGlideRatio:
        ui->minimumLabel->setText(tr("Minimum glide ratio:"));
        ui->maximumLabel->setText(tr("Maximum glide ratio:"));
        break;
    case Configuration::ValueMagnitude:
        switch (configuration.toneMode)
        {
        case Configuration::HorizontalSpeed:
        case Configuration::VerticalSpeed:
        case Configuration::TotalSpeed:
            unitText = configuration.speedUnits();
            break;
        default:
            break;
        }
        if (unitText.isEmpty())
        {
            ui->minimumLabel->setText(tr("Minimum magnitude:"));
            ui->maximumLabel->setText(tr("Maximum magnitude:"));
        }
        else
        {
            ui->minimumLabel->setText(tr("Minimum magnitude (%1):").arg(unitText));
            ui->maximumLabel->setText(tr("Maximum magnitude (%1):").arg(unitText));
        }
        break;
    case Configuration::ValueChange:
        ui->minimumLabel->setText(tr("Minimum change (percent/s):"));
        ui->maximumLabel->setText(tr("Maximum change (percent/s):"));
        break;
    case Configuration::DiveAngle:
        ui->minimumLabel->setText(tr("Minimum angle (degrees):"));
        ui->maximumLabel->setText(tr("Maximum angle (degrees):"));
        break;
    default:
        ui->minimumLabel->setText(tr("Minimum:"));
        ui->maximumLabel->setText(tr("Maximum:"));
        break;
    }
}

void RateForm::updateConfiguration(
        Configuration &configuration,
        UpdateOptions options) const
{
    if (options & Options)
    {
        QComboBox *combo = ui->modeComboBox;
        configuration.rateMode = (Configuration::Mode) combo->itemData(combo->currentIndex()).toInt();
    }

    if (options & Values)
    {
        if (ui->minimumValueEdit->text()
                != QString::number(configuration.minRateToUnits()))
        {
            configuration.minRateFromUnits(ui->minimumValueEdit->text().toDouble());
        }
        if (ui->maximumValueEdit->text()
                != QString::number(configuration.maxRateToUnits()))
        {
            configuration.maxRateFromUnits(ui->maximumValueEdit->text().toDouble());
        }

        configuration.minRate = ui->minimumEdit->text().toDouble() * 100;
        configuration.maxRate = ui->maximumEdit->text().toDouble() * 100;
        configuration.flatline = ui->flatlineCheckBox->isChecked();
    }
}
