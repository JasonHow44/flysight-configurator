#ifndef SILENCEFORM_H
#define SILENCEFORM_H

#include "configurationpage.h"

namespace Ui {
class SilenceForm;
}

class SilenceForm : public ConfigurationPage
{
    Q_OBJECT

public:
    explicit SilenceForm(QWidget *parent = 0);
    ~SilenceForm();

    QString title() const { return "Silence"; }

    void updateConfiguration(Configuration &configuration,
                             UpdateOptions options) const;
    void setConfiguration(const Configuration &configuration,
                          UpdateOptions options);

private:
    Ui::SilenceForm *ui;

private slots:
    int add();
    void remove();
    void updateControls();
};

#endif // SILENCEFORM_H
