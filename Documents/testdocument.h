
#ifndef TESTDOCUMENT_H
#define TESTDOCUMENT_H


#include <Documents/IDocument.h>
#include <QWidget>
#include <QObject>
#include <QDebug>
#include <QTextEdit>
//#include <tabbarx.h>
#include <Components/tabwidgetx.h>
#include <QTextCursor>
#include <QString>

#include <QDebug>
class TestDocument:  public IDocument ,public QTextEdit
{
private:
    int id;
    //QTextEdit *editor;
    //IDocument
    bool available;
    QString file_path;
    bool saved;
public:
    TestDocument(){}
    //~DefaultDocument(){}
    TestDocument(int i, TabWidgetX* parent = 0 );

    TestDocument(const QString &type): IDocument( type ){}

    IDocument* create( int index , TabWidgetX* parent = 0 ){
        return new TestDocument( index , parent );
    }
    //IDocument
    void reconnect(  TabWidgetX* newParent ){}
    void set_available(){ available = false; saved=false; }
    bool get_available() { return available; }
    int get_id() { return id; }
    bool get_saved() { return saved; }

    QString get_path() { return file_path; }
    void set_path( const QString &path) { file_path = path; }


    void editor_clear() {}
    void editor_save();
    void editor_saveAs( const QString &fileName );
    void editor_open( const QString &fileName );


    int get(){ return 1000+id;}


    void setText( const QString &text ){ this->setPlainText(text); this->setDocumentTitle("xxx");}
    //void saveAs( const QString &fileName );

    void editor_copy(){ copy(); }
    void editor_cut(){ cut(); }
    void editor_paste(){ paste(); }
    void editor_selectAll() { selectAll(); }
    void editor_undo() { undo(); }
    void editor_redo() { redo(); }
    void goTo( int line ) { }

    QString editor_selectedText() { return this->textCursor().selectedText(); }
    int editor_selectedIndex() { return this->textCursor().selectionStart(); }

    void editor_insert( const QString &text, int index ) {}

signals:
    //void editor_text_changed();
    void editor_saved_changed( );
    //QWidget *getWidget() { return (QWidget *)editor; }
public slots:
    void set_changed( );
};

#endif // TESTDOCUMENT_H
