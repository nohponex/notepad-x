#ifndef FINDREPLACE_H
#define FINDREPLACE_H

#include <QtWidgets/QWidget>

/*
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QKeyEvent>
*/
class QLabel;
class QLineEdit;
class QPushButton;
class QToolButton;
class QHBoxLayout;
class QKeyEvent;

class findReplace : public QWidget
{
    Q_OBJECT
protected:
    QLabel *find_label;
    QLabel *replace_label;
    QLineEdit *find_text;
    QLineEdit *replace_text;

    QPushButton *close_button;
    QToolButton *backSearch;
    QPushButton *find_button;
    QPushButton *replace_button;
    QPushButton *replaceAll_button;

    QWidget *find_widget;
    QWidget *replace_widget;
    void keyPressEvent(QKeyEvent *e);
public:
    explicit findReplace(QWidget *parent = 0);

signals:
    
public slots:
    
};

#endif // FINDREPLACE_H
