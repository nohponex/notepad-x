#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QtWidgets/QWidget>
#include <Components/plaintexteditx.h>

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(PlainTextEditX *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    PlainTextEditX *codeEditor;
};


#endif // LINENUMBERAREA_H
