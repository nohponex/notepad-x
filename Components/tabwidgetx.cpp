#include "tabwidgetx.h"

#include <QtWidgets/QTabBar>
#include <Components/tabbarx.h>
#include <QDebug>

#include <Classes/iconpack.h>
#include <Documents/defaultdocument.h>
#include <Documents/IDocument.h>
#include <mainwindow.h>

TabWidgetX::TabWidgetX( QWidget* parent): QTabWidget(parent){
    setContextMenuPolicy( Qt::CustomContextMenu );
   // QTabBar* tb = new TabBarX(0);

    setTabBar( new TabBarX() );

    setAcceptDrops( true );
    setMovable( true );
    setTabsClosable( true );
    setDocumentMode( true );
    //setTabShape( QTabWidget::Triangular );
    connect( this, SIGNAL( tabCloseRequested(int) ), this, SLOT( closing(int) ) );
    //connect( this, SIGNAL( tabCloseRequested(int) ), MainWindow::instance() , SLOT( file_close() ) );
    connect( this, SIGNAL( currentChanged(int) ), this, SLOT( selection_change(int) ) );

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), MainWindow::instance(), SLOT(show_tabs_contextMenu(const QPoint&)));
}
void TabWidgetX::tabInserted(int index){
    widget(index)->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setCurrentIndex( index );
    //setTabIcon( index, iconpack.get_icon( iconpack::icon_saved );
    document_changed();
    MainWindow::instance()->change_selected_tab( widget( index ) );

}

void TabWidgetX::closing(int index){

    if( MainWindow::instance()->selected_tab_control != this ){
        MainWindow::instance()->selected_tab_control = this;
    }
    if ( currentIndex() != index ){
        this->setCurrentIndex( index );
    }
    MainWindow::instance()->change_selected_tab( widget( index ) );
    MainWindow::instance()->file_close();
    //this->removeTab( index );
}
void TabWidgetX::selection_change(int index){

    if( index < 0 ){
        //MainWindow::instance()->change_selected_tab( 0  );
    }else if( MainWindow::instance()->selected_tab != widget( index ) ){
        MainWindow::instance()->change_selected_tab( widget( index ) );
    }
}
void TabWidgetX::document_changed(){
    //IDocument* doc = dynamic_cast<IDocument*>(sender());
    IDocument* doc = dynamic_cast<IDocument*>( widget( currentIndex() ) );
    //qDebug() << ();
    if( ( doc->get_available() || doc->get_saved() ) && doc->editor_getText() != "" ){
        qDebug() << " set available";
        doc->set_available();
    }

    if( doc->get_saved() || doc->get_available() ){
        setTabIcon( currentIndex(), *iconpack::instance()->get_icon( iconpack::icon_saved ) );
    }else{
        //check
        setTabIcon( this->currentIndex(), *iconpack::instance()->get_icon( iconpack::icon_notsaved ) );
    }
}
void TabWidgetX::document_saved( bool saved ){
    if( saved ){
        //check
        setTabIcon( this->currentIndex(), *iconpack::instance()->get_icon( iconpack::icon_saved ) );
    }else{
        setTabIcon( this->currentIndex(), *iconpack::instance()->get_icon( iconpack::icon_notsaved ) );
    }
    setTabText( this->currentIndex(),  dynamic_cast<IDocument*>( widget( this->currentIndex() ) )->getTabText());
}
