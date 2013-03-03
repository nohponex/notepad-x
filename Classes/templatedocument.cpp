#include "templatedocument.h"

#include <QString>
templateDocument::templateDocument(const QString &_filepath, const QString &_name, const QString &_extra)
{
    filepath = _filepath;
    name = _name;
    extra  = _extra;
}

QString templateDocument::getFilePath() { return filepath; }
QString templateDocument::getName() { return name; }
QString templateDocument::getExtra() { return extra; }
