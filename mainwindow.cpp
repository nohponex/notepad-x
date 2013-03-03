#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>

#include <QtWidgets/QActionGroup>
#include <Components/tabwidgetx.h>
#include <Components/tabbarx.h>

#include <Classes/iconpack.h>
#include <Documents/defaultdocument.h>


#include <QKeySequence>
#include <QCloseEvent>

#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QtWidgets/QFileDialog>
#include <Documents/IDocument.h>
#include <Documents/documenttypes.h>
#include <QSettings>
#include <vector>
//Dialogs
#include <Dialogs/aboutdialog.h>
#include <Dialogs/settingsdialog.h>


#include <Components/externalwindow.h>
#include <Classes/templatedocument.h>
#include <QtWidgets/QGroupBox>

#include <QDesktopServices>
#include <QUrl>

#include <Classes/json.h>
#include <QFileInfoList>
#include <Components/console.h>
#include <Components/findreplace.h>

#include <Classes/toolbar.h>
//#include <Documents/testdocument.h>
#include <QPropertyAnimation>

//TO REMOVE
#include <QtWidgets/QLineEdit>
MainWindow* MainWindow::s_instance = 0;

std::vector<IDocument*> IDocument::types;

MainWindow* MainWindow::instance(){
    if (!s_instance){
        s_instance = new MainWindow();
    }
    return s_instance;
}
MainWindow::MainWindow() : QMainWindow(0){

    new DefaultDocument("default_document");
    //new TestDocument("test_document");
    //json *j = new json();
    //j->parse( "my ass ");

    selected_tab = 0;
    document_index = 0;
    console = 0;
    findReplace_dialog = 0 ;

    setAcceptDrops( true );
    this->setWindowOpacity( 0 );
    //setup_main_window();
}
void MainWindow::setup_main_window(){


    //setDockNestingEnabled( true );
    QDir templates_dir("templates/");
    if (!templates_dir.exists()) {
        //qDebug()<< "create";
        templates_dir.mkpath(".");
    }

    QFileInfoList  templateFiles = templates_dir.entryInfoList(QDir::Files);

    for( int i = 0 ; i< templateFiles.count() ; i++){
       templates.push_back( new templateDocument( templateFiles.at(i).absoluteFilePath(), templateFiles.at(i).fileName() , "" ) );
    }

    QSettings settings("NohponeX", "Notepad X");

    move( settings.value("position", QPoint(200, 200)).toPoint() );

    resize( settings.value("size", QSize(400, 400)).toSize() );

    if( settings.value("maximized", false).toBool() ){
        showMaximized();
    }
    enable_projects = settings.value("enable_projects",true).toBool();

    recent_documents = settings.value("recent_documents").toStringList();
    recent_documents_max = 5;

    show_toolbar_in_external = true;
    default_document_type =  settings.value("default_document_type", 0).toInt();
    if( default_document_type >= IDocument::count() ){
        default_document_type = 0;
    }
    show_other_document_types = settings.value("show_other_document_types", true).toBool();
    //main_panel
    main_panel = new QSplitter( Qt::Horizontal );

    editor_panel = new QSplitter( Qt::Vertical );

    editor_row_0 = new QSplitter( Qt::Horizontal );

    tab_widget_0 = new TabWidgetX( );

    editor_row_0->addWidget( tab_widget_0 );

    editor_panel->addWidget( editor_row_0 );
    main_panel->setOpaqueResize( false );
    //left sidebar main_panel->addWidget( new TabWidgetX() );
    main_panel->addWidget( editor_panel );
    //right sidebar main_panel->addWidget( new TabWidgetX() );
    selected_tab_control = tab_widget_0;

    this->setCentralWidget( main_panel );
    /*
    Actions --------------------
    */
    //New
    Actions[ MainWindow::action_new ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_new ) ,"New",this);
    connect(Actions[ MainWindow::action_new ], SIGNAL(triggered()), this, SLOT(file_new()));
    //Open
    Actions[ MainWindow::action_open ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_open ) ,"Open..",this);
    connect(Actions[ MainWindow::action_open ], SIGNAL(triggered()), this, SLOT(file_open()));
    //Recent
    //Actions[ MainWindow::action_recent ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_recent ) ,"Recent",this);
    //Actions[ MainWindow::action_recent ] ->setIconVisibleInMenu( true );
    //Recent Clear
    Actions[ MainWindow::action_recent_clear ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_close ) ,"Clear",this);
    connect(Actions[ MainWindow::action_recent_clear ], SIGNAL(triggered()), this, SLOT( file_recent_clear()) );
    //Save
    Actions[ MainWindow::action_save ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_save ) ,"Save..",this);
    connect(Actions[ MainWindow::action_save ], SIGNAL(triggered()), this, SLOT(file_save()));
    //Save As
    Actions[ MainWindow::action_saveAs ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_saveAs ) ,"Save as..",this);
    connect(Actions[ MainWindow::action_saveAs ], SIGNAL(triggered()), this, SLOT(file_saveAs()));
    //Close
    Actions[ MainWindow::action_close ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_close ) ,"Close",this);
    connect(Actions[ MainWindow::action_close ], SIGNAL(triggered()), this, SLOT(file_close()));
    //Print
    Actions[ MainWindow::action_print ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_print ) ,"Print",this);
    connect(Actions[ MainWindow::action_print ], SIGNAL(triggered()), this, SLOT(file_print()));
    //Print Preview
    Actions[ MainWindow::action_printPreview ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_printPreview ) ,"Print Preview",this);
    connect(Actions[ MainWindow::action_printPreview ], SIGNAL(triggered()), this, SLOT(file_printPreview()));
    //Page Setup
    Actions[ MainWindow::action_pageSetup ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_pageSetup ) ,"Page Setup",this);
    connect(Actions[ MainWindow::action_pageSetup ], SIGNAL(triggered()), this, SLOT(file_pageSetup()));

    //Exit
    Actions[ MainWindow::action_exit ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_exit ) ,"Exit",this);
    connect(Actions[ MainWindow::action_exit ], SIGNAL(triggered()), this, SLOT(close()));

    //EDIT
    //Copy
    Actions[ MainWindow::action_copy ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_copy ) ,"Copy",this);
    connect(Actions[ MainWindow::action_copy ], SIGNAL(triggered()), this, SLOT(edit_copy()));
    //Cut
    Actions[ MainWindow::action_cut ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_cut ) ,"Cut",this);
    connect(Actions[ MainWindow::action_cut ], SIGNAL(triggered()), this, SLOT(edit_cut()));
    //Paste
    Actions[ MainWindow::action_paste ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_paste ) ,"Paste",this);
    connect(Actions[ MainWindow::action_paste ], SIGNAL(triggered()), this, SLOT(edit_paste()));
    //Select All
    Actions[ MainWindow::action_selectAll ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_selectAll ) ,"Select All",this);
    connect(Actions[ MainWindow::action_selectAll ], SIGNAL(triggered()), this, SLOT(edit_selectAll()));
    //Undo
    Actions[ MainWindow::action_undo ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_undo ) ,"Undo",this);
    connect(Actions[ MainWindow::action_undo ], SIGNAL(triggered()), this, SLOT(edit_undo()));
    //Redo
    Actions[ MainWindow::action_redo ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_redo ) ,"Redo",this);
    connect(Actions[ MainWindow::action_redo ], SIGNAL(triggered()), this, SLOT(edit_redo()));
    //Find
    Actions[ MainWindow::action_find ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_find ) ,"Find",this);
    connect(Actions[ MainWindow::action_find ], SIGNAL(triggered()), this, SLOT(edit_find()));
    //Replace
    Actions[ MainWindow::action_replace ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_replace ) ,"Replace",this);
    connect(Actions[ MainWindow::action_replace ], SIGNAL(triggered()), this, SLOT(edit_replace()));


    //Tab

    //Close Others
    Actions[ MainWindow::action_closeOthers ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_closeOthers ) ,"Close Others",this);
    connect(Actions[ MainWindow::action_closeOthers ], SIGNAL(triggered()), this, SLOT(tab_closeOthers()));
    //Close All
    Actions[ MainWindow::action_closeAll ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_closeAll ) ,"Close All",this);
    connect(Actions[ MainWindow::action_closeAll ], SIGNAL(triggered()), this, SLOT(tab_closeAll()));
    //Next
    Actions[ MainWindow::action_next ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_next ) ,"Next",this);
    connect(Actions[ MainWindow::action_next ], SIGNAL(triggered()), this, SLOT(tab_next()));
    //Previous
    Actions[ MainWindow::action_previous ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_previous ) ,"Previous",this);
    connect(Actions[ MainWindow::action_previous ], SIGNAL(triggered()), this, SLOT(tab_previous()));
    //Open in new window
    Actions[ MainWindow::action_moveToNew ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_moveToNewWindow ) ,"Move to new window",this);
    connect(Actions[ MainWindow::action_moveToNew ], SIGNAL(triggered()), this, SLOT(tab_moveToNew()));
    //Browse folder
    Actions[ MainWindow::action_browse_folder ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_open ) ,"Browse folder",this);
    connect(Actions[ MainWindow::action_browse_folder ], SIGNAL(triggered()), this, SLOT(tab_browser_folder()));

    //View
    //Layout Manage
    Actions[ MainWindow::action_layout_manage ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout ) ,"Manage..",this);
    connect(Actions[ MainWindow::action_layout_manage ], SIGNAL(triggered()), this, SLOT(layout_manage()));
    //Layout Add Col
    Actions[ MainWindow::action_layout_addCol ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_addCol ) ,"Add Column",this);
    connect(Actions[ MainWindow::action_layout_addCol ], SIGNAL(triggered()), this, SLOT(layout_addCol()));
    //Layout Add Row
    Actions[ MainWindow::action_layout_addRow ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_addRow ) ,"Add Row",this);
    connect(Actions[ MainWindow::action_layout_addRow ], SIGNAL(triggered()), this, SLOT(layout_addRow()));
    //Layout Default
    Actions[ MainWindow::action_layout_default ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_default ) ,"Default",this);
    connect(Actions[ MainWindow::action_layout_default ], SIGNAL(triggered()), this, SLOT(layout_default()));
    //Layout Split
    Actions[ MainWindow::action_layout_split ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_split ) ,"Split",this);
    //Layout Split Vertical
    Actions[ MainWindow::action_layout_splitVertical ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_splitVertical ) ,"Split Vertical",this);
    //Layout Grid
    Actions[ MainWindow::action_layout_grid ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_layout_grid ) ,"Grid",this);
    //Console
    Actions[ MainWindow::action_console ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_console ) ,"Console",this);
    connect(Actions[ MainWindow::action_console ], SIGNAL(triggered()), this, SLOT(view_console()));
    Actions[ MainWindow::action_console ]->setShortcut(   QKeySequence("CTRL+`") );

    //Tools

    //Settings
    Actions[ MainWindow::action_settings ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_settings ) ,"Settings",this);
    connect(Actions[ MainWindow::action_settings ], SIGNAL(triggered()), this, SLOT(tools_settings()));

    //Project

    //Create
    Actions[ MainWindow::action_projectsCreate ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_projectsCreate ) ,"Create Project",this);
    Actions[ MainWindow::action_projectsOpen ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_projects ) ,"Open Project",this);

    //Help

    //Help
    Actions[ MainWindow::action_help ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_help ) ,"Help",this);
    connect(Actions[ MainWindow::action_help ], SIGNAL(triggered()), this, SLOT(help_help()));
    //Donate
    Actions[ MainWindow::action_donate ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_donate ) ,"Donate",this);
    connect(Actions[ MainWindow::action_donate ], SIGNAL(triggered()), this, SLOT(help_donate()));
    //Website
    Actions[ MainWindow::action_website ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_website ) ,"Website",this);
    connect(Actions[ MainWindow::action_website ], SIGNAL(triggered()), this, SLOT(help_website()));
    //About
    Actions[ MainWindow::action_about ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_about ) ,"About",this);
    connect(Actions[ MainWindow::action_about ], SIGNAL(triggered()), this, SLOT(help_about()));
    //Feature request
    Actions[ MainWindow::action_featureRequest ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_featureRequest ) ,"Feature request",this);
    connect(Actions[ MainWindow::action_featureRequest ], SIGNAL(triggered()), this, SLOT(help_featureRequest()));
    //Bug report
    Actions[ MainWindow::action_bugReport ] = new QAction( *iconpack::instance()->get_icon( iconpack::icon_bugReport ) ,"Bug report",this);
    connect(Actions[ MainWindow::action_bugReport ], SIGNAL(triggered()), this, SLOT(help_bugReport()));

    //Shortcuts
    for( int a = 0 ; a < MainWindow::action_about ; a++ ){
        if ( settings.contains("shortcut_" + QString(a) ) ){
            //Actions[ a ]->setShortcut( QKeySequence( settings.value( "shortcut_" + a ).toString() ) );
        }
    }

    validDocumentActions = new QActionGroup( this );

    validDocumentActions->addAction( Actions[ MainWindow::action_save ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_saveAs ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_print ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_printPreview ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_pageSetup ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_copy ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_cut ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_paste ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_selectAll ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_undo ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_redo ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_find ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_next ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_previous ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_replace ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_close ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_closeOthers ] );
    validDocumentActions->addAction( Actions[ MainWindow::action_moveToNew ] );

    validDocumentActions->setDisabled( true );

    /*
    Menu-------------------------------
    */
    fileMenu = menuBar()->addMenu("&File");

    fileMenu-> addAction( Actions[ MainWindow::action_new ] );

    if( templates.size() > 0 ){
        file_templatesMenu = fileMenu->addMenu( "templates" );
        //file_templatesMenu ->menuAction()->setShortcut( QKeySequence::Find );
        //file_templatesMenu->setDefaultAction( Actions[ MainWindow::action_new ]  );
        //file_templatesMenu->setActiveAction( );
        int size = templates.size();
        for( int i = 0 ; i < size ; i++ ){
            // new QString( ((templateDocument*))->getName() ));
            QAction * newTemplate = new QAction( *iconpack::instance()->get_icon( iconpack::icon_new ), templates[ i ]->getName(), this);
            newTemplate->setData( i );
            connect( newTemplate, SIGNAL(triggered()) , this, SLOT( file_templateOpen()));
            file_templatesMenu->addAction( newTemplate );
        }
    }

        //  }
    //Actions[ MainWindow::action_new ]->menu()->addAction( Actions[ MainWindow::action_open ]);
    fileMenu->addSeparator();
    fileMenu->addAction(  Actions[ MainWindow::action_open ] );

    file_recentMenu = fileMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_recent ) ,"Recent" );
    //file_recentMenu->menuAction();
    //file_recentMenu->addAction(  Actions[ MainWindow::action_recent_clear ] );

    fileMenu->addSeparator();
    fileMenu->addAction(  Actions[ MainWindow::action_save] );
    fileMenu->addAction(  Actions[ MainWindow::action_saveAs ] );
    fileMenu->addSeparator();
    fileMenu->addAction( Actions[ MainWindow::action_close ] );
    fileMenu->addSeparator();
    fileMenu->addAction(  Actions[ MainWindow::action_print ] );
    fileMenu->addAction(  Actions[ MainWindow::action_printPreview ] );
    fileMenu->addAction(  Actions[ MainWindow::action_pageSetup ] );
    fileMenu->addSeparator();
    fileMenu->addAction( Actions[ MainWindow::action_exit ] );


    editMenu = menuBar()->addMenu("&Edit");

    editMenu->addAction( Actions[ MainWindow::action_undo ] );
    editMenu->addAction( Actions[ MainWindow::action_redo ] );
    editMenu->addSeparator();
    editMenu->addAction( Actions[ MainWindow::action_copy ] );
    editMenu->addAction( Actions[ MainWindow::action_cut ] );
    editMenu->addAction( Actions[ MainWindow::action_paste ] );
    editMenu->addSeparator();
    editMenu->addAction( Actions[ MainWindow::action_selectAll ] );
    editMenu->addSeparator();
    editMenu->addAction( Actions[ MainWindow::action_find ] );
    editMenu->addAction( Actions[ MainWindow::action_replace ] );


    tabMenu = menuBar()->addMenu("Tabs");

    tabMenu->addAction( Actions[ MainWindow::action_new ] );
    tabMenu->addSeparator();
    tabMenu->addAction( Actions[ MainWindow::action_next ] );
    tabMenu->addAction( Actions[ MainWindow::action_previous ] );
    tabMenu->addSeparator();
    tabMenu->addAction( Actions[ MainWindow::action_close ] );
    tabMenu->addAction( Actions[ MainWindow::action_closeOthers ] );
    tabMenu->addAction( Actions[ MainWindow::action_closeAll ] );

    viewMenu = menuBar()->addMenu("View");
    layoutMenu = viewMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_layout ) ,"Layout" );
    viewMenu->addSeparator();
    layoutMenu->addAction( Actions[ MainWindow::action_layout_addCol ] );
    layoutMenu->addAction( Actions[ MainWindow::action_layout_addRow ] );
    layoutMenu->addAction( Actions[ MainWindow::action_layout_manage ] );
    layoutMenu->addSeparator();
    layoutMenu->addAction( Actions[ MainWindow::action_layout_default ] );
    layoutMenu->addAction( Actions[ MainWindow::action_layout_split ] );
    layoutMenu->addAction( Actions[ MainWindow::action_layout_splitVertical ] );
    layoutMenu->addAction( Actions[ MainWindow::action_layout_grid ] );


    viewMenu->addAction( Actions[ MainWindow::action_console ] );
    view_languageMenu = viewMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_language ) ,"Language" );
    //view_languageMenu->setIcon( * iconpack::instance()->get_icon( iconpack::icon_language ) );
    view_windowsMenu = viewMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_window ) ,"Windows" );
    //view_windowsMenu->setIcon( * iconpack::instance()->get_icon( iconpack::icon_window ) );

    projectsMenu = menuBar()->addMenu( "Projects" );

    projectsMenu->addAction( Actions[ MainWindow::action_projectsCreate ] );
    projectsMenu->addAction( Actions[ MainWindow::action_projectsOpen ] );

    projects_recentMenu = projectsMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_projectsRecent ),"Recent Projects");
    projectsMenu->addSeparator();

    toolsMenu = menuBar()->addMenu("Tools");

    toolsMenu->addAction( Actions[ MainWindow::action_settings ] );



    helpMenu = menuBar()->addMenu("Help");

    helpMenu->addAction( Actions[ MainWindow::action_help ] );
    helpMenu->addSeparator();
    helpMenu->addAction( Actions[ MainWindow::action_bugReport ] );
    helpMenu->addAction( Actions[ MainWindow::action_featureRequest ] );
    helpMenu->addSeparator();
    helpMenu->addAction( Actions[ MainWindow::action_website ] );
    helpMenu->addAction( Actions[ MainWindow::action_donate ] );
    helpMenu->addSeparator();
    helpMenu->addAction( Actions[ MainWindow::action_about ] );

    editor_contextMenu = new QMenu(this);

    editor_contextMenu->addAction( Actions[ MainWindow::action_undo ] );
    editor_contextMenu->addAction( Actions[ MainWindow::action_redo ] );
    editor_contextMenu->addSeparator();
    editor_contextMenu->addAction( Actions[ MainWindow::action_copy ] );
    editor_contextMenu->addAction( Actions[ MainWindow::action_cut ] );
    editor_contextMenu->addAction( Actions[ MainWindow::action_paste ] );
    editor_contextMenu->addSeparator();
    editor_contextMenu->addAction( Actions[ MainWindow::action_selectAll ] );
    editor_contextMenu->addSeparator();
    editor_contextMenu->addAction( Actions[ MainWindow::action_close] );

    tabs_contextMenu = new QMenu(this);
    tabs_contextMenu->addAction( Actions[ MainWindow::action_new ] );
    tabs_contextMenu->addSeparator();
    tabs_contextMenu->addAction( Actions[ MainWindow::action_browse_folder ] );
    tabs_contextMenu->addSeparator();
    tabs_contextMenu->addAction( Actions[ MainWindow::action_close ] );
    tabs_contextMenu->addAction( Actions[ MainWindow::action_closeOthers ] );
    tabs_contextMenu->addAction( Actions[ MainWindow::action_closeAll ] );
    tabs_contextMenu->addSeparator();
    tabs_contextMenu->addAction( Actions[ MainWindow::action_moveToNew ] );


    tabs_moveToWinodwMenu = tabs_contextMenu->addMenu( *iconpack::instance()->get_icon( iconpack::icon_moveToWindow ),"Move to window ->" ); //tabs_contextMenu->addMenu( "Move to window ->" );
    //tabs_moveToWinodwMenu->setIcon( *  );

    //tabs_contextMenu->addMenu( tabs_moveToWinodwMenu );
    tabMenu->addSeparator();

    tabMenu->addAction(  Actions[ MainWindow::action_moveToNew ] );
    tabMenu->addMenu( tabs_moveToWinodwMenu );

    mainToolBar = addToolBar("File");
    mainToolBar->layout()->setMargin(0);
    mainToolBar->setIconSize( QSize(16,16) );
    mainToolBar->addAction( Actions[ MainWindow::action_new ] );
    mainToolBar->addAction( Actions[ MainWindow::action_open ] );
    mainToolBar->addSeparator();
    mainToolBar->addAction( Actions[ MainWindow::action_save ] );
    mainToolBar->addAction( Actions[ MainWindow::action_saveAs ] );
    mainToolBar->addSeparator();
    mainToolBar->addAction( Actions[ MainWindow::action_undo ] );
    mainToolBar->addAction( Actions[ MainWindow::action_redo ] );
    mainToolBar->addSeparator();
    mainToolBar->addAction( Actions[ MainWindow::action_copy ] );
    mainToolBar->addAction( Actions[ MainWindow::action_cut ] );
    mainToolBar->addAction( Actions[ MainWindow::action_paste ] );

    //Connections
    connect(tabs_moveToWinodwMenu, SIGNAL(aboutToShow()), this, SLOT( tabs_moveToWindowAboutToShow()));
    connect(file_recentMenu, SIGNAL(aboutToShow()), this, SLOT( file_recentAboutToShow()) );
    connect(view_languageMenu, SIGNAL(aboutToShow()), this, SLOT( view_languageAboutToShow()) );
    connect(view_windowsMenu, SIGNAL(aboutToShow()), this, SLOT( view_windowsAboutToShow()) );

    statusBar()->showMessage("Ready", 9999);
    show();
    //check args here
    //qDebug() << QApplication::argv[0];
    /*for( int i = 1 ; i < QApplication::argc() ; i++ ){
        qDebug() << QApplication::argv()[ i ] ;
        if ( QFileInfo( QApplication::argv()[ i ] ).exists() ) {
            file_open( QApplication::argv()[ i ] );
        }
    }*/
    if( !selected_tab_control->count() ){
        file_new();
    }
    default_layout="2";
    if( default_layout != "1" ){
        //read layout
        QStringList rows = default_layout.split('|');
        foreach( const QString &row , rows ){

        }
        for( int i=0; i< rows.count(); i++ ){
            if( i ){
                layout_addRow();
            }
            if(  rows.at(i).isEmpty() ){
                continue;
            }
            for( int c = 1; c< rows[i].toInt(); c++ ){
                layout_addCol();
            }
        }
    }


    //qDebug() << "exists " << QFile::exists("toolbars/test.json");
    QDir toolbars_dir("toolbars/");
    if (!toolbars_dir.exists()) {
        toolbars_dir.mkpath(".");
    }
    QFileInfoList  toolbars_files = toolbars_dir.entryInfoList(  QStringList( "*.json" ) );// ,QDir::Files);

    for( int i = 0 ; i< toolbars_files.count() ; i++){
        new Toolbar( toolbars_files.at(i).absoluteFilePath() );
    }

    this->setWindowIcon( *iconpack::instance()->get_icon( iconpack::icon_new ) );

    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::InExpo);
    animation->start();
}

