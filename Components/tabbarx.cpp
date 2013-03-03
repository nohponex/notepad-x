#include "tabbarx.h"

#include <QtWidgets/QTabBar>
#include <QIcon>
#include <QDebug>
#include <QDropEvent>
#include <mainwindow.h>

#include <QDrag>
#include <Components/tabwidgetx.h>
TabBarX::TabBarX( ) : QTabBar(0){
    setAcceptDrops( true );
    setDocumentMode( true );
}
void TabBarX::mousePressEvent(QMouseEvent *event){

    if (event->button() == Qt::LeftButton){
         qDebug() << "MOUSE PRESS - FROM TAB BAR";
         makeDrag();
         event->accept();
    }else{

    }

    if( MainWindow::instance()->selected_tab != this ){
        if( TabWidgetX* tab_widget = qobject_cast<TabWidgetX*>( this->parent() ) ){
            MainWindow::instance()->change_selected_tab( tab_widget->currentWidget() );
        }
    }
    QTabBar::mousePressEvent( event );
}
void TabBarX::dropEvent(QDropEvent* event)
{
    /*
    qDebug() << "DROP ENTER - FROM TAB BAR";
    const QMimeData* mimeData = event->mimeData();
    qDebug() << "FROM TAB BAR";
    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
       MainWindow::instance()->dropEvent( event );
    }else if( mimeData->text() == "This is a test" ){
        qDebug() << "DROP TAB EVENT FROM TAB";
    }*/
}
void TabBarX::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug() << "DRAG ENTER - FROM TAB BAR";
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void TabBarX::dragMoveEvent(QDragMoveEvent* event)
{
    qDebug() << "DRAG MOVE - FROM TAB BAR";
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}


void TabBarX::dragLeaveEvent(QDragLeaveEvent* event)
{
    qDebug() << "DRAG LEAVE - FROM TAB BAR";
    event->accept();
}
//delete and insert
void TabBarX::makeDrag()
{
    /*
    qDebug() << "MAKE DRAG";
    QDrag *dr = new QDrag(this);
    // The data to be transferred by the drag and drop operation is contained in a QMimeData object
    QMimeData *data = new QMimeData;
    data->setText("This is a test");
    // Assign ownership of the QMimeData object to the QDrag object.
    dr->setMimeData(data);
    // Start the drag and drop operation
    //dr->start();
    dr->exec(Qt::MoveAction);*/
}
