#include "plaintexteditx.h"
#include <Classes/linenumberarea.h>
#include <QtWidgets/QPlainTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QTextBlock>
#include <QDebug>

#include <QMouseEvent>
#include <Classes/syntaxhighlighter.h>

PlainTextEditX::PlainTextEditX(): QPlainTextEdit(0)
{
     Highlighter* highlighter = new Highlighter( document() );
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int PlainTextEditX::lineNumberAreaWidth()
 {
     int digits = 1;
     int max = qMax(1, blockCount());
     while (max >= 10) {
         max /= 10;
         ++digits;
     }

     int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

     return space;
 }



 void PlainTextEditX::updateLineNumberAreaWidth(int /* newBlockCount */)
 {
     setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
 }



 void PlainTextEditX::updateLineNumberArea(const QRect &rect, int dy)
 {
     if (dy)
         lineNumberArea->scroll(0, dy);
     else
         lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

     if (rect.contains(viewport()->rect()))
         updateLineNumberAreaWidth(0);
 }



 void PlainTextEditX::resizeEvent(QResizeEvent *e)
 {
     QPlainTextEdit::resizeEvent(e);

     QRect cr = contentsRect();
     lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
 }



 void PlainTextEditX::highlightCurrentLine()
 {
     QList<QTextEdit::ExtraSelection> extraSelections;

     if (!isReadOnly()) {
         QTextEdit::ExtraSelection selection;

         QColor lineColor = QColor( 42,42,42,60);
                 //(Qt::yellow).lighter(160);

         selection.format.setBackground(lineColor);
         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
         selection.cursor = textCursor();
         selection.cursor.clearSelection();
         extraSelections.append(selection);
     }

     setExtraSelections(extraSelections);
 }



 void PlainTextEditX::lineNumberAreaPaintEvent(QPaintEvent *event)
 {
     QPainter painter(lineNumberArea);
     painter.fillRect(event->rect(), Qt::lightGray);


     QTextBlock block = firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();

     while (block.isValid() && top <= event->rect().bottom()) {
         if (block.isVisible() && bottom >= event->rect().top()) {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignRight, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
 }
 void PlainTextEditX::mouseReleaseEvent(QMouseEvent * event){
     if (event->button() == Qt::LeftButton &&
     event->modifiers() == Qt::ControlModifier){
         qDebug() << "CONTROL CLICK";
         //this->textCursor().
        QTextCursor cc(this->textCursor());
         //QTextBlockFormat backgroundFormat =   ;
        QColor lineColor = QColor( 132,46,102,160);
         QTextCharFormat *c = new QTextCharFormat();
          c->setBackground( lineColor );

         QTextEdit::ExtraSelection xxx;
         xxx.cursor = this->textCursor();
         xxx.format.setBackground( lineColor );

         QList<QTextEdit::ExtraSelection> extras;
         extras << xxx;
         this->setExtraSelections( extras );

                 //(Qt::yellow).lighter(160);
        //textCursor().sty
        textCursor().setCharFormat( *c );


        //PaintMe( 0 );
          //  update();


          //cc.selection()
        // const QTextCursor t();
        // this->setCursor( t  );
     }
 }


/*
     //}
         QPlainTextEdit::paintEvent(e);

         QPainter painter(this);

         //if(drawShapes)
         //{
             QRectF rectangle(10.0, 20.0, 80.0, 60.0);
             QPen pen(Qt::red);
             int startAngle = 30 * 16;
             int spanAngle = 120 * 16;
             painter.setPen(pen);

             painter.drawArc(rectangle, startAngle, spanAngle);
             */

