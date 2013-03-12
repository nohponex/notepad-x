#include "console.h"
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <mainwindow.h>
#include <QDebug>
#include <QtWidgets/QCompleter>
#include <QtWidgets/QDirModel>
#include <QStringListModel>
#include <QtWidgets/QHBoxLayout>
#include <QPropertyAnimation>
#include <QKeyEvent>
Console::Console( QWidget * parent ): QFrame( parent ,Qt::Tool | Qt::Window | Qt::FramelessWindowHint)
{
    qDebug() << "Open console";


//    QFrame* popup1 = new QFrame(this, Qt::Tool | Qt::Window | Qt::FramelessWindowHint);
    /*QPalette tpalette = palette();
    tpalette.setColor(QPalette::Window, QColor(34,34,34,70));
    setPalette(tpalette);
    setStyleSheet(" background-color: gray; ");*/
    file_mode = false;
    resize(300,50);
    QHBoxLayout *box = new QHBoxLayout( this );
    edit = new QLineEdit( );
    box->addWidget( edit );

    connect( edit, SIGNAL( returnPressed() ), this, SLOT( execute() ) );
   // connect( this,SIGNAL(
    //connect( edit, SIGNAL( textChanged(const QString&)), this, SLOT( setActive() ) );

    //tmpE->setGeometry(10,10, 130, 30);
    //popup1->move( this->pos().x() ,  this->pos().y() );
    QPoint t = MainWindow::instance()->editor_panel->mapToGlobal(MainWindow::instance()->editor_panel->pos() );
    this->move( ( t.x() + MainWindow::instance()->editor_panel->width()/2 - this->width()/2 )  ,t.y() + 25   );

    word_list << "/open" << "/close" << "/new" << "file:";

    completer = new QCompleter(word_list, this);
    completer->setCompletionMode( QCompleter::PopupCompletion );
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    edit->setCompleter(completer);
}
void Console::execute(){
    if( !file_mode ){
        if( edit->text()=="/close" ){
            MainWindow::instance()->file_close();
        }else if( edit->text()=="/new" ){
            MainWindow::instance()->file_new();
        }else if( edit->text()=="/open" ){
            MainWindow::instance()->file_open();
        }else if( edit->text()=="file:" ){
            completer->setModel( new QDirModel(completer) );
            completer->setCompletionMode( QCompleter::PopupCompletion );
            edit->setText("/home/");
            file_mode = true;
            return;
        }
    }else{
        file_mode = false;
        MainWindow::instance()->file_open( edit->text() );
 //       completer->setModel( new QStringListModel(completer) );

        completer = new QCompleter(word_list, this);
        completer->setCompletionMode( QCompleter::InlineCompletion );
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        edit->setCompleter(completer);

    }
    edit->clear();
    hide();
}

void Console::keyPressEvent(QKeyEvent *e){
    if ( e->key() == Qt::Key_Escape ) {
        this->hide();
    }
}
void Console::showEvent ( QShowEvent * event ){
   /* QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();*/
    qDebug() << "Console::showEvent";
    this->activateWindow();
    edit->setFocus();
}