void MainWindow::file_new(){
    //qDebug() << "NEW " << selected_tab_control;
    if( !selected_tab_control ){
        selected_tab_control = tab_widget_0;
    }
    //qDebug() << "NEW " << selected_tab_control << (selected_tab_control == tab_widget_0);

    const QString tab_text =  QString("Doc %1").arg( document_index+1 );
    selected_tab_control -> addTab( dynamic_cast<QWidget*>( IDocument::createByType(0 ,&tab_text, document_index++, selected_tab_control )  ) , tab_text );

    connect(dynamic_cast<QWidget*>(selected_tab), SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(show_editor_contextMenu(const QPoint&)));
    dynamic_cast<QWidget*>(selected_tab)->setFocus();
}
void MainWindow::file_open(){
    QStringList fileNames = QFileDialog::getOpenFileNames(this,"Open files");
    //if ( !fileNames.isEmpty() ){
    //for( int i=0;i<fileNames.length() ;i++){
      //  qDebug()<< fileNames.at(i);
       // file_open( fileNames.at(i) );
//}
    foreach( const QString &fileName, fileNames  ){
            file_open( fileName );
            qDebug() <<fileName;
    }
    //}
}
void MainWindow::file_open( QString fileName ){
    if( !selected_tab ){
        file_new();
    }
    IDocument* doc = dynamic_cast<IDocument*>(selected_tab);
    if( !doc ){
        file_new();
    }
    if( !dynamic_cast<IDocument*>(selected_tab)->get_available() ){
        file_new();
    }
    int index = recent_documents.indexOf( fileName );
    if( index > 0 ){
        recent_documents.removeAt( index );
    }
    if( index != 0){
        recent_documents.push_front( fileName );
    }
    while ( recent_documents.size() > recent_documents_max ){
        recent_documents.removeLast();
    }
    dynamic_cast<IDocument*>(selected_tab)->editor_open( fileName );
}
void MainWindow::file_recent_clear(){
    recent_documents.clear();
}
bool MainWindow::file_save(){
    IDocument *doc = dynamic_cast<IDocument*>(selected_tab);
    if( !selected_tab ){
        return false;
    }
    if( doc->get_path() == QString::null ){
        return file_saveAs();
    }else{
        doc ->editor_save();
        return true;
    }
}

