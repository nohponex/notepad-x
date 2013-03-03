#include "documenttypes.h"

#include <QString>

DocumentTypes ** DocumentTypes::types;
int DocumentTypes::types_count=0;


DocumentTypes::DocumentTypes(const QString &my_type_id){
    type_id = my_type_id;

    types_count++;

    if( types_count == 1 ){
        types = (DocumentTypes**)malloc(sizeof(DocumentTypes*));
    }else{
        types = (DocumentTypes**)realloc(types, types_count * sizeof(DocumentTypes *));
    }
    types[ types_count -1 ] = this;

}
