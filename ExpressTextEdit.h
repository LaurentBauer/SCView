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
#include <schema.h>

class EntityDescriptor;
class TypeDescriptor;
class ExpressSyntaxHighlighter;

class ExpressTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ExpressTextEdit(Registry &registry, QWidget *parent=0);
    void fillHighlighterWithTypes(const QStringList &list);
    void fillHighlighterWithEntities(const QStringList &list);

protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

signals:
    void descriptorDoubleClicked(const TypeDescriptor *);

public slots:
    void setDescriptor(const TypeDescriptor * typeDescriptor);

private:
    Registry &m_Registry;
    ExpressSyntaxHighlighter * m_Highlighter;
};

#endif // EXPRESSTEXTEDIT_H
