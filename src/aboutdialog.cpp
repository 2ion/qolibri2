#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutdialog::aboutdialog()
    : ui(new Ui::aboutdialog)
{
    ui->setupUi(this);
    ui->labelVersion->setText("Version 1.9-git");
}

aboutdialog::~aboutdialog()
{
    delete ui;
}
