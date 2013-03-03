#include "externalwindow.h"

#include <Components/tabwidgetx.h>
#include <QCloseEvent>
#include <mainwindow.h>
#include <QDebug>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>
ExternalWindow::ExternalWindow(QWidget *parent) :
    QMainWindow(parent)
{
    tabControl = new TabWidgetX();
    this->setCentralWidget( tabControl );

    MainWindow::instance()->selected_tab_control = tabControl;
    //MainWindow::instance()->file_new();
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    if( MainWindow::instance()->show_toolbar_in_external ){
          QToolBar *t = this->addToolBar("toolbar");
          t->setIconSize( QSize(20,20) );

          QAction* new_external = new QAction( MainWindow::instance()->Actions[ MainWindow::action_new ] );
          new_external->setIcon(  MainWindow::instance()->Actions[ MainWindow::action_new ]->icon() );
          new_external->setText( MainWindow::instance()->Actions[ MainWindow::action_new ]->text() );
          disconnect( new_external, SIGNAL( triggered() ) );
          connect( new_external, SIGNAL(triggered() ), this, SLOT( file_new_external() ) );

          t->addAction( new_external );
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_open ] );
          t->addSeparator();
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_save ] );
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_saveAs ] );
          t->addSeparator();
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_undo ] );
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_redo ] );
          t->addSeparator();
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_copy ] );
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_cut ] );
          t->addAction( MainWindow::instance()->Actions[ MainWindow::action_paste ] );
    }
}
ExternalWindow::~ExternalWindow(){

    delete tabControl;
    tabControl = 0;
}
bool ExternalWindow::closeWindow( ){
    bool value = true;
    for( int t = tabControl->count() -1 ; t >= 0 ; t-- ){
        tabControl->setCurrentIndex( t );
        MainWindow::instance()->change_selected_tab( tabControl->widget( t ) );

        value &= MainWindow::instance()->file_close();
    }

    //if( value ){
      //  qDebug() << "CLOSE";
        //this->close();
        //closeEvent(0);
    //}
    return value;
}

void ExternalWindow::closeEvent(QCloseEvent *event)
{
    if( !closeWindow () ){
        event->ignore();
        return;
    }
    //event->accept();
    //MainWindow::instance()->selected_tab_control = 0;
    int size = MainWindow::instance()->external_windows.size();
    for( int i = 0 ; i< size ; i++ ){
        if( MainWindow::instance()->external_windows[ i ]  == this ){

            MainWindow::instance()->external_windows[ i ] = 0;
            break;
        }
    }
    tabControl->clear();

    tabControl = 0;
    delete this;

    MainWindow::instance()->selected_tab_control = MainWindow::instance()->tab_widget_0;
}
void ExternalWindow::file_new_external(){
    qDebug() << "EXTERNAL NEW";
    MainWindow::instance()->selected_tab_control = this->tabControl;
    MainWindow::instance()->file_new();
}
