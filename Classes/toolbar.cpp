#include "toolbar.h"
#include <QtWidgets/QToolBar>
#include <QString>

#include <QDebug>
#include <Classes/json.h>
#include <mainwindow.h>
Toolbar::Toolbar( const QString  &filePath )
{
    json_Object *data = json::parse( filePath );


    if( data ){
        name = data->element("name")->toElement()->value();
        toolbarControl = new QToolBar( name );
        author = data->element("author")->toElement()->value();
        version = data->element("version")->toElement()->value();

        json_Array* controls = data->element("controls")->toArray();
        int count = controls->count();
        for( int i = 0 ; i < count ; i++){
            json_Object* control =  controls->element( i )->toObject();

            if( !control->contains("type") ){ //OR type == action
                int action_index = control->element( "action" )->toElement()->toInt();
                if( action_index >=0 && action_index <= MainWindow::action_about ){
                    toolbarControl->addAction( MainWindow::instance()->Actions[ action_index ] );
                }
            }else{
                QString type = control->element( "type" )->toElement()->toString();

                if( type == "separator"){
                    toolbarControl->addSeparator();
                }
            }
        }
        toolbarControl->setIconSize( QSize(16,16) );
        MainWindow::instance()->addToolBar( toolbarControl );

    }
}
