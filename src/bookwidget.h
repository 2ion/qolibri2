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

#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include "book.h"

class QPushButton;

class Book;
class Group;

class BookWidget : public QWidget
{
    Q_OBJECT
public:
    BookWidget(Group *grp, bool bDel, bool bView, bool bFont,
               bool titleDisp, bool bEdit, QWidget *parent);
    void initBook(Group *grp);
    bool addBook(const QString &name, const QString &path, int subbook );
    inline QListWidget *bookListWidget() const
    {
        return bookListWidget_;
    }
    inline int currentRow() const
    {
        return bookListWidget_->currentRow();
    }
    inline Book *currentBook() const
    {
        return group->bookList()[currentRow()];
    }
    inline QListWidgetItem *currentItem() const
    {
        return bookListWidget_->currentItem();
    }
    inline void setCurrentRow(int row) const
    {
        bookListWidget_->setCurrentRow(row);
    }

signals:
    void rowChanged(int row);
    void bookViewRequested(Book *book);
    void fontViewRequested(Book *book);

private slots:
    void upItem();
    void downItem();
    void delItem();
    void viewItem()
    {
        emit bookViewRequested(group->bookList()[currentRow()]);
    }
    void editItem(QListWidgetItem* item)
    {
        bookListWidget_->openPersistentEditor(item);
        bookListWidget_->editItem(item);
    }
    void editItem()
    {
        editItem(currentItem());
    }

    void setFont()
    {
        emit fontViewRequested(currentBook());
    }

    void changeRow(int)
    {
        resetButtons();
    }
    void changeName(QListWidgetItem *item)
    {
        ((Book *)item)->setName(item->text());
    }
    void changeSelect(QListWidgetItem*, QListWidgetItem* prev)
    {
        bookListWidget_->closePersistentEditor(prev);
    }
    void changeGroupName(const QString &name)
    {
        if (group) {
            group->setName(name);
            group->setText(name);
        }
    }


private:
    void resetButtons();

    QListWidget *bookListWidget_;
    QLineEdit *groupNameEdit;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *delButton;
    QPushButton *viewButton;
    QPushButton *fontButton;
    QPushButton *editButton;

    Group *group;
};


#endif
