#include <Classes/syntaxhighlighter.h>

#include <QTextDocument>
#include <QSyntaxHighlighter>

 #include <QtGui>

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;



    reservedKeywordFormat.setForeground(QColor(250, 120,172 ));
    reservedKeywordFormat.setFontWeight(QFont::Bold);
    QStringList reservedKeywordPatterns;
    reservedKeywordPatterns <<"\\b(alignas|alignof|and|and_eq|asm|auto|bitand|bitor|bool|break|case|catch|char|char16_t|char32_t|class|compl|const|constexpr|const_cast|continue|decltype|default|delete|do|double|dynamic_cast|else	|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|register|reinterpret_cast|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)\\b";

            /*<<"\\balignas \\b"<<"\\balignof\\b"<<"\\band\\b"
                           <<"\\band_eq\\b"
                           <<"\\basm\\b"
                           <<"\\bauto\\b"
                           <<"\\bbitand\\b"
                           <<"\\bbitor\\b"
                           <<"\\bbool\\b"
                           <<"\\bbreak\\b"
                           <<"\\bcase\\b"
                           <<"\\bcatch\\b"
                           <<"\\bchar\\b"
                           <<"\\bchar16_t\\b"
                           <<"\\bchar32_t\\b"
                           <<"\\bclass\\b"
                           <<"\\bcompl\\b"
                           <<"\\bconst\\b"
                           <<"\\bconstexpr\\b"
                           <<"\\bconst_cast\\b"
                           <<"\\bcontinue\\b"
                           <<"\\bdecltype\\b"
                           <<"\\bdefault\\b"
                           <<"\\bdelete\\b"
                           <<"\\bdo\\b"
                           <<"\\bdouble\\b"
                           <<"\\bdynamic_cast\\b"
                           <<"\\belse\\b"
                           <<"\\benum\\b"
                           <<"\\bexplicit\\b"
                           <<"\\bexport\\b"
                           <<"\\bextern\\b"
                           <<"\\bfalse\\b"
                           <<"\\bfloat\\b"
                           <<"\\bfor\\b"
                           <<"\\bfriend\\b"
                           <<"\\bgoto\\b"
                           <<"\\bif\\b"
                           <<"\\binline\\b"
                           <<"\\bint\\b"
                           <<"\\blong\\b"
                           <<"\\bmutable\\b"
                           <<"\\bnamespace\\b"
                           <<"\\bnew\\b"
                           <<"\\bnoexcept\\b"
                           <<"\\bnot\\b"
                           <<"\\bnot_eq\\b"
                           <<"\\bnullptr\\b"
                           <<"\\boperator\\b"
                           <<"\\bor\\b"
                           <<"\\bor_eq\\b"
                           <<"\\bprivate\\b"
                           <<"\\bprotected\\b"
                           <<"\\bpublic\\b"
                           <<"\\bregister\\b"
                           <<"\\breinterpret_cast\\b"
                           <<"\\breturn\\b"
                           <<"\\bshort\\b"
                           <<"\\bsigned\\b"
                           <<"\\bsizeof\\b"
                           <<"\\bstatic\\b"
                           <<"\\bstatic_assert\\b"
                           <<"\\bstatic_cast\\b"
                           <<"\\bstruct\\b"
                           <<"\\bswitch\\b"
                           <<"\\btemplate\\b"
                           <<"\\bthis\\b"
                           <<"\\bthread_local\\b"
                           <<"\\bthrow\\b"
                           <<"\\btrue\\b"
                           <<"\\btry\\b"
                           <<"\\btypedef\\b"
                           <<"\\btypeid\\b"
                           <<"\\btypename\\b"
                           <<"\\bunion\\b"
                           <<"\\bunsigned\\b"
                           <<"\\busing\\b"
                           <<"\\bvirtual\\b"
                           <<"\\bvoid\\b"
                           <<"\\bvolatile\\b"
                           <<"\\bwchar_t\\b"
                           <<"\\bwhile\\b"
                           <<"\\bxor\\b"
                           <<"\\bxor_eq\\b";*/
    foreach (const QString &pattern, reservedKeywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = reservedKeywordFormat;
        highlightingRules.append(rule);
    }
    keywordFormat.setForeground( QColor(236, 105,30 ));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns /*<< "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b"//*/ //<< "\\b#[_a-zA-Z0-9]{1,}\\b"; //<-- preprocessor
            << "(^|\\s|\\n|\\b)#[_a-zA-Z0-9]+\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    arrayFormat.setForeground(  QColor(145, 255,0 ) );
    arrayFormat.setFontItalic( true );
    //rule.pattern = QRegExp(".*\\[[a-z]+\\].*");
    rule.pattern = QRegExp( "\\[(?:[^\\[]|\\.)*\\]" );
    //"\'(?:[^\']|\\.)*\'"
    rule.format = arrayFormat;
    highlightingRules.append(rule);

    numberFormat.setForeground(  QColor(186, 102,209 ) );
    rule.pattern  = QRegExp( "[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?" );// QRegExp("\\b[0-9]+\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    //#\\b[a-z]+\\b"; //<-- preprocessor
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(QColor( 210, 82, 82 ));
    rule.pattern = QRegExp( "\\b[A-Za-z0-9_]+(?=\\.)"); //"\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(QColor( 199,221, 12));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground( QColor( 204,223, 50) );

    quotationCharFormat.setForeground(  QColor(100, 198,0 ));
    rule.pattern = QRegExp( "\'[^\'\\\\]*(?:\\\\.[^\'\\\\]*)*\'"); //"\'(?:[^\']|\\.)*\'");
    rule.format = quotationCharFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(  QColor(255, 198,0 ) );
    /////"([^"\\]*(\\.[^"\\]*)*)"/
    rule.pattern = QRegExp(  "\"[^\"\\\\]*(?:\\\\.[^\"\\\\]*)*\"" );// "\"(?:[^\\\"]+|\\.)*\"" );
    //"\"(?:[^\"]|[^\\\']|\".)*\""); //"\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::cyan);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}
//Highlighter::~Highlighter(){}
void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
