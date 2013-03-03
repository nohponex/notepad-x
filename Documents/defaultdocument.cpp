#include "defaultdocument.h"

#include <Documents/IDocument.h>
#include <mainwindow.h>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QFile>
#include <mainwindow.h>
#include <QEvent>
#include <Components/tabwidgetx.h>
#include <Classes/linenumberarea.h>
#include <QPainter>
#include <QPaintEvent>

#include <QFileInfo>
#include <Components/plaintexteditx.h>

#include <QtWidgets/QCompleter>


 #include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QScrollBar>
DefaultDocument::DefaultDocument( int i,const QString* tab_text, TabWidgetX* parent ): IDocument(), PlainTextEditX(), c(0) //: QTextEdit( 0 ), IDocument()
{

    //setParent( parent );
    parent_control = parent;
    id=i;
    available = true;
    saved = false;
    file_path = QString::null;
    //tabText =  tab_text; //QString("Tab %1").arg(i);
    tabText.append( tab_text );
    setAcceptDrops( true );

  //  updateLineNumberAreaWidth(0);
  //  highlightCurrentLine();
  //  lineNumberArea = new LineNumberArea(this);


    connect( this  , SIGNAL(textChanged()) , parent_control, SLOT(document_changed()));
    connect( this, SIGNAL( cursorPositionChanged()) , MainWindow::instance(), SLOT( set_selected_tab() ));
   /* connect( this, SIGNAL( undoAvailable(bool) ), MainWindow::instance(), SLOT( edit_undo_available( bool ) ) );
    connect( this, SIGNAL( redoAvailable(bool) ), MainWindow::instance(), SLOT( edit_redo_available( bool ) ) );
    //pasteAvailable(true);
    //this->copyAvailable();
    connect( this, SIGNAL( copyAvailable(bool) ), MainWindow::instance(), SLOT( edit_copy_available( bool ) ) );
    //connect( this, SIGNAL(  (bool) ), MainWindow::instance(), SLOT( edit_paste_available( bool ) ) );
    //connect( this, SIGNAL( cursorPositionChanged()) , MainWindow::instance(), SLOT( change_selected_tab( this )));
    //connect( this, SIGNAL( cursorPositionChanged()) , MainWindow::instance(), SLOT( set_selected_tab() ));
    //connect( this, SIGNAL(focusInEvent(QFocusEvent*)) , MainWindow::instance(), SLOT( set_selected_tab() ));

   // this->installEventFilter( this );
*/
    //this->update();
//    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
//    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
//    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    //todo set ok
    available = true;
    qDebug() << "created";

    QStringList word_list;
    word_list << "alpha" << "omega" << "omicron" << "zeta" << "nohponex" << "/close" << "/new" << "file:";

    QCompleter * completer = new QCompleter(word_list, this);
    completer->setCompletionMode( QCompleter::PopupCompletion );
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    this->setCompleter(completer);
}
void DefaultDocument::reconnect( TabWidgetX* newParent, bool saved ){
    disconnect(parent_control);
    parent_control = newParent;
    this->saved = saved;
    connect( this, SIGNAL( textChanged() ) , parent_control, SLOT(document_changed()));
    if( saved ){
        parent_control->document_saved( true );
    }
}

void DefaultDocument::editor_open( const QString &fileName ){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }
    QTextStream in(&file);
    setPlainText( in.readAll() );
    file_path = fileName;
    tabText  = QFileInfo( fileName ).fileName();
    in.flush();
    file.close();
    saved = true; // TODO
    available = false; // TODO

    parent_control->document_saved( true );
}
void DefaultDocument::editor_save(){
    QFile file(file_path);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QTextStream out(&file);
    //out.setCodec("UTF-8");
    out << toPlainText();
    out.flush();

    file.close();
    saved = true;
    parent_control->document_saved( true );
}
void DefaultDocument::editor_saveAs(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QTextStream out(&file);

    out << this->toPlainText();
    out.flush();
    file_path = fileName;
    tabText  = QFileInfo( fileName ).fileName();
    file.close();
    saved = true;
    parent_control->document_saved( true );
}
void DefaultDocument::set_changed(){
    if( saved ){
        saved = false;
        //emit editor_saved_changed();
    }
}
void DefaultDocument::mouseReleaseEvent(QMouseEvent * event){
    if( MainWindow::instance()->selected_tab != this ){
        MainWindow::instance()->change_selected_tab( this );
    }
    event->accept();
}

/*
bool DefaultDocument::eventFilter(QObject* object,QEvent* event)
{
    qDebug()<< "FILTER" << event->type();
    if(event->type() == QEvent::FocusIn)
    {
        //MainWindow::instance()->set_selected_tab();
  //std::cout <<"Filtered KeyPress Event.."<<std::endl;
        return true;
    }
    else
    {
        return QObject::eventFilter(object,event);
    }
}
*/
void DefaultDocument::setCompleter(QCompleter *completer)
 {
     if (c)
         QObject::disconnect(c, 0, this, 0);

     c = completer;

     if (!c)
         return;

     c->setWidget(this);
     c->setCompletionMode(QCompleter::PopupCompletion);
     c->setCaseSensitivity(Qt::CaseInsensitive);
     QObject::connect(c, SIGNAL(activated(QString)),
                      this, SLOT(insertCompletion(QString)));
 }
QCompleter *DefaultDocument::completer() const
 {
     return c;
 }
void DefaultDocument::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}
QString DefaultDocument::textUnderCursor() const
 {
     QTextCursor tc = textCursor();
     tc.select(QTextCursor::WordUnderCursor);
     return tc.selectedText();
 }
void DefaultDocument::focusInEvent(QFocusEvent *e)
 {
     if (c)
         c->setWidget(this);
     QPlainTextEdit::focusInEvent(e);
 }
void DefaultDocument::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {


       case Qt::Key_Return:
           qDebug() << "XX";
           qDebug() << c->currentCompletion();
           qDebug() << c->currentRow();
           //inser rest of the text
          // c->complete();
           //insertCompletion( c->completionModel()->
            //c->
           qDebug() << c->popup()->currentIndex();
           this->insertPlainText( c->currentCompletion().right( textUnderCursor().length() -1 ) );
           c->setCompletionPrefix("");
           //c->
           return;
       case Qt::Key_Enter:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // dont process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 2
                      || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0)
                + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}
void DefaultDocument::dropEvent(QDropEvent* event)
{
    /*
    const QMimeData* mimeData = event->mimeData();
    qDebug() << "FROM DEFAULT DOCUMENT";
    // check for our needed mime type, here a file or a list of files
    if (mimeData->hasUrls())
    {
       MainWindow::instance()->dropEvent( event );
    }*/
}