bool MainWindow::file_saveAs(){
    IDocument *doc = dynamic_cast<IDocument*>(selected_tab);
    if( !doc ){
        return false;
    }
    QFileDialog *dialog = new QFileDialog( this, "Save file");
    //dialog->se
    QString fileName = dialog->getSaveFileName();
    if( !fileName.isEmpty() ){
        doc->editor_saveAs(fileName);
        return true;
    }
    delete dialog;
    return false;
}

bool MainWindow::file_close( bool openNew  ){
    if( !selected_tab || !selected_tab_control ){
        change_selected_tab( 0 );
        return openNew;
    }

    bool value = false;
    bool is_external = ( !selected_tab_control->parent()->parent()->parent() );
    IDocument *doc = dynamic_cast<IDocument*>(selected_tab);
    QSplitter*  splitter = qobject_cast<QSplitter*>( selected_tab_control->parent() );
    TabWidgetX * temp_selected_tab_control;

    if( doc->get_available() || doc->get_saved() ){
        doc->editor_clear();
        temp_selected_tab_control = ( selected_tab_control == tab_widget_0 || selected_tab_control->count() >= 2 ? 0 : selected_tab_control ) ;
        delete selected_tab;

        if( !is_external && temp_selected_tab_control ){
            delete temp_selected_tab_control;
            temp_selected_tab_control = 0;
            if( splitter && splitter != tab_widget_0->parent() && !splitter->count() ){
                delete splitter;
                splitter = 0;
            }
            change_selected_tab( 0 );
            return true;
        }
        value = true;
    }else{
        QMessageBox msgBox;
        msgBox.setText( QString("The document %1 has been modified.").arg( doc->getTabText() ));
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);

        switch ( msgBox.exec() ) {
           case QMessageBox::Save:
               if ( file_save() ){
                   doc->editor_clear();

                   temp_selected_tab_control = ( selected_tab_control == tab_widget_0 || selected_tab_control->count() >= 2 ? 0 : selected_tab_control ) ;
                   delete selected_tab;

                   if( !is_external && temp_selected_tab_control ){
                       delete temp_selected_tab_control;
                       temp_selected_tab_control = 0;
                       if( splitter && splitter != tab_widget_0->parent() && !splitter->count() ){
                           delete splitter;
                           splitter = 0;
                       }
                       change_selected_tab( 0 );
                       return true;
                   }

                   value = true;
               }
               break;
           case QMessageBox::Discard:
               doc->editor_clear();

               temp_selected_tab_control = ( selected_tab_control == tab_widget_0 || selected_tab_control->count() >= 2 ? 0 : selected_tab_control ) ;
               delete selected_tab;

               if( !is_external && temp_selected_tab_control ){
                   delete temp_selected_tab_control;
                   temp_selected_tab_control = 0;
                   if( splitter && splitter != tab_widget_0->parent() && !splitter->count() ){
                       delete splitter;
                       splitter = 0;
                   }
                   change_selected_tab( 0 );
                   return true;
               }

               value = true;

               break;
           case QMessageBox::Cancel:
               return false;
         }

    }

    if( openNew && selected_tab_control && !selected_tab_control->count() && (  selected_tab_control == tab_widget_0  || is_external ) ){
        file_new();
    }

    if( !selected_tab_control || !selected_tab ){
        change_selected_tab( 0 );
    }
    return value;

}
void MainWindow::file_print(){ 

}
void MainWindow::file_printPreview(){

}
void MainWindow::file_pageSetup(){}

