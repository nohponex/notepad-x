#ifndef CONSOLE_H
#define CONSOLE_H

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>
class Console : public QFrame
{
    Q_OBJECT
protected:
    QCompleter *completer;
    QLineEdit *edit;
    QStringList word_list;
    void keyPressEvent(QKeyEvent *e);
    void showEvent ( QShowEvent * event );
    bool file_mode;
public:
    Console( QWidget * parent );
protected slots:

    void execute();

};

#endif // CONSOLE_H
