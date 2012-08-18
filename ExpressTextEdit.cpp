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

ExpressTextEdit::ExpressTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , m_Highlighter ( new ExpressSyntaxHighlighter(this->document()))
{
}

void ExpressTextEdit::fillHighlighterWithTypes(const QStringList &list)
{
    m_Highlighter->fillTypes(list);
}

void ExpressTextEdit::fillHighlighterWithEntities(const QStringList &list)
{
    m_Highlighter->fillEntities(list);
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
