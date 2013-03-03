#ifndef DOCUMENTTYPES_H
#define DOCUMENTTYPES_H

#include <QString>
#include <QtWidgets/QWidget>
#include <QDebug>

class DocumentTypes
{
protected:
    DocumentTypes(const QString &my_type_id );
public:
     static int types_count;

     static DocumentTypes ** types;
     QString type_id;

    virtual QString get_type_id() = 0;
    virtual DocumentTypes* create_document(int id) = 0;
    DocumentTypes(){}

    static void print(){
        for( int i =0 ; i < types_count ; i++ ){
            qDebug() << "type" << types[i]->get_type_id();
        }
    }
};

#endif // DOCUMENTTYPES_H