void MainWindow::edit_copy(){
    dynamic_cast<IDocument*>(selected_tab)->editor_copy();
}
void MainWindow::edit_cut(){
    dynamic_cast<IDocument*>(selected_tab)->editor_cut();
}
/*
void MainWindow::edit_copy_available(  bool value ){
    Actions[ action_copy ]->setEnabled( value );
    Actions[ action_cut ]->setEnabled( value );
}*/
void MainWindow::edit_paste(){
    dynamic_cast<IDocument*>(selected_tab)->editor_paste();
}
/*void MainWindow::edit_paste_available(  bool value ){
    Actions[ action_paste ]->setEnabled( value );
}*/
void MainWindow::edit_selectAll(){
    dynamic_cast<IDocument*>(selected_tab)->editor_selectAll();
}
void MainWindow::edit_undo(){
    dynamic_cast<IDocument*>(selected_tab)->editor_undo();
}
void MainWindow::edit_redo(){
    dynamic_cast<IDocument*>(selected_tab)->editor_redo();
}
/*
void MainWindow::edit_undo_available( bool value ){
    Actions[ action_undo ]->setEnabled( value );
}
void MainWindow::edit_redo_available( bool value ){
    Actions[ action_redo ]->setEnabled( value );
}*/

void MainWindow::edit_find(){
    //if ( !findReplace_dialog ){
        findReplace_dialog = new findReplace();
        editor_panel->addWidget( findReplace_dialog );
    //}
    findReplace_dialog->setVisible( true );
    /*
    QWidget* box = new QWidget();

   // QSize size(,40);
    //box->setMinimumSize(size);
    box->setMaximumHeight(40);
    box->setSizePolicy(QSizePolicy(QSizePolicy::Ignored,QSizePolicy::Maximum));

    //box->setMaximumHeight( 35 );
    QHBoxLayout *lay = new QHBoxLayout();

    lay->setMargin(0);
    //lay->setSizeConstraint();
    QPushButton *q = new QPushButton("DAS");
    q->setMaximumSize( 50 , 25 );
    q->setMinimumSize( 50 , 25 );
    q->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    lay->addWidget( q );
    lay->addWidget( new QPushButton("DAS2"));
    box->setLayout( lay );
    editor_panel->setMinimumHeight( 30 );
    editor_panel->addWidget( box );*/
}
void MainWindow::edit_replace(){
}
bool MainWindow::tab_closeAll(){
    bool value = true;
    //Rows

    //Externals

    int size = external_windows.size();
    for( int e = size -1 ; e >= 0 ; e--){
        if( !external_windows[ e ] ){
            continue;
        }
        if ( (ExternalWindow*)(external_windows[ e ])->closeWindow() ){
            //(ExternalWindow*)(external_windows[ e ])->close();
        }else{
            value = false;
        }
        /*TabWidgetX* tabcontrol = ((ExternalWindow*)external_windows[ e ])->tabControl;
        int tabs = tabcontrol->count();

        for( int t = tabs - 1 ; t >= 0 ; t-- ){
            tabcontrol->setCurrentIndex( t );
            ret &= file_close( false );
        }
        if(  tabcontrol->count() == 0 ){
            delete external_windows[ e ];
            external_windows[ e ]
            external_windows[ e ] = 0;
        }*/
    }
    int rows = editor_panel->count();
    //qDebug() << "rows : " << rows;
    //qDebug() << "CLOSE ALL";
    for( int r = rows - 1; r >= 0 ; r-- ){
     //   qDebug() << r;
        QSplitter* row = qobject_cast<QSplitter*>( editor_panel->widget( r ) );
        if( !row ){
            continue;
        }
        //Cols
        int cols = row->count();
        //qDebug() << "cols : " << cols;
        for( int c = cols - 1; c >= 0 ; c-- ){
            if( !qobject_cast<QSplitter*>( editor_panel->widget( r ) ) ){
                break;
            }
           // qDebug() << r << " - " << c;
            //tabs
            TabWidgetX* col = qobject_cast<TabWidgetX*>( row->widget( c ) );
            if( !col ){
                continue;
            }
            int tabs = col->count();
    //        qDebug() << "tabs : " << tabs;
            for( int t = tabs - 1; t >= 0 ; t-- ){
                if( !qobject_cast<QSplitter*>( editor_panel->widget( r ) ) || !qobject_cast<TabWidgetX*>( row->widget( c ) ) ){
                    break;
                }
                //qDebug() << "R" << r << " C " << c << " T " << t;
                //qDebug() << ((TabWidgetX*)( (QSplitter*)(editor_panel->widget( r ) ) ->widget( c ))) ->setCurrentIndex( t );
                //((TabWidgetX*)(((QSplitter*)(editor_panel->widget( r ) )) ->widget( c )))->setCurrentIndex( t );
                //((TabWidgetX*)  row->widget( c ) )->setCurrentIndex( t );

                //col ->setCurrentIndex( t );
                change_selected_tab( col->widget( t ) );

                value &= file_close( false );
                if( !value  ){
                    return value;
                }
                //qDebug() << "row";
                if( !qobject_cast<QSplitter*>( editor_panel->widget( r ) ) || !qobject_cast<TabWidgetX*>( row->widget( c ) ) ){
                    break;
                }
                /*qDebug() << row;
                qDebug() << "COL";
                qDebug() << col;
                qDebug() << qobject_cast<TabWidgetX*>( row->widget( c ) );
                if( !col ){
                    break;
                }*/
            }
            /*if( !col ){
                break;
            }
            qDebug() << "REACH";
            qDebug() << col;
            if ( col && !col->count() && col != tab_widget_0 ){
                qDebug() << "DELETE COL";
                //row->widget( c )->hide();
                col->hide();
                delete row->widget( c );
            }*/
        }
        /*if( !row->count() && row != editor_row_0 ){
            row->hide();
            delete editor_panel->widget( r );
        }*/
    }
    return value;
}
void MainWindow::tab_closeOthers(){
    //TODO
    QWidget* seleted = selected_tab;

    int rows = editor_panel->count();
    for( int r = rows - 1; r >= 0 ; r-- ){
        //Cols
        int cols = ( (QSplitter*)editor_panel->widget( r ) )->count();

        for( int c = cols - 1; c >= 0 ; c-- ){

            int tabs = ((TabWidgetX*)( ((QSplitter*)editor_panel->widget( r ) )->widget(c) ))->count();
            for( int t = tabs - 1; t >= 0 ; t-- ){
                if( seleted !=  ((TabWidgetX*)( ((QSplitter*)editor_panel->widget( r ))->widget( c ) ))->widget( t ) ){
                    ((TabWidgetX*)( ((QSplitter*)editor_panel->widget( r ))->widget( c ) ))->setCurrentIndex( t );
                    file_close();
                }
            }
        }
    }
}

