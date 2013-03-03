#ifndef TEMPLATE_DOCUMENT_H
#define TEMPLATE_DOCUMENT_H

#include <QString>

class templateDocument
{
private:
    QString filepath;
    QString name;
    QString extra;
public:
    templateDocument( const QString &_filepath, const QString &_name, const QString &_extra );

    QString getFilePath();
    QString getName();
    QString getExtra();
};

#endif // TEMPLATE_DOCUMENT_H
