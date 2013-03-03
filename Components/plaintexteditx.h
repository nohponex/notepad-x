#ifndef PLAINTEXTEDITX_H
#define PLAINTEXTEDITX_H

#include <QtWidgets/QPlainTextEdit>
#include <QObject>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class QMouseEvent;

class LineNumberArea;

class PlainTextEditX : public QPlainTextEdit
{
    Q_OBJECT
public:
    PlainTextEditX( );
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

   protected:
       void resizeEvent(QResizeEvent *event);
       void mouseReleaseEvent ( QMouseEvent * event );
   private slots:
       void updateLineNumberAreaWidth(int newBlockCount);
       void highlightCurrentLine();
       void updateLineNumberArea(const QRect &, int);

       //void paintEvent(QPaintEvent *);
   private:
       QWidget *lineNumberArea;
};

#endif // PLAINTEXTEDITX_H