void MainWindow::tab_next(){
    if( selected_tab_control && selected_tab  ){
        int index = selected_tab_control->currentIndex();
        if( selected_tab_control->count() > index ){
            qDebug() << index+1 << "count" <<  selected_tab_control->count();
            //selected_tab = selected_tab_control->widget( index+1 );
            //selected_tab->setFocus();
            selected_tab_control->setCurrentIndex( index + 1 );
        }
    }
}
void MainWindow::tab_previous(){
    if( selected_tab_control && selected_tab  ){
        int index = selected_tab_control->currentIndex();
        if( index > 0 ){
            selected_tab_control->setCurrentIndex( index - 1 );
        }
    }
}
void MainWindow::tab_moveToNew(){
    if( !selected_tab_control ){
        return;
    }
    TabWidgetX *preSelected  = selected_tab_control;
    //int PreIndex = selected_tab_control->indexOf( selected_tab );
    bool pre_selected_saved =  dynamic_cast<IDocument*>(selected_tab)->get_saved();
    int index = external_windows.size();
    ExternalWindow *newWindow = new ExternalWindow( this );
    external_windows.push_back( newWindow );
    external_windows[ index ]->tabControl->addTab( selected_tab, dynamic_cast<IDocument*>(selected_tab)->getTabText() );

    //preSelected->removeTab(  PreIndex );
    external_windows[ index ]->show();
    if( !preSelected->count() ){
        selected_tab_control =  preSelected;
        file_new();
    }
    dynamic_cast<IDocument*>( external_windows[ index ]->tabControl->widget( 0 )) -> reconnect( external_windows[ index ]->tabControl, pre_selected_saved );

}
void MainWindow::tab_browser_folder(){
    IDocument *doc = dynamic_cast<IDocument*>(selected_tab);
    if ( doc->get_saved() ){
        QString path = QDir::toNativeSeparators( QFileInfo( doc->get_path() ).absolutePath() ); ///QApplication::applicationDirPath());
        QDesktopServices::openUrl(QUrl("file:///" + path));
    }

}
void MainWindow::view_console(){
    if ( !console ){
        console = new Console( this );
    }
    if( !console->isVisible() ){
        console->show();
    }else{
        console->hide();
    }
}

