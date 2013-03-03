#include "json.h"

#include <QString>
//#include <QChar>
#include <QFile>
#include <QTextStream>

#include <QStack>
#include <QHash>

#include <QDebug>
json::json()
{

}
json::~json()
{
    //qDebug()<<"DELETE JSON";
}
json_Object* json::parse(const QString &fileName){
    QFile file(fileName);

    //this->setPlainText( in.readAll() );


    //json_Object * test = parseObject(" {\"name\":\"nohponex\", \"obj\" : {\"name\":\"fonis\"} , \"array\" : [ 3,\"dsada2\", 4 ]  }");
    //qDebug() << test->elements().count();
    //qDebug() << test->element("array")->toArray()->element(1)->toElement()->toString();
/*
    root->add( "me",  sub );
    json_Element *element = new json_Element( " my value " );
    sub->add( "me",  element );

    //qDebug() << root->element("me")->type;
    if( ((json_Object*)(root->elements()["me"]))->elements()["me"]->type == json_IObject::element ){
        json_Element* test = ((json_Element *)(((json_Object*)root->elements()["me"])->elements()["me"]));
        //qDebug() << test->value();
    }
//    parseObject(" { \"obj\" : {\"name":\"nohponex"} }");

    //qDebug() << ((json_Element*)test->element("name"))->value();

    //qDebug() << test->elements().count();
    //qDebug() << test->element("obj")->type;
    //qDebug() << ((json_Element*)((json_Object*)test->element("obj"))->element("name"))->value();

    //qDebug() << test->element("array")->type;
    //qDebug() << "array count" << ((json_Array*)test->element("array"))->elements().count();
    //qDebug() << ((json_Element*)((json_Array*)test->element("array"))->element(0))->value();
    //qDebug() << ((json_Element*)((json_Array*)test->element("array"))->element(1))->value();
    //qDebug() << test->element("array")->toArray()->element(2)->toElement()->value();
    delete test;
    */
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return 0;
    }
    QTextStream in(&file);
    json_Object *object = parseObject( in.readAll() );
    in.flush();
    file.close();
    return object;
}

json_Object* json::parseObject( const QString &data ){
    json_Object *returnValue = new json_Object();
    //qDebug() << "parsing object " << data;
    QString key("");
    bool key_started = false;
    bool key_set = false;

    bool start_object = false;
    int length = data.length();
    for( int i = 0 ; i < length ; i++ ){
        QChar c = data[ i ];
        //qDebug() << c << " : " << i  << " key : " << key;
        if( c == '"' && !key_started ){
            key = "";
            key_started = true;
        }else if( c== '"' && key_started && !key_set ){
            key_set = true;
            continue;
        }else{
            if( key_started && !key_set){
                key += c;
                continue;
            }

            if( key_set ){
                if( c == ' ' || c == '\t' || c == '\n' || c == '\r' ){
                    continue; //ignore space
                }
                if( c == ':' ){
                    start_object = true;
                    continue;
                }

                if( start_object ){
                    if( c == '{' ){
                        int end = json::findEnd( '{', '}' , data.mid( i + 1 ) );

                        returnValue->add( key,  parseObject( data.mid( i + 1 , end ) ));

                        i += end;
                        key_set = key_started = start_object= false;
                        key = "";
                    }else if( c== '[' ){
                        //array
                        int end = findEnd( '[', ']' , data.mid( i + 1 ) );

                        returnValue->add( key,  parseArray( data.mid( i + 1 , end ) ));

                        i += end;
                        key_set = key_started = start_object = false;
                        key = "";
                    }else{
                        //element
                        if( c == '"' ){
                            i++;
                        }
                        int end = findEndOfElement( data.mid( i ) );
                        //qDebug() << end;
                        //qDebug() << "adding element to object" <<  data.mid( i , end );
                        returnValue->add( key, new json_Element( data.mid( i , end ) ) );
                        //end++;
                        i += end;
                        key_set = false;
                        key_started = false;
                        key = "";

                    }
                }
            }
        }
    }

    return returnValue;

}
json_Array* json::parseArray( const QString &data ){
    json_Array *returnValue = new json_Array();
    int length = data.length();
    for( int i = 0 ; i < length ; i++ ){
        QChar c = data[ i ];
        if( c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == ',' ){
            continue;
        }else if( c == '{' ){
            int end = findEnd( '{', '}' , data.mid( i + 1 ) );
            //qDebug() << "adding object to array" <<  data.mid( i + 1 , end );
            returnValue->add( parseObject( data.mid( i + 1 , end ) ) );
            ++end;
            i += end;
        }else if( c == '[' ){
            int end = findEnd( '[', ']' , data.mid( i + 1 ) );

            returnValue->add( parseArray( data.mid( i + 1 , end ) ) );
            i += end;

        }else{
            //qDebug() << "CHAR IS " << c;
            if( c == '"' ){
                i++;
            }

            int end = findEndOfElement( data.mid( i ) );
            returnValue->add( new json_Element( data.mid( i , end ) ) );
            end++;
            /*
            QString element = data.mid( i , end );

            bool ok = false;
            element.toInt( &ok );
            if( ok ){
                returnValue->add( new json_ElementInt( element.toInt()) );
            }else{
                element.toFloat( &ok );
                if( ok ){
                   returnValue->add( new json_ElementFloat( element.toFloat() ) );
                }else{
                    returnValue->add( new json_ElementString( element ) );
                }
            }*/

            i += end;
        }
    }
    return returnValue;
}
/*
json_Element* json::parseElement( const QString &data ){

}*/

int json::findEnd(const QChar &char_open, const QChar &char_close, const QString &data){
    QStack< QChar > stack;
    //qDebug() << "searching for end ..." << data;
    int length = data.length();
    for( int j = 0 ; j < length ; j++ ){
        if( data[ j ] == char_open ){
            stack.push( char_open );
        }else if(  data[ j ] == char_close ){
            if( stack.isEmpty() ){
                return j;
            }else{
                stack.pop();
            }
        }
    }
    return length;
}

int json::findEndOfElement(const QString &data){
    //qDebug() << "END OF " << data;
    int length = data.length();
    for( int j = 0 ; j < length ; j++ ){
        //qDebug() << j <<  data[ j ] <<  ( data[ j ] == '"' ) ;
        if( data[ j ] == '"' || data[ j ] == ',' || data[ j ] == '}'){
            //qDebug() << "return" << j;
            return j;
        }
    }
    return length;
}
