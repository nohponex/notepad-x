#ifndef JSON_H
#define JSON_H

#include <QString>
#include <QHash>
#include <QVector>

#include <QDebug>
class json_Object;
class json_Array;
class json_Element;

class json
{
private:
    static json_Object* parseObject( const QString &data );
    static json_Array* parseArray( const QString &data );
   // json_Element* parseElement( const QString &data );

    static int findEnd( const QChar &char_open , const QChar &char_close, const QString &string );
    static int findEndOfElement( const QString &data );

public:
    json();
    ~json();
    static json_Object* parse( const QString &fileName );

};


class json_IObject{
protected:
    int type;
public:
    json_IObject(){}
    int get_type(){ return type;}
    enum types { element = 0 , object , array };

    json_Object* toObject(){
        return (json_Object*)this;
    }
    json_Array* toArray(){
        return (json_Array*)this;
    }
    json_Element* toElement(){
        return (json_Element*)this;
    }
};

class json_Object : public json_IObject{
private:
    QHash<QString, json_IObject*> _elements;
public:
    json_Object(){
        type = json_IObject::object;
    }
    ~json_Object(){
        _elements.clear();
    }
    void add(const QString &key, json_IObject* element ){
        _elements[ key ] = element;
    }
    bool contains( const QString &key ){
        return _elements.contains( key );
    }
    int count(){
        return _elements.count();
    }
    QHash<QString, json_IObject*> elements(){
        return _elements;
    }
    json_IObject* element( const QString &key ){
        return _elements [key ];
    }
};

class json_Element : public json_IObject{
protected:
    int element_type;
    QString _value;
public:
    json_Element( const QString &value ){
        type = json_IObject::element;
         _value = value;
    }
    enum element_types { element_string, element_int, element_float };
    QString value(){
        return _value;
    }
    int get_element_type() { return element_type; }

    QString toString(){
       return _value;
    }
    bool isInt(){
        bool ok;
        _value.toInt( &ok );
        return ok;
    }
    bool isFloat(){
        bool ok;
        _value.toFloat( &ok );
        return ok;
    }

    int toInt(){
        return _value.toInt();
    }
    float toFloat(){
        return _value.toFloat();
    }
};

/*
class json_ElementString : public json_Element{
private:
    QString _value;
public:
    json_ElementString( const QString &value ){
        _value = value;
        element_type = json_Element::element_string;
    }
    QString value(){
        return _value;
    }
};

class json_ElementInt : public json_Element{
private:
    int _value;
public:
    json_ElementInt( int value ){
        _value = value;
        element_type = json_Element::element_int;
    }
    int value(){
        return _value;
    }
};


class json_ElementFloat : public json_Element{
private:
    float _value;
public:
    json_ElementFloat( float value ){
        _value = value;
        element_type = json_Element::element_float;
    }
    float value(){
        return _value;
    }
};*/

class json_Array: public json_IObject{
private:
    QVector<json_IObject*> _elements;
public:
    json_Array( ){
        type = json_IObject::array;
    }
    ~json_Array(){
        _elements.clear();
    }
    void add(json_IObject* element ){
        _elements.push_back( element );
    }
    int count(){
        return _elements.count();
    }
    QVector<json_IObject*> elements(){
        return _elements;
    }
    json_IObject* element( const int index ){
        return _elements[ index ];
    }
};


#endif // JSON_H
