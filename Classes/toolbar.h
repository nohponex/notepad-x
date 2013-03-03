#ifndef TOOLBAR_H
#define TOOLBAR_H

//#include <QToolBar>
#include <QString>
class QToolBar;
class Toolbar
{
protected:
    QString name;
    QString author;
    QString version;


    QToolBar *toolbarControl;
public:
    Toolbar( const QString  &filePath );
};

#endif // TOOLBAR_H
