#ifndef EXTERNALWINDOW_H
#define EXTERNALWINDOW_H

#include <QtWidgets/QMainWindow>
#include <Components/tabwidgetx.h>
#include <mainwindow.h>

class QCloseEvent;

class ExternalWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);

public:
    explicit ExternalWindow(QWidget *parent = 0);
    TabWidgetX *tabControl;
    ~ExternalWindow();
    bool closeWindow( );
signals:
    
public slots:
    void file_new_external();
};

#endif // EXTERNALWINDOW_H
