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

#ifndef FONTSETTING_H
#define FONTSETTING_H

#include <QDialog>

#include "book.h"

class QTreeWidget;
class QTreeWidgetItem;
class QLabel;

class FontSetting : public QDialog
{
    Q_OBJECT
public:
    FontSetting(Book *book, QWidget *parent);
    int setupTreeWidget(const QString &fpath);
    QHash <QString, QString>  *newAlternateFontList();

private slots:
    void selectFont(QTreeWidgetItem *next, QTreeWidgetItem *prev);
    void changeFontCode(const QString &txt);
    void save();
    void load();

private:

    QPushButton *fontButton;
    QLabel *fontCodeLabel;
    QTreeWidget *fontTreeWidget;
    QLineEdit *fontCodeEdit;
    QLabel *fontLabel;
    QString casheDir;
    Book *book;
};

#endif
