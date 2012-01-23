#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QMainWindow *parent);
    ~MainMenu();
    
signals:
    
public slots:
    
private:
    void buildFileMenu(QMainWindow *parent);
    void buildCellularMenu(QMainWindow *parent);

    QMenu *_file;//, *_help;
    QAction *_open, *_save, *_exit;

    QMenu *_cellular;
    QAction *_reset, *_clear;
//    QAction *_about;
};

#endif // MAINMENU_H
