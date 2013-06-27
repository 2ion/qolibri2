#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutdialog::aboutdialog()
    : ui(new Ui::aboutdialog)
{
    ui->setupUi(this);
#ifndef QOLIBRI_VERSION
    ui->labelVersion->setText("Version 2.0-git");
#else
    ui->labelVersion->setText("Version" QOLIBRI_VERSION);
#endif
}

aboutdialog::~aboutdialog()
{
    delete ui;
}