void MainWindow::tools_settings(){
    SettingsDialog *d = new SettingsDialog( );
    d->show();
}
void MainWindow::help_help(){
    QDesktopServices::openUrl( QUrl("http://notepad-x.sourceforge.net/help") );
}
void MainWindow::help_about(){
    AboutDialog *d = new AboutDialog( );
    d->show();
}
void MainWindow::help_website(){
    QDesktopServices::openUrl( QUrl("http://notepad-x.sourceforge.net") );
}
void MainWindow::help_donate(){
    QDesktopServices::openUrl( QUrl("https://sourceforge.net/project/project_donations.php?group_id=202614") );
}
void MainWindow::help_bugReport(){}
void MainWindow::help_featureRequest(){}

void MainWindow::file_recent_open(){
    QAction *action = qobject_cast<QAction *>(sender());
    if( QFileInfo( action->data().toString() ).exists() ){
        file_open( action->data().toString() );
    }
}
void MainWindow::file_templateOpen(){
    QAction *action = qobject_cast<QAction *>(sender());
    templateDocument *t = templates[ action->data().toInt() ];
    qDebug() << t->getName();
    if( QFileInfo( t->getFilePath() ).exists() ){
        file_open( t->getFilePath() );
        dynamic_cast<IDocument*>(selected_tab)->set_path( QString::null );
        //NOW RENAME FILE
        //CLEAR PATH
        //CLEAR SAVED
    }else{
        qDebug()<<"FILE NOT FOUND";
    }
}

