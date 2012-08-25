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

#include "ExpressTextEdit.h"
#include "ExpressSyntaxHighlighter.h"
#include <ExpDict.h>
#include <QMouseEvent>

ExpressTextEdit::ExpressTextEdit(Registry &registry, QWidget *parent)
    : QTextEdit(parent)
    , m_Registry(registry)
    , m_Highlighter ( new ExpressSyntaxHighlighter(this->document()))
{
    setMouseTracking(true);
}

void ExpressTextEdit::fillHighlighterWithTypes(const QStringList &list)
{
    m_Highlighter->fillTypes(list);
}

void ExpressTextEdit::fillHighlighterWithEntities(const QStringList &list)
{
    m_Highlighter->fillEntities(list);
}

void ExpressTextEdit::mouseMoveEvent(QMouseEvent *e)
{
    QTextCursor cursor = cursorForPosition(e->pos());
    cursor.select(QTextCursor::WordUnderCursor);
    QString wordUnderCursor = cursor.selectedText();

    const EntityDescriptor * entityDescriptor = m_Registry.FindEntity(wordUnderCursor.toAscii());
    const TypeDescriptor * typeDescriptor = m_Registry.FindType(wordUnderCursor.toAscii());
    if (entityDescriptor )
    {
        std::string str;
        setToolTip(entityDescriptor->GenerateExpress(str));
    }
    else if(typeDescriptor)
    {
        std::string str;
        setToolTip(typeDescriptor->GenerateExpress(str));
    }
    else setToolTip(QString());


}

void ExpressTextEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString wordUnderCursor = cursor.selectedText();

    const EntityDescriptor * entityDescriptor = m_Registry.FindEntity(wordUnderCursor.toAscii());
    const TypeDescriptor * typeDescriptor = m_Registry.FindType(wordUnderCursor.toAscii());
    if (entityDescriptor )
        emit entityDoubleClicked(entityDescriptor);
    else if(typeDescriptor)
        emit typeDoubleClicked(typeDescriptor);
}

void ExpressTextEdit::setEntityDescriptor(const EntityDescriptor *entityDescriptor)
{
    clear();
    std::string str;
    QString text(entityDescriptor->GenerateExpress(str));
    setPlainText(text);
}

void ExpressTextEdit::setTypeDescriptor(const TypeDescriptor *typeDescriptor)
{
    clear();
    std::string str;
    QString text(typeDescriptor->GenerateExpress(str));
    setPlainText(text);
}


/*
void ExpressTextEdit::findExpressObject()
{
    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    QString wordUnderCursor = cursor.selectedText();

    const EntityDescriptor * entityDescriptor = m_Registry.FindEntity(wordUnderCursor.toAscii());
    if (entityDescriptor )
    {
        std::string str;
        setToolTip(entityDescriptor->GenerateExpress(str));
    }
    else setToolTip(QString());

}
*/
