/*  This file is part of SCView, a STEP-Express viewer
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

#ifndef EXPRESSGSCENE_H
#define EXPRESSGSCENE_H

#include <QGraphicsScene>
class EntityDescriptor;
class TypeDescriptor;

class ExpressGScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ExpressGScene(QObject *parent = 0);
    QGraphicsItem* setDescriptor(const TypeDescriptor *td);

protected:
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    // virtual mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void descriptorDoubleClicked( const TypeDescriptor * );

public slots:
    
private:

};

#endif // EXPRESSGSCENE_H
