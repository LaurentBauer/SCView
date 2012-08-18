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

#ifndef EXPRESSTEXTEDIT_H
#define EXPRESSTEXTEDIT_H

#include <QTextEdit>

class EntityDescriptor;
class TypeDescriptor;
class ExpressSyntaxHighlighter;

class ExpressTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ExpressTextEdit(QWidget *parent = 0);
    void fillHighlighterWithTypes(const QStringList &list);
    void fillHighlighterWithEntities(const QStringList &list);
signals:
    
public slots:
    void setEntityDescriptor(const EntityDescriptor * entityDescriptor);
    void setTypeDescriptor(const TypeDescriptor * typeDescriptor);

private:
    ExpressSyntaxHighlighter * m_Highlighter;
};

#endif // EXPRESSTEXTEDIT_H
