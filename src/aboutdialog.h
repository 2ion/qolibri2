#ifndef QOL_ABOUTDIALOG
#define QOL_ABOUTDIALOG

#include <QDialog>

namespace Ui {
    class aboutdialog;
}

class aboutdialog : public QDialog {
    Q_OBJECT
    public:
        aboutdialog();
        virtual ~aboutdialog();
    private:
        Ui::aboutdialog *ui;
};

#endif
