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

#include <QtCore>

#include "book.h"

const char *FontFile = { "afonts_" };

void Book::loadAlterFont()
{
    if (fontList_) {
        delete fontList_;
        fontList_ = NULL;
    }
    QString fname = path_ + "/" + FontFile + QString().setNum(bookNo_);
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //qWarning() << "Can't open for read" << fname;
        return;
    }

    fontList_ = new QHash<QString, QString>;
    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString line = in.readLine();
    while (!line.isNull()) {
        QStringList list = line.remove('\n').split(' ');
        if (list.count() == 2) {
            fontList_->insert(list[0], list[1]);
        }
        line = in.readLine();
    }
}

void Book::saveAlterFont()
{
    QString fname = path_ + "/" + FontFile + QString().setNum(bookNo_);
    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Can't open for write" << fname;
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QHashIterator<QString, QString> i(*fontList_);
    while (i.hasNext()) {
        i.next();
        out << i.key() << " " << i.value() << "\n";
    }
}

