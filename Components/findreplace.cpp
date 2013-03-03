#include "findreplace.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

#include <Classes/iconpack.h>
findReplace::findReplace(QWidget *parent) :
    QWidget(parent)
{

    setMaximumHeight(48);
    setSizePolicy(QSizePolicy(QSizePolicy::Ignored,QSizePolicy::Maximum));


    QVBoxLayout *lay = new QVBoxLayout();
    setLayout( lay );
    lay->setMargin( 0 );
    lay->setSpacing( 2 );
    QHBoxLayout *find_layout = new QHBoxLayout();

    find_layout -> setMargin( 0 );
    find_layout->setSpacing( 2 );
    //lay->addItem( find_layout );
    find_widget = new QWidget() ;

    find_widget->setLayout( find_layout );


    find_label = new QLabel("Find");

    find_button= new QPushButton("Find");
    close_button = new QPushButton( *iconpack::instance()->get_icon( iconpack::icon_close ),"" );
    close_button->setToolTip( "Close" );
    find_text = new QLineEdit();


    find_layout->addWidget( close_button );
    find_layout->addWidget( find_label );
    find_layout->addWidget( find_text );
    find_layout->addWidget( find_button );

    QHBoxLayout *replace_layout = new QHBoxLayout();

    replace_layout -> setMargin( 0 );
    replace_layout ->setSpacing( 2 );
    replace_widget = new QWidget() ;
    replace_widget->setLayout( replace_layout );

    replace_label = new QLabel("Replace");
    replace_button= new QPushButton("Replace");
    replace_text = new QLineEdit();

    replace_layout->addWidget( replace_label );
    replace_layout->addWidget( replace_text );
    replace_layout->addWidget( replace_button );

    lay->addWidget( find_widget );
    lay->addWidget( replace_widget );

    connect( close_button, SIGNAL(pressed()),this,SLOT(hide()));
}
void findReplace::keyPressEvent(QKeyEvent *e){
    /*if ( e->key() == Qt::Key_Escape ) {
        this->hide();
    }*/
}
