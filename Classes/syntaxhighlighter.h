#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QTextDocument>
#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

#include <QSyntaxHighlighter>
#include <QTextDocument>

 #include <QHash>
 #include <QTextCharFormat>

#include <QObject>
 class Highlighter : public QSyntaxHighlighter
 {
     Q_OBJECT
 public:
     Highlighter(QTextDocument *parent = 0);

     //~QSyntaxHighlighter(){}
     //~Highlighter(){}
 protected:
     void highlightBlock(const QString &text);

 private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> highlightingRules;

     QRegExp commentStartExpression;
     QRegExp commentEndExpression;

     QTextCharFormat keywordFormat;
     QTextCharFormat reservedKeywordFormat;
     QTextCharFormat classFormat;
     QTextCharFormat arrayFormat;
     QTextCharFormat singleLineCommentFormat;
     QTextCharFormat multiLineCommentFormat;
     QTextCharFormat quotationCharFormat;
     QTextCharFormat quotationFormat;
     QTextCharFormat functionFormat;

     QTextCharFormat numberFormat;

     //TODO NUMBER
     //TODO VARIABLES LIKE $
     //TODO ARRAY ?? \[.\]
 };
#endif // SYNTAXHIGHLIGHTER_H
