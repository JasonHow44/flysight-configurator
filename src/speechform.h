#ifndef SPEECHFORM_H
#define SPEECHFORM_H

#include "configurationpage.h"

namespace Ui {
class SpeechForm;
}

class SpeechForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit SpeechForm(QWidget *parent = 0);
    ~SpeechForm();

    QString title() const { return "Speech"; }
    void updateConfiguration(Configuration &configuration);

private:
    Ui::SpeechForm *ui;

public slots:
    void setConfiguration(const Configuration &configuration);
};

#endif // SPEECHFORM_H
