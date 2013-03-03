#include "testdocument.h"

#include <Documents/IDocument.h>
#include <QTextEdit>
#include <QFile>
#include <mainwindow.h>
TestDocument::TestDocument( int i, TabWidgetX* parent ) : QTextEdit( 0 ), IDocument()
{
    //setParent( parent );
    parent_control = parent;
    id=i;
    available = true;
    file_path = QString::null;

    QPalette p = palette();
    p.setColor(QPalette::Base, QColor(0, 0, 255));
    setPalette(p);

    connect( this, SIGNAL( textChanged() ) , this, SLOT(set_changed()));

    connect( this, SIGNAL( cursorPositionChanged()) , MainWindow::instance(), SLOT( set_selected_tab() ));
    //connect( this, SIGNAL( cursorPositionChanged()) , MainWindow::instance(), SLOT( set_selected_tab() ));
}

void TestDocument::editor_open( const QString &fileName ){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }
    QTextStream in(&file);
    this->setPlainText( in.readAll() );
    in.flush();
    file.close();
    saved = false; // TODO
    available = false; // TODO
}
void TestDocument::editor_save(){
    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QTextStream out(&file);

    out << this->toPlainText();
    out.flush();
    file.close();
    saved = true;
}
void TestDocument::editor_saveAs(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QTextStream out(&file);

    out << this->toPlainText();
    out.flush();
    file.close();
    saved = true;
}
void TestDocument::set_changed(){
    if( saved ){
        saved = false;
        //emit editor_saved_changed();
    }
}