void MainWindow::writeSettings()
 {
     QSettings settings("NohponeX", "Notepad X");
     settings.setValue("maximized", isMaximized() );
     if( isMaximized() ){
         showNormal();
     }
     settings.setValue( "default_layout", default_layout );
     settings.setValue("position", pos());
     settings.setValue("size", size());
     for( int a = 0 ; a < MainWindow::action_about ; a++ ){
         if( Actions[ a ] ->shortcuts().count() ){
             settings.setValue("shortcut_" + a, Actions[ a ] ->shortcuts()[0].toString() );
         }
     }
     settings.setValue("recent_documents", recent_documents );

 }

MainWindow::~MainWindow()
{
    delete main_panel;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if( tab_closeAll() ){
        writeSettings();
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::show_editor_contextMenu(const QPoint& point)
{
    editor_contextMenu->exec( dynamic_cast<QAbstractScrollArea*>(selected_tab)->viewport()->mapToGlobal(point) );
}
void MainWindow::show_tabs_contextMenu(const QPoint& point)
{
    selected_tab_control = (TabWidgetX*)sender();
    selected_tab = selected_tab_control->currentWidget();
    qDebug() << point;
    qDebug() << selected_tab;
    qDebug() << "AT" << selected_tab_control->childAt( point );
    //selected_tab_control->tabA
    qDebug() << selected_tab_control->indexOf( selected_tab_control->childAt( point ) );

    tabs_contextMenu->exec( QCursor::pos() );
}
void MainWindow::set_selected_tab( ){
    change_selected_tab( (QWidget*)sender() );
    /*
    qDebug() << "WTF";
    if( sender() != selected_tab ){
        selected_tab = (QWidget*)sender();
        qDebug()<< dynamic_cast<IDocument*>(selected_tab)->parent_control;
        selected_tab_control = (TabWidgetX*)dynamic_cast<IDocument*>(selected_tab)->parent_control;
        //emit changed
    }*/
}
void MainWindow::change_selected_tab( QWidget* control ){

    if( !control && tab_widget_0->count() ){
        change_selected_tab( tab_widget_0->widget( 0 ) );
        return;
    }else if(!control && !tab_widget_0->count() ){
        //qDebug() << "selected_tab_control=tab_widget_0";
        selected_tab_control = tab_widget_0;
        file_new();
        return;
    }
    if( control != selected_tab ){
        //qDebug() << "change_selected_tab";
        selected_tab = control;
        if( selected_tab ){
            setWindowTitle( QString( "%1 | Notepad X").arg(  dynamic_cast<IDocument*>(selected_tab)->getTabText() ) );
            selected_tab_control = (TabWidgetX*)dynamic_cast<IDocument*>(selected_tab)->parent_control;
            if ( !validDocumentActions->isEnabled() ){
                validDocumentActions->setEnabled( true );
            }
            qDebug() << selected_tab_control->count() << selected_tab_control->currentIndex();
            Actions[ MainWindow::action_next ]->setEnabled( ( selected_tab_control->count() > selected_tab_control->currentIndex() + 1 ) );
            Actions[ MainWindow::action_previous ]->setEnabled( ( selected_tab_control->currentIndex() > 0 ) );

            selected_tab_control->setFocus();
            selected_tab->setFocus();
            if( selected_tab_control->currentIndex() != selected_tab_control->indexOf( selected_tab ) ){
                selected_tab_control->setCurrentIndex( selected_tab_control->indexOf(  selected_tab ) );
            }
        /*}else{ Never reach
            setWindowTitle( "Notepad X");
            if ( validDocumentActions->isEnabled() ){
                validDocumentActions->setDisabled( true );
            }*/
        }
    }
    //qDebug() << QApplication::focusWidget();
    //QApplication::focusWidget()!= selected_tab;
    //selected_tab->setFocus();
}
QString MainWindow::current_layout(){
    QString value = "";
    for(  int r = 0 ; r<  editor_panel->count() ; r++ ){
        QSplitter* currentRow = qobject_cast<QSplitter*>( editor_panel->widget( r ) );
        if( !currentRow ){
            continue;
        }
        value.append( QString::number( currentRow->count()) + "|" );
    };
    if( value.endsWith( "|" )){
        return value.left( value.length() -1  );
    }
    return value;
}

//Layout
void MainWindow::layout_addRow(){
    QSplitter *newRow = new QSplitter( Qt::Horizontal );
    TabWidgetX *newTabWidget = new TabWidgetX( );
    newRow->addWidget( newTabWidget );
    editor_panel -> addWidget( newRow );

    selected_tab_control = newTabWidget;
    file_new();
}
void MainWindow::layout_default(){
    //OR DO close all with open new to false and keep default layout true
    //then check layout if not equal to default fix it
    for( int r = editor_panel->count() -1 ; r >= 0  ;r-- ){
        QSplitter* currentRow = qobject_cast<QSplitter*>( editor_panel->widget( r ) );
        if( !currentRow ){
            continue;
        }
        //qDebug() << currentRow;

/*        if( editor_panel->widget(i)->metaObject()->className() != QSplitter::staticMetaObject.className() ){
            continue;
        }*/

        int count = currentRow->count();
        for( int c = count -1 ; c >= 0  ; c-- ){
            if( r != 0 ||  ( r==0 && c != 0 ) ){
                //qDebug()<< "COL" << currentRow->widget( c );
                currentRow->widget( c )->hide();
                delete currentRow->widget( c );
            }
        }
        if( currentRow != editor_row_0 ){
            currentRow->hide();
            delete editor_panel->widget( r );
        }
    }
    change_selected_tab( 0 );
    //selected_tab_control = tab_widget_0;
}

void MainWindow::layout_addCol() {
    qDebug() << "add col";
    if( !selected_tab_control ){
        layout_addCol(0);
    }else{
        for( int r=0 ;r< editor_panel->count() ;r++ ){
            QSplitter* currentRow = qobject_cast<QSplitter*>( editor_panel->widget( r ) );
            if( !currentRow ){
                continue;
            }
            for( int c = 0; c < currentRow->count() ; c++ ){
                if( selected_tab_control == currentRow->widget(c)){
                    layout_addCol( r );
                    return;
               }
            }
        }
    }
}

void MainWindow::layout_addCol( int row ){
     TabWidgetX *newTabWidget = new TabWidgetX( );

     ( (QSplitter*)editor_panel->widget( row ) )->addWidget( newTabWidget );
     selected_tab_control = newTabWidget;
     file_new();
     statusBar()->showMessage("New", 9999);
}
void MainWindow::file_templatesAboutToShow(){
    //NEEDED ??
}
void MainWindow::view_languageAboutToShow(){

}
void MainWindow::view_windowsAboutToShow(){
    qDebug() << "view_windowsAboutToShow";
    view_windowsMenu->clear();
    int size =  external_windows.size();

    QAction *newWindow = new QAction( *iconpack::instance()->get_icon( iconpack::icon_window ) , "Main" ,view_windowsMenu );
    newWindow->setData( -1 );
    view_windowsMenu->addAction( newWindow );
    //view_windows->addAction( new );
    view_windowsMenu->addSeparator();
    for( int i = 0 ; i < size ; i++ ){
        QAction * newWindow = new QAction( *iconpack::instance()->get_icon( iconpack::icon_window ) , "Window" + QString("%1").arg(i),view_windowsMenu );
        newWindow->setData( i );
        view_windowsMenu->addAction( newWindow );

        //connect( newWindow, SIGNAL( triggered() ), this, SLOT( file_recent_open() ));
    }

}
void MainWindow::file_recentAboutToShow(){
    file_recentMenu->clear();
    int size =  recent_documents.count();
    //qDebug() << size;
    for( int i = 0 ; i < size ; i++ ){
        QAction *newRecent = new QAction( *iconpack::instance()->get_icon( iconpack::icon_new ) , QFileInfo( recent_documents[i]  ).fileName() ,file_recentMenu );
        newRecent->setData( recent_documents[i] );
        file_recentMenu->addAction( newRecent );

        connect( newRecent, SIGNAL( triggered() ), this, SLOT( file_recent_open() ));
    }
    file_recentMenu->addSeparator();
    file_recentMenu->addAction( Actions[ action_recent_clear ] );
}

void MainWindow::tabs_moveToWindowAboutToShow(){
    tabs_moveToWinodwMenu->clear();
    int size = external_windows.size();
    QAction *mainWindow  = new QAction( *iconpack::instance()->get_icon( iconpack::icon_moveToWindow ), "MAIN", tabs_moveToWinodwMenu );
    connect(mainWindow, SIGNAL(triggered()), this, SLOT(tabs_moveToWindow()));
    mainWindow->setData( -1 );
    mainWindow->setEnabled( true );
    if( selected_tab_control->parent()->parent() && selected_tab_control->parent()->parent()->parent() && selected_tab_control->parent()->parent()->parent()->parent() && selected_tab_control->parent()->parent()->parent()->parent() == this ){
        mainWindow->setEnabled( false );
    }
    tabs_moveToWinodwMenu->addAction( mainWindow );
    tabs_moveToWinodwMenu->addSeparator();
    for(int i = 0 ; i<size ; i++){
        if( !external_windows[ i ] ){
            continue;
        }
        QAction *newExternal = new QAction( *iconpack::instance()->get_icon( iconpack::icon_moveToWindow ) , QString("Menu %1").arg( i ) ,tabs_moveToWinodwMenu );
        newExternal->setData( i );
        connect(newExternal, SIGNAL(triggered()), this, SLOT(tabs_moveToWindow()));
        tabs_moveToWinodwMenu ->addAction( newExternal  );
    }
}
void MainWindow::tabs_moveToWindow(){
    QAction *action = qobject_cast<QAction *>(sender());
    int index = action->data().toInt();

    if( index == -1 ){//TODO MOVE TO MAIN

        TabWidgetX *preSelected  = selected_tab_control;
        bool pre_selected_saved =  dynamic_cast<IDocument*>(selected_tab)->get_saved();
        if( selected_tab_control->parent()->parent() && selected_tab_control->parent()->parent()->parent() && selected_tab_control->parent()->parent()->parent()->parent() && selected_tab_control->parent()->parent()->parent()->parent() == this ){ // New to new not allowed
            return;
        }
        int newIndex = tab_widget_0->count();
        tab_widget_0->addTab( selected_tab  , dynamic_cast<IDocument*>(selected_tab)->getTabText()  );
        dynamic_cast<IDocument*>( tab_widget_0->widget( newIndex ) ) -> reconnect( tab_widget_0,pre_selected_saved );

        if( preSelected->count() == 0 ){
            ((ExternalWindow*)preSelected->parent())->close();
        }
    }else if( index < 0 || index+1 > external_windows.size() ){

    }else{

        TabWidgetX *preSelected  = selected_tab_control;
        bool pre_selected_saved =  dynamic_cast<IDocument*>(selected_tab)->get_saved();
        int newIndex = external_windows[ index ]->tabControl->count();

        external_windows[ index ]->tabControl->addTab( selected_tab  , dynamic_cast<IDocument*>(selected_tab)->getTabText() );
        dynamic_cast<IDocument*>( external_windows[ index ]->tabControl->widget( newIndex ) ) -> reconnect( external_windows[ index ]->tabControl,pre_selected_saved );

        external_windows[ index ]->show();

        if( !preSelected->count() ){
            selected_tab_control =  preSelected;
            file_new();
        }
    }
}


void MainWindow::dropEvent(QDropEvent* event)
{
    /*const QMimeData* mimeData = event->mimeData();

    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
        QStringList pathList;
        QList<QUrl> urlList = mimeData->urls();

        // extract the local paths of the files
        for (int i = 0; i < urlList.size() && i < 32; ++i)
        {
        //    pathList.append(urlList.at(i).toLocalFile());
            qDebug() << urlList.at(i).toLocalFile();
            file_open( urlList.at(i).toLocalFile() );
        }
        // call a function to open the files
        //openFiles(pathList);
    }*/
}
void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}


void MainWindow::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

