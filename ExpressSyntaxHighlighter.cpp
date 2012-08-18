/*  This file is part of SCView, a STEP-Express viewer based on StepCode
    Copyright (C) 2012 Laurent Bauer lahoraent@hotmail.com

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; version 2
    of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "ExpressSyntaxHighlighter.h"

#include <iostream>
using namespace std;

ExpressSyntaxHighlighter::ExpressSyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(QColor(0,0,128));
    //keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bTYPE\\b" << "\\bEND_TYPE\\b"
                    << "\\bENUMERATION OF\\b"
                    << "\\bSELECT\\b"
                    << "\\bENTITY\\b" << "\\bEND_ENTITY\\b"
                    << "\\bABSTRACT\\b"
                    << "\\bSUBTYPE OF\\b" << "\\bSUPERTYPE\\b" << "\\bONEOF\\b"
                    << "\\bDERIVE\\b"
                    << "\\bOPTIONAL\\b"
                    // << "\\bWHERE\\b" << "\\bEND_RULE\\b"
                       ;
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    primitiveFormat.setForeground(QColor(128,128,0));
    QStringList primitivePatterns;
    // the regexp:
    // starts with a word       \\b
    // that can be              INTEGER|REAL...
    // it is followed           (?=
    // by 0 or 1                ?:
    // ; or whitespace          ;|\\s
    primitivePatterns    << "\\b(INTEGER|REAL|BOOLEAN|LOGICAL|STRING|BINARY|NUMBER)(?=(?:;|\\s))";

    // foreach not YET necessary since there is only one pattern
    // but what will be tomorrow?
    foreach (const QString &pattern, primitivePatterns)
    {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = primitiveFormat;
        highlightingRules.append(rule);
    }
}

void ExpressSyntaxHighlighter::fillTypes(const QStringList &list)
{
    cout << "ExpressSyntaxHighlighter::fillTypes " << list.count() << endl;
    HighlightingRule rule;

    typeFormat.setForeground(QColor(128,0,0));
    QStringList typePatterns;
    int typeCount =list.count();
    for (int i=0; i<typeCount; ++i)
    {
        QString pattern;
        pattern = "(?:\\s|\\(|,)" + list.at(i) + "(?=(?:;|,|\\s|\\)|\\n||\\r))";
        typePatterns << pattern;
    }
    foreach (const QString &pattern, typePatterns)
    {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }
}

void ExpressSyntaxHighlighter::fillEntities(const QStringList &list)
{
    HighlightingRule rule;

    entityFormat.setForeground(QColor(128,0,128));
    QStringList entityPatterns;
    int entityCount =list.count();
    for (int i=0; i<entityCount; ++i)
    {
        QString pattern;
        pattern = "(?:\\s|\\(|,)" + list.at(i) + "(?=(?:;|,|\\s|\\)|\\n||\\r))";
        entityPatterns << pattern;
    }
    foreach (const QString &pattern, entityPatterns)
    {
        rule.pattern = QRegExp(pattern, Qt::CaseInsensitive);
        rule.format = entityFormat;
        highlightingRules.append(rule);
    }
}

void ExpressSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
}
