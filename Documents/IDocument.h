#ifndef IDOCUMENT_H
#define IDOCUMENT_H
#include <QtWidgets/QWidget>
#include <QObject>
#include <QString>
#include <QDebug>
#include <vector>
#include <Components/tabwidgetx.h>

//#include <defaultdocument.h>

class IDocument{

private:
    QString type_name;

protected:
    static std::vector<IDocument*> types;
public:
    IDocument(){}
    //virtual ~IDocument() {}

    IDocument( const QString &type){
        type_name = type;
        types.push_back( this );
    }

    static IDocument* createByType( int  t, const QString *tab_text, int index, TabWidgetX* parent = 0 ){
         return types[ t ]  -> create( index, tab_text, parent );
    }
    static int count() { return types.size(); }
    virtual IDocument* create( int index,const QString *tab_text, TabWidgetX* parent ) = 0;

    TabWidgetX* parent_control;
    //Properties
    virtual bool get_available() = 0;
    virtual void set_available() = 0;
    virtual int get_id() = 0;
    virtual bool get_saved() = 0;
    virtual QString editor_getText() = 0;
    virtual QString getTabText() = 0;

    virtual QString get_path() = 0;
    virtual void set_path( const QString &path ) = 0;

    virtual void editor_clear() = 0;
    virtual void editor_save() = 0;
    virtual void editor_saveAs( const QString &fileName ) = 0;
    virtual void editor_open( const QString &fileName ) = 0;

    virtual void editor_print() = 0;
    virtual void editor_printPreview() = 0;
    virtual void editor_pageSetup() = 0;

    virtual void editor_cut() = 0;
    virtual void editor_copy() = 0;
    virtual void editor_paste() = 0;
    virtual void editor_selectAll() = 0;
    virtual void editor_undo() = 0;
    virtual void editor_redo() = 0;
    virtual void goTo( int line ) = 0;


    virtual QString editor_selectedText() = 0;
    virtual int editor_selectedIndex() = 0;

    virtual void editor_insert( const QString &text, int index ) = 0;
    virtual void reconnect(  TabWidgetX* newParent, bool saved ) = 0;
    //virtual int get () = 0;
    //virtual void print() = 0;

    //virtual void setText( const QString &text ) = 0;
};

//std::vector<IDocument*> IDocument::types;
#endif // IDOCUMENT_H
