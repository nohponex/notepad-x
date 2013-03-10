#include <QDebug>

#include "settingsdialog.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <Classes/iconpack.h>
#include "mainwindow.h"
#include <QtWidgets/QLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTabBar>

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QAction>
#include <QPair>
SettingsDialog::SettingsDialog( QWidget *parent ): QWidget(parent){
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setMargin(2);
    resize(650,450);

    //QRect scr = QApplication::desktop()->screenGeometry();
    //move( scr.center() - rect().center() );
    move( MainWindow::instance()->geometry().center() - rect().center() );
    setWindowTitle("Settings");

    tab_control = new QTabWidget( );
    lay->addWidget( tab_control );
    //tab_control->resize( 200 , 200 );
    //tab_general = new QTabBar();
    //tab_control->addTab( tab_general, *iconpack::instance()->get_icon( iconpack::icon_settings),  "General" );
    //tab_icons = new QTabBar();
    //tab_control->addTab( tab_icons, *iconpack::instance()->get_icon( iconpack::icon_copy ),  "Icons" );

    buttons = new QDialogButtonBox( QDialogButtonBox::Apply|QDialogButtonBox::Cancel );
    lay->addWidget( buttons );
    //this->setLayout( lay );
    //General
    ///QVBoxLayout *general_layout = new QVBoxLayout(   );
    //general_layout->setMargin( 0 );
    gereral_scroll = new QScrollArea();
    gereral_scroll->setWidgetResizable( true );
    //general_layout->addWidget( gereral_scroll );
    tab_control->addTab( gereral_scroll, *iconpack::instance()->get_icon( iconpack::icon_settings),  "General" );
    //gereral_scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    //gereral_scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );

    //gereral_scroll->setWidgetResizable( true );
    //<general>

    QWidget *gereral_scroll_inside = new QWidget( );
    QVBoxLayout* gereral_layout = new QVBoxLayout();
    gereral_layout->setMargin( 0 );
    gereral_scroll_inside->setLayout( gereral_layout );

    //gereral_scroll->setWidget( gereral_scroll_inside );
    //gereral_scroll->addScrollBarWidget( gereral_scroll_inside, Qt::AlignLeft );
    //gereral_scroll->addScrollBarWidget( new QLineEdit(),Qt::AlignLeft );
    //general_layout->addWidget( gereral_scroll );

    QWidget *gereral_general = new QWidget( );
    general_form = new QFormLayout();
    gereral_general->setLayout( general_form );
    gereral_layout->addWidget( gereral_general );
    //gereral_scroll->addScrollBarWidget( general_form, Qt::AlignLeft );
    //gereral_scroll_inside->setLayout(  general_form );
    general_form->addRow("XAXAX", new QFontComboBox() );
    general_form->addRow("XAXAX2", new QLineEdit() );
    general_form->addRow("XAXAX3", new QLineEdit() );
    general_form->addRow("XAXAX", new QLineEdit() );
    general_form->addRow("XAXAX2", new QLineEdit() );
    general_form->addRow("XAXAX3", new QLineEdit() );
    general_form->addRow("XAXAX", new QLineEdit() );
    general_form->addRow("XAXAX2", new QLineEdit() );
    general_form->addRow("XAXAX3", new QLineEdit() );
    general_form->addRow("XAXAX", new QLineEdit() );
    general_form->addRow("XAXAX2", new QLineEdit() );
    general_form->addRow("XAXAX3", new QLineEdit() );
    general_form->addRow("XAXAXaaaaaaa3", new QLineEdit() );


    gereral_scroll->setWidget( gereral_scroll_inside );
    //</general>
    //<general/extensions>
    //QWidget *gereral_extensions = new QWidget( );
    QGroupBox *gereral_extensions = new QGroupBox("Extensions");

    QHBoxLayout* gereral_extensions_layout = new QHBoxLayout();
    gereral_extensions_layout->setMargin( 2 );
    gereral_extensions->setLayout( gereral_extensions_layout );
    /*QFormLayout* general_extensions_form = new QFormLayout();
    gereral_extensions->setLayout( general_extensions_form );
    general_extensions_form->addRow("XAXAX3", new QLineEdit() );*/
    general_extensions_table = new  QTableWidget(0, 2);
    QStringList labels;
    labels << tr("Name") << tr("Extension");
    general_extensions_table->setHorizontalHeaderLabels(labels);
    general_extensions_table->horizontalHeader()->setStretchLastSection(true);
    //general_extensions_table->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    general_extensions_table->verticalHeader()->hide();
    general_extensions_table->setShowGrid(false);
    //general_extensions_table->rowCount();
    general_extensions_table->setRowCount( 4+1 );
    general_extensions_table->setItem(0, 0, new QTableWidgetItem("Text document"));
    general_extensions_table->setItem(0, 1, new QTableWidgetItem("*.txt"));
    general_extensions_table->setItem(1, 0, new QTableWidgetItem("JSON"));
    general_extensions_table->setItem(1, 1, new QTableWidgetItem("*.json"));
    general_extensions_table->setItem(2, 0, new QTableWidgetItem("JSON"));
    general_extensions_table->setItem(2, 1, new QTableWidgetItem("*.json"));
    general_extensions_table->setItem(3, 0, new QTableWidgetItem("JSON"));
    general_extensions_table->setItem(3, 1, new QTableWidgetItem("*.json"));

    qDebug() << general_extensions_table->item( 4,0);
    general_extensions_table->setItem(4,0, new QTableWidgetItem(""));
    general_extensions_table->setItem(4,1, new QTableWidgetItem(""));

    general_extensions_table->item( 4,0)->setBackgroundColor(  Qt::blue );
    general_extensions_table->item( 4,1)->setBackgroundColor(  Qt::red );
    general_extensions_table_index = 4;
    //QPalette pal = widget.palette();
    //pal.setColor(widget.backgroundRole(), Qt::blue);

    //general_extensions_table->item( 4,1)->setBackgroundColor(  Qt::blue );
    connect( general_extensions_table,SIGNAL(cellChanged(int,int)),this,SLOT(cellChanged(int,int)));


    general_extensions_table->setAlternatingRowColors( true );
    general_extensions_table->setDragDropMode( QAbstractItemView::NoDragDrop );

    //Fix row height
    general_extensions_table->setFixedHeight( 300 );
    general_extensions_table->resizeColumnsToContents();
    general_extensions_table->resizeRowsToContents();
    //QLabel*  general_extensions_label = new QLabel("Save Extensions");
    //gereral_extensions_layout->addWidget( general_extensions_label );
    gereral_extensions_layout->addWidget( general_extensions_table );

    gereral_layout->addWidget( gereral_extensions );
    //</general/extensions>
    //<shortcuts>
    shortcuts_scroll = new QScrollArea();
    shortcuts_scroll->setWidgetResizable( true );
    tab_control->addTab( shortcuts_scroll, *iconpack::instance()->get_icon( iconpack::icon_help ),  "Shortcuts" );


    QWidget *shortcuts_scroll_inside = new QWidget( );
    QVBoxLayout * shortcuts_scroll_layout = new QVBoxLayout();
    shortcuts_scroll_layout->setMargin( 2 );
    shortcuts_scroll_inside->setLayout( shortcuts_scroll_layout );

    //<shortcuts/table>
    shortcuts_table = new QTableWidget(0,2);

    //connect( shortcuts_table,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(currentTChanged(int,int,int,int)));
    connect(shortcuts_table,SIGNAL(currentCellChanged(int,int,int,int)),
                this,SLOT(shortcuts_table_selection_changed(int,int,int,int)));
    shortcuts_scroll_layout->addWidget(shortcuts_table);

    QStringList shortcuts_table_labels;
    shortcuts_table_labels << tr("Actrion") << tr("Shortcut");
    shortcuts_table->setHorizontalHeaderLabels(shortcuts_table_labels);
    shortcuts_table->setSelectionMode( QAbstractItemView::SingleSelection );
    shortcuts_table->setSelectionBehavior( QAbstractItemView::SelectRows );
    shortcuts_table->horizontalHeader()->setStretchLastSection(true);
    shortcuts_table->verticalHeader()->hide();
    //shortcuts_table->setShowGrid(false);
    //shortcuts_table->rowCount();
    shortcuts_table->setRowCount( MainWindow::action_about +1 );

    /* QTableWidgetItem *newItem = new QTableWidgetItem(*iconpack::instance()->get_icon( iconpack::icon_new ),"New");
    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
    connect( shortcuts_table, SIGNAL(cellChanged(int,int)),this, SLOT(shortcuts_table_update_cell(int,int)) );
    shortcuts_table->setItem(0, 0, newItem); // new QTableWidgetItem("New"));
    shortcuts_table->setItem(0, 1, new QTableWidgetItem("CTRL + N"));
    QTableWidgetItem *openItem = new QTableWidgetItem(*iconpack::instance()->get_icon( iconpack::icon_open ),"Open");
    */
    //openItem->setFlags(openItem->flags() ^ Qt::ItemIsEditable);
    QAction **actions =  MainWindow::instance()->Actions;
    for( int i = 0 ; i <= MainWindow::action_about; i++){
        QTableWidgetItem *newItem = new QTableWidgetItem( actions[i]->icon(), actions[i]->text() );
        newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        shortcuts_table->setItem(i, 0, newItem);
        shortcuts_table->setItem(i, 1, new QTableWidgetItem( actions[i]->shortcut().toString( ).toUpper().replace(" ","")));
    }
    /*
    shortcuts_table->setItem(1, 0, openItem); //new QTableWidgetItem("Open"));
    shortcuts_table->setItem(1, 1, new QTableWidgetItem("CTRL + O"));*/
    shortcuts_table->setAlternatingRowColors( true );
    shortcuts_table->setDragDropMode( QAbstractItemView::NoDragDrop );

    //Fix row height
    //shortcuts_table->setFixedHeight( 300 );
    shortcuts_table->resizeColumnsToContents();
    shortcuts_table->resizeRowsToContents();
    //</shortcuts/table>
    //<shortcuts/edit_group>
    shortcuts_edit_group = new QGroupBox("Edit");
    QHBoxLayout* shortcuts_edit_group_layout = new QHBoxLayout();
    shortcuts_edit_group_layout->setMargin( 2 );
    shortcuts_edit_group->setLayout( shortcuts_edit_group_layout );
    shortcuts_edit_control = new QCheckBox("Control");
    shortcuts_edit_shift = new QCheckBox("Shift");
    shortcuts_edit_alt = new QCheckBox("Alt");
    shortcuts_edit_key = new QComboBox();
    QStringList key_list;
    key_list << "" <<"A"<<
    "B"<<    "C"<<    "D"<<    "E"<<    "F"<<
    "G"<<    "H"<<    "I"<<    "J"<<    "K"<<
    "L"<<    "M"<<    "N"<<    "O"<<
    "P"<<    "Q"<<    "R"<<    "S"<<
    "T"<<    "U"<<    "V"<<
    "W"<<    "X"<<    "Y"<<    "Z"<<
    "0"<<    "1"<<    "2"<<    "3"<<
    "4"<<    "5"<<    "6"<<
    "7"<<    "8"<<    "9"<<
    "F1"<<    "F2"<<
    "F3"<<    "F4"<<
    "F5"<<    "F6"<<    "F7"<<    "F8"<<    "F9"<<    "F10"<<    "F11"<<    "F12"<<    "Left"<<
    "Right"<<
    "Up"<<
    "Down"<<
    "Del"<<
    "End"<<
    "Ins"<<

    "Pause"<<
               "`";
              shortcuts_edit_key->addItems(key_list);
    shortcuts_edit_group_layout->addWidget( shortcuts_edit_control );
    shortcuts_edit_group_layout->addWidget( shortcuts_edit_shift );
    shortcuts_edit_group_layout->addWidget( shortcuts_edit_alt );
    shortcuts_edit_group_layout->addWidget( shortcuts_edit_key );

    shortcuts_scroll_layout->addWidget(shortcuts_edit_group);
    //</shortcuts/edit_group>

    //<shortcuts/edit_buttons>
    shortcuts_edit_buttons = new QDialogButtonBox( QDialogButtonBox::Apply | QDialogButtonBox::Cancel |  QDialogButtonBox::RestoreDefaults );
    QPushButton* shortcuts_edit_buttons_apply = shortcuts_edit_buttons->button( QDialogButtonBox::Apply );
    connect(shortcuts_edit_buttons_apply, SIGNAL(clicked()), this, SLOT(shortcuts_edit_buttons_apply()));
    QPushButton* shortcuts_edit_buttons_cancel = shortcuts_edit_buttons->button( QDialogButtonBox::Cancel );
    connect(shortcuts_edit_buttons_cancel, SIGNAL(clicked()), this, SLOT(shortcuts_edit_buttons_cancel()));
    QPushButton* shortcuts_edit_buttons_restore_defaults = shortcuts_edit_buttons->button( QDialogButtonBox::RestoreDefaults );
    connect( shortcuts_edit_buttons_restore_defaults , SIGNAL(clicked()), this, SLOT(shortcuts_edit_buttons_restore_defaults()));
    shortcuts_scroll_layout->addWidget(shortcuts_edit_buttons);
    //</shortcuts/edit_buttons>

    /*shortcuts_form = new QFormLayout();
    shortcuts_scroll_inside->setLayout( shortcuts_form );
    shortcuts_form->addRow("XAXAX", new QLineEdit() );
    shortcuts_form->addRow("XAXAX2", new QLineEdit() );
    shortcuts_form->addRow("XAXAX3", new QLineEdit() );
    shortcuts_form->addRow("XAXAX", new QLineEdit() );
    shortcuts_form->addRow("XAXAX2", new QLineEdit() );
    shortcuts_form->addRow("XAXAX3", new QLineEdit() );*/


    shortcuts_scroll->setWidget( shortcuts_scroll_inside );
    //</shortcuts>
    //<icons>
    icons_scroll = new QScrollArea();
    icons_scroll->setWidgetResizable( true );
    tab_control->addTab( icons_scroll, *iconpack::instance()->get_icon( iconpack::icon_save ),  "Icons" );


    QWidget *icons_scroll_inside = new QWidget( );

    icons_form = new QFormLayout();
    icons_scroll_inside->setLayout( icons_form );
    icons_form->addRow("XAXAX", new QLineEdit() );
    icons_form->addRow("XAXAX2", new QLineEdit() );
    icons_form->addRow("XAXAX3", new QLineEdit() );
    icons_form->addRow("XAXAX", new QLineEdit() );
    icons_form->addRow("XAXAX2", new QLineEdit() );
    icons_form->addRow("XAXAX3", new QLineEdit() );

    icons_scroll->setWidget( icons_scroll_inside );
    //</icons>
    //<toolbars>
    toolbars_control = new QWidget();
    tab_control->addTab( toolbars_control, *iconpack::instance()->get_icon( iconpack::icon_moveToWindow ),  "Toolbars" );
    QVBoxLayout *toolbars_layout = new QVBoxLayout();
    toolbars_layout->setMargin( 2 );
    toolbars_control->setLayout( toolbars_layout );
    QWidget * toolbars_controls = new QWidget();
    QHBoxLayout * toolbars_controls_layout = new  QHBoxLayout();
    toolbars_controls_layout->setMargin( 2 );
    toolbars_controls->setLayout( toolbars_controls_layout  );

    toolbars_table = new QTableWidget(0,2);
    QStringList toolbars_table_labels;
    toolbars_table_labels << tr("Name") << tr("Version");
    toolbars_table->setHorizontalHeaderLabels( toolbars_table_labels );
    toolbars_table->verticalHeader()->hide();
    toolbars_controls_layout->addWidget(toolbars_table);
    toolbars_table->setRowCount(1);
    QTableWidgetItem *ttt = new QTableWidgetItem("XX");
    ttt->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    ttt->setCheckState( Qt::Checked );

    toolbars_table->setItem(0,0, ttt );

    toolbars_table->setAlternatingRowColors( true );
    toolbars_table->setDragDropMode( QAbstractItemView::NoDragDrop );
    toolbars_table->setSelectionMode( QAbstractItemView::SingleSelection );
    toolbars_table->setSelectionBehavior( QAbstractItemView::SelectRows );
    toolbars_table->horizontalHeader()->setStretchLastSection(true);

    toolbars_table->resizeColumnsToContents();
    toolbars_table->resizeRowsToContents();

    toolbar_buttons = new  QDialogButtonBox( );

    toolbar_buttons->setOrientation( Qt::Vertical );

    toolbar_buttons_add = new QPushButton( *iconpack::instance()->get_icon( iconpack::icon_new ), "Add");
    toolbar_buttons->addButton( toolbar_buttons_add, QDialogButtonBox::NoRole );

    toolbar_buttons_delete = new QPushButton( *iconpack::instance()->get_icon( iconpack::icon_close ), "Delete");
    toolbar_buttons->addButton( toolbar_buttons_delete, QDialogButtonBox::NoRole );

    toolbar_buttons_browse = new QPushButton( *iconpack::instance()->get_icon( iconpack::icon_open ), "Browse");
    toolbar_buttons->addButton( toolbar_buttons_browse, QDialogButtonBox::NoRole );

    toolbar_buttons_up = new QPushButton( "Up");
    toolbar_buttons->addButton( toolbar_buttons_up, QDialogButtonBox::NoRole );

    toolbar_buttons_down = new QPushButton( "Down");
    toolbar_buttons->addButton( toolbar_buttons_down, QDialogButtonBox::NoRole );

    toolbar_buttons_download = new QPushButton( "Download");
    toolbar_buttons->addButton( toolbar_buttons_download, QDialogButtonBox::NoRole );

    toolbars_controls_layout->addWidget( toolbar_buttons );
    toolbars_layout->addWidget( toolbars_controls );

    toolbars_details_group = new QGroupBox();
    QGridLayout *toolbars_details_layout = new  QGridLayout();
    toolbars_details_layout->setMargin( 2 );
    toolbars_details_group->setLayout( toolbars_details_layout );
    QLabel *toolbars_name_label =  new   QLabel("Name :");
    toolbars_name =  new   QLabel("XXX");
    QLabel *toolbars_author_label =  new   QLabel("Author :");
    toolbars_author =  new   QLabel("YYY");
    QLabel *toolbars_version_label =  new   QLabel("Version :");
    toolbars_version =  new   QLabel("ZZZ");
    QLabel *toolbars_description_label =  new   QLabel("Description :");
    toolbars_description =  new   QLabel("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT  TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
    toolbars_description->setWordWrap( true );

    toolbars_details_layout->addWidget(toolbars_name_label,0,0);
    toolbars_details_layout->addWidget(toolbars_name,0,1);
    toolbars_details_layout->addWidget(toolbars_author_label,0,2);
    toolbars_details_layout->addWidget(toolbars_author,0,3);
    toolbars_details_layout->addWidget(toolbars_version_label,0,4);
    toolbars_details_layout->addWidget(toolbars_version,0,5);
    toolbars_details_layout->addWidget(toolbars_description_label,1,0);
    toolbars_details_layout->addWidget( toolbars_description,1,1,1,5);
    //shortcuts_details_layout->addWidget( MainWindow::instance()->mainToolBar,2,0);

    toolbars_layout->addWidget( toolbars_details_group );
    //</toolbars>
    this->setWindowIcon( *iconpack::instance()->get_icon( iconpack::icon_settings) );

    QPushButton* applyButton = buttons->button( QDialogButtonBox::Apply );
    connect(applyButton, SIGNAL(clicked()), this, SLOT(close()));

    QPushButton* cancelButton = buttons->button( QDialogButtonBox::Cancel );
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}
void SettingsDialog::shortcuts_table_selection_changed(  int x, int y,int px, int py ){

    if( x >= shortcuts_table->rowCount() ||  !shortcuts_table->item( x,1)  ){
        shortcuts_edit_buttons->button( QDialogButtonBox::Apply )->setEnabled( false );

        shortcuts_edit_buttons->button( QDialogButtonBox::Cancel )->setEnabled( false );
        shortcuts_edit_control->setChecked( false );
        shortcuts_edit_shift->setChecked( false );
        shortcuts_edit_alt->setChecked( false );
        shortcuts_edit_key->setCurrentIndex(0);
        return;
    }
    //qDebug() << shortcuts_table->item( x,y )->text();
    QString shortcut =  shortcuts_table->item( x,1 )->text().trimmed().replace(" ","").toLower();
    shortcuts_edit_control->setChecked( shortcut.contains( "ctrl" ) );
    shortcuts_edit_shift->setChecked( shortcut.contains( "shift" ) );
    shortcuts_edit_alt->setChecked( shortcut.contains( "alt" ) );
    shortcut.replace( "shift+","").replace( "ctrl+","").replace( "alt+","");
    int index = shortcuts_edit_key->findText(shortcut, Qt::MatchFixedString );

    shortcuts_edit_key->setCurrentIndex(index);
    shortcuts_edit_buttons->button( QDialogButtonBox::Apply )->setEnabled( true );
    shortcuts_edit_buttons->button( QDialogButtonBox::Cancel )->setEnabled( true );
}
void SettingsDialog::shortcuts_edit_buttons_apply( ){
    qDebug() << "Apply";
    int index = shortcuts_table->currentRow();
    if( shortcuts_edit_key->currentIndex() == 0 || ( !shortcuts_edit_control->checkState()&&!shortcuts_edit_shift->checkState() && !shortcuts_edit_alt->checkState() ) ){
        shortcuts_table->item( index,1 )->setText( "" );
    }else if( index > 0){
        QString new_key = "";
        if( shortcuts_edit_control->checkState() ){
            new_key += "CTRL+";
        }
        if( shortcuts_edit_shift->checkState() ){
            new_key += "SHIFT+";
        }
        if( shortcuts_edit_alt->checkState() ){
            new_key += "ALT+";
        }
        new_key += shortcuts_edit_key->currentText().toUpper();
        qDebug() << index;
        shortcuts_table->item( index,1 )->setText( new_key );
    }
}
void SettingsDialog::shortcuts_edit_buttons_cancel(){
    //reopen row values
    this->shortcuts_table_selection_changed( shortcuts_table->currentRow(), 1,shortcuts_table->currentRow(),1);
}
void SettingsDialog::shortcuts_edit_buttons_restore_defaults(){
    QVector< QPair<int,QString> > *defaults = new QVector< QPair<int,QString> >();

    defaults->append( QPair<int,QString>( MainWindow::action_new,"CTRL+N") );
    defaults->append( QPair<int,QString>( MainWindow::action_open,"CTRL+O") );
    defaults->append( QPair<int,QString>( MainWindow::action_save,"CTRL+S") );
    defaults->append( QPair<int,QString>( MainWindow::action_saveAs,"CTRL+SHIFT+S") );



    defaults->append( QPair<int,QString>( MainWindow::action_close,"CTRL+W") );

    defaults->append( QPair<int,QString>( MainWindow::action_undo,"CTRL+Z") );
    defaults->append( QPair<int,QString>( MainWindow::action_redo,"CTRL+Y") );
    defaults->append( QPair<int,QString>( MainWindow::action_copy,"CTRL+C") );
    defaults->append( QPair<int,QString>( MainWindow::action_cut,"CTRL+X") );
    defaults->append( QPair<int,QString>( MainWindow::action_paste,"CTRL+P") );
    defaults->append( QPair<int,QString>( MainWindow::action_selectAll,"CTRL+A") );
    defaults->append( QPair<int,QString>( MainWindow::action_find,"CTRL+F") );
    defaults->append( QPair<int,QString>( MainWindow::action_replace,"CTRL+H") );
    defaults->append( QPair<int,QString>( MainWindow::action_console,"CTRL+`") );
    defaults->append( QPair<int,QString>( MainWindow::action_exit,"ALT+F4") );

    for(int i=0 ; i< shortcuts_table->rowCount();i++  ){
        shortcuts_table->item( i,1)->setText("");
    }
    for(int i=0 ; i<defaults->count();i++  ){       
        shortcuts_table->item( (int)defaults->at(i).first ,1)->setText( defaults->at(i).second );
    }
}
 void SettingsDialog::cellChanged(int x,int y){
     qDebug() << x << y;
     if( x == general_extensions_table_index ){//&& general_extensions_table->rowCount() - 1 ){
         general_extensions_table->setRowCount( x + 2 );
         general_extensions_table->setItem(x+1,0,new QTableWidgetItem(""));
         general_extensions_table->setItem(x+1,1,new QTableWidgetItem(""));
         general_extensions_table->item(x+1,0)->setBackgroundColor( QColor(200,100,100,70) );
         general_extensions_table->item(x+1,1)->setBackgroundColor( QColor(200,100,100,70) );
         general_extensions_table_index = x+1;
     }
 }
