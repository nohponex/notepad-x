#ifndef DEFAULTDOCUMENT_H
#define DEFAULTDOCUMENT_H

#include <Documents/IDocument.h>
#include <mainwindow.h>
#include <QtWidgets/QWidget>
#include <QObject>
#include <QDebug>
#include <QtWidgets/QTextEdit>
#include <Components/tabwidgetx.h>
#include <QTextCursor>
#include <QString>

#include <QtWidgets/QPlainTextEdit>
#include <QDebug>
#include <QtWidgets/QCompleter>

#include <Components/plaintexteditx.h>
class DefaultDocument : public IDocument ,public PlainTextEditX //QTextEdit
{
private:
    int id;
    //QTextEdit *editor;
    //IDocument
    bool available;
    QString file_path;
    bool saved;

    QString tabText;
    //Completer
    QString textUnderCursor() const;
    QCompleter *c;
public:
    DefaultDocument(){}
    //~DefaultDocument(){}
    DefaultDocument(int i,const QString *tab_text, TabWidgetX* parent = 0 );

    DefaultDocument(const QString &type): IDocument( type ){}

    IDocument* create( int index ,const QString *tab_text, TabWidgetX* parent = 0 ){
        return new DefaultDocument( index , tab_text, parent );
    }
    //Completer
    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

  //  bool eventFilter(QObject* object,QEvent* event);
    //IDocument
    void set_available(){ available = false; saved=false;}
    bool get_available() { return available; }
    int get_id() { return id; }
    bool get_saved() { return saved; }

    QString get_path() { return file_path; }
    void set_path( const QString &path) { saved = false; file_path = path; }
    virtual QString getTabText(){ return tabText; }

    void editor_clear() {}
    void editor_save();
    void editor_saveAs( const QString &fileName );
    void editor_open( const QString &fileName );
    virtual void editor_print(){}
    virtual void editor_printPreview(){}
    virtual void editor_pageSetup(){}

    int get(){ return 1000+id;}


    void setText( const QString &text ){ this->setPlainText(text); }
    //void saveAs( const QString &fileName );

    void editor_copy() { copy(); }
    void editor_cut() { cut(); }
    void editor_paste() { paste(); }
    void editor_selectAll() { selectAll(); }
    void editor_undo() { undo(); }
    void editor_redo() { redo(); }
    void goTo( int line ) { }
    QString editor_selectedText() { return this->textCursor().selectedText(); }
    int editor_selectedIndex() { return this->textCursor().selectionStart(); }
    QString editor_getText(){  return toPlainText(); }
    void editor_insert( const QString &text, int index ) {}
  //  void reconnect(  TabWidgetX* newParent );

    void reconnect( TabWidgetX* newParent, bool saved );


    //QWidget *lineNumberArea;

   // void lineNumberAreaPaintEvent(QPaintEvent *event);
    //int lineNumberAreaWidth();
signals:
    //void editor_text_changed();
    void editor_saved_changed( );
    //QWidget *getWidget() { return (QWidget *)editor; }
    //virtual void focusInEvent( QFocusEvent * e );
public slots:
    void set_changed( );
private slots:
     //void updateLineNumberAreaWidth(int newBlockCount);
     //void highlightCurrentLine();
     //void updateLineNumberArea(const QRect &, int);
    void insertCompletion(const QString &completion);
protected:
    void mouseReleaseEvent(QMouseEvent * event);
    //Completer
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);
   //   void resizeEvent(QResizeEvent *event);

    //DRAG N DROP
    void dropEvent(QDropEvent* event);
    //void dragEnterEvent(QDragEnterEvent* event);

    /**
     *  this event is called when the mouse moves inside the widgets area during a drag/drop operation
     */
    //void dragMoveEvent(QDragMoveEvent* event);

    /**
     *  this event is called when the mouse leaves the widgets area during a drag/drop operation
     */
    //void dragLeaveEvent(QDragLeaveEvent* event);
};

#endif // DEFAULTDOCUMENT_H
