/*
    qolibri2 - An EPWING dictionary and book viewer
    Copyright (C) 2013 Jens Oliver John <asterisk^at^2ion.de>
    Copyright (C) 2007 BOP (author of the original qolibri)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    This project's homepage is at https://github.com/2ion/qolibri2
    The original project's homepage is at http://qolibri.sourceforge.jp
    The original author's profile page is at http://en.sourceforge.jp/users/bop
*/

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
