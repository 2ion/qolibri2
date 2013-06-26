#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutdialog::aboutdialog()
    : ui(new Ui::aboutdialog)
{
    ui->setupUi(this);
}

aboutdialog::~aboutdialog()
{
    delete ui;
}
