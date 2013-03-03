#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
//#include <QMainWindow>
#include <QDebug>

//#include <Classes/templatedocument.h>
//#include "tabwidget.h"

QT_BEGIN_NAMESPACE
class QSplitter;
class templateDocument;
class QWidget;
class QMenu;
class vector;
class TabWidgetX;
class TabBarX;
class ExternalWindow;
class findReplace;
class QAction;
class QActionGroup;
class Console;
QT_END_NAMESPACE
//delete
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static MainWindow* s_instance;
    void closeEvent(QCloseEvent *event);
    //explicit
    //MainWindow(QWidget *parent);
    int document_index;
    int default_document_type;
    bool show_other_document_types;

    QStringList recent_documents;
    int recent_documents_max;

    std::vector<templateDocument*> templates;
    Console *console;
protected:
    MainWindow();

    void dragEnterEvent(QDragEnterEvent* event);

    /**
     *  this event is called when the mouse moves inside the widgets area during a drag/drop operation
     */
    void dragMoveEvent(QDragMoveEvent* event);

    /**
     *  this event is called when the mouse leaves the widgets area during a drag/drop operation
     */
    void dragLeaveEvent(QDragLeaveEvent* event);

    findReplace *findReplace_dialog;
public:

    static MainWindow *instance();
    ~MainWindow();

    void setup_main_window();

    bool show_toolbar_in_external;
    bool enable_projects;
    QString default_layout;
    std::vector<ExternalWindow*> external_windows;


     QWidget *selected_tab;
     TabWidgetX *selected_tab_control;
     QString current_layout();
     enum ActionTypes{ action_new = 0, action_open, action_recent_clear, action_save, action_saveAs,
                       action_close, action_closeAll, action_closeOthers, action_print, action_printPreview,
                       action_pageSetup, action_exit, action_copy, action_cut, action_paste,
                       action_find, action_replace, action_selectAll, action_undo, action_redo,
                       action_next, action_previous, action_moveToNew, action_browse_folder, action_settings,
                       action_layout_default, action_layout_addRow, action_layout_addCol, action_layout_manage, action_help,
                       action_layout_split, action_layout_splitVertical, action_layout_grid, action_console,action_projectsCreate,
                       action_projectsOpen,
                       action_bugReport, action_featureRequest, action_website, action_donate, action_about };


     QToolBar *mainToolBar;
     QAction *Actions[ action_about +1 ];
    void dropEvent(QDropEvent* event);

    QSplitter *editor_panel;
    TabWidgetX *tab_widget_0;
private:

    //Main Notepad X
    QSplitter *main_panel;


    QSplitter *editor_row_0;


    //Menu
    QMenu *fileMenu;
    QMenu *file_templatesMenu;
    QMenu *file_recentMenu;

    QMenu *editMenu;
    QMenu *tabMenu;
    QMenu *tabs_moveToWinodwMenu;
    QMenu *viewMenu;

    QMenu *view_languageMenu;
    QMenu *view_windowsMenu;
    QMenu *toolsMenu;
    QMenu *projectsMenu;
    QMenu *projects_recentMenu;

    QMenu *layoutMenu;
    QMenu *helpMenu;

    //Context Menu
    QMenu *editor_contextMenu;
    QMenu *tabs_contextMenu;

    QActionGroup *validDocumentActions;

    void writeSettings();
private slots:
    void layout_addCol();
    void layout_addRow();
    void layout_addCol( int row );
    void layout_default();

    void file_templatesAboutToShow();
    void file_recentAboutToShow();
    void tabs_moveToWindowAboutToShow();
    void view_languageAboutToShow();
    void view_windowsAboutToShow();

    void tabs_moveToWindow();
    void file_recent_open();
    void file_templateOpen();
public slots:
    void file_new();
    void file_open();
    void file_open( QString fileName );
    void file_recent_clear();
    bool file_save();
    bool file_saveAs();
    bool file_close( bool openNew = true );
    void file_print();
    void file_printPreview();
    void file_pageSetup();

    void tab_closeOthers();
    bool tab_closeAll();
    void tab_next();
    void tab_previous();
    void tab_moveToNew();
    void tab_browser_folder();

    void edit_copy();
    void edit_cut();
    void edit_paste();
    void edit_selectAll();
    void edit_find();
    void edit_replace();
    void edit_undo();
    void edit_redo();

    void view_console();
    void tools_settings();

    void help_help();
    void help_about();
    void help_website();
    void help_donate();
    void help_bugReport();
    void help_featureRequest();

    void show_editor_contextMenu(const QPoint& point);
    void show_tabs_contextMenu(const QPoint& point);

    void set_selected_tab( );
    void change_selected_tab( QWidget* control );

    /*
    void edit_copy_available( bool value );
    void edit_paste_available( bool value );

    void edit_undo_available( bool value );
    void edit_redo_available( bool value );
    */

    void keyPressEvent(QKeyEvent *e)
    {
         // Do something

         // Otherwise pass to the graphics view
        qDebug()<< e->key() << (  e->key() == Qt::Key_Escape ) ;
    }

};

#endif // MAINWINDOW_H
