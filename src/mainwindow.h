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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "method.h"
#include "aboutdialog.h"

class QAction;
class QActionGroup;
class QComboBox;
class QLineEdit;
class QLabel;
class QSpinBox;
class QSettings;
class QSound;
class QTimer;
class QPushButton;
class QMenu;

class GroupDock;
class BookView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum BookMode { ModeDictionary, ModeBook };
    enum DockPosition { DockLeft, DockRight };

    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
#if defined (Q_WS_X11) || defined (Q_WS_WIN)
    bool event(QEvent *event);
#endif

signals:
    void searchFinished();
    void nowBusy(bool enable);
    void viewFontChanged(const QFont &font);

private slots:
    void viewInfo(Book *book);
    void viewMenu();
    void viewFull();
    void viewSearch();
    void viewSearch(const QString &str, const SearchMethod &method);
    void viewSearch(SearchDirection d, const QString &str);
    void doSearch();                            // by Menu
    void showStatus(const QString &str = QString());
    void pasteMethod(const QString &str, const SearchMethod &method);
    void pasteSearchText(const QString&);
    void setBooks();
    void setBookFont(Book *book);
    void setViewFont();
    void setAppFont();
    void setDictSheet();
    void setBookSheet();
    void setStatusBarSheet();
    void setConfig();
    void toggleBar();
    void toggleRuby();
    void toggleDock(bool check);

    void changeSearchText(const QString&);
    void changeDirection(int direction)
    {
        method.direction = (SearchDirection)direction;
    }
    void changeLogic(int logic)
    {
        method.logic = (NarrowingLogic)logic;
    }
    void changeGroup(int index);
    void changeBook(int index);
    void changeLimitBook(int val)
    {
        method.limitBook = val;
    }
    void changeLimitTotal(int val)
    {
        method.limitTotal = val;
    }
    void changeOptDirection(QAction*);
    void changeViewTabCount(int tab_count);
    void changeOptSearchButtonText(const QString &str);

    void addMark();
    void execProcess(const QString& prog);
    void execSound(const QString& fname);
    void execError(QProcess::ProcessError);
    void checkSound();
    void stopSound();
#if !defined (Q_WS_WIN)
    void clearCashe();
#endif
    void closedDock();

#if defined (Q_WS_X11) || defined (Q_WS_WIN)
    void showDock();
#endif
    void aboutQolibri();


private:
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();

    void setTitle();

    Group *groupFromName(const QString &name);
    Book *bookFromName(Group* group, const QString &name);
    SearchMethod readMethodSetting(const QSettings &);
    void writeMethodSetting(const SearchMethod&, QSettings*);
    QString loadAllExternalFont(Book *pbook);

#if defined (Q_WS_X11) || defined (Q_WS_WIN)
    void setDockPosition();
    void resizeDock();
    void moveDock();
#endif

    QList <Group*> groupList;
    SearchMethod method;
    BookMode bookMode;

    GroupDock *groupDock;
    BookView *bookView;

    QMenu   *optDirectionMenu;
    QActionGroup *optDirectionGroup;
    QAction *addMarkAct;
    QAction *exitAct;
    QAction *enterAct;
    QAction *stopAct;
    QAction *openBookAct;
    QAction *clearEditAct;
    QAction *toggleTabsAct;
    QAction *toggleDockAct;
    QAction *toggleBarAct;
    QAction *toggleRubyAct;
    QAction *toggleMethodBarAct;
    QAction *booksAct;
    QAction *configAct;
    QAction *sSheetAct;
    QAction *fontAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *viewAllAct;

    QToolBar *searchBar;
    QToolBar *bookBar;
    QToolBar *methodBar;

    QLineEdit *searchTextEdit;
    QComboBox *methodCombo;
    QComboBox *logicCombo;
    QComboBox *bookCombo;

    QSpinBox *limitBookSpin;
    QSpinBox *limitTotalSpin;

    QLabel *processLabel;

    QPushButton *optSearchButton;

    QSound *sound;
    SearchDirection optDirection;
    QTimer *timer;
#if defined (Q_WS_X11)
    QTimer *timerDock;
#endif

#if defined (Q_WS_X11) || defined (Q_WS_WIN)
    DockPosition dockPosition;
#endif
};

#endif

