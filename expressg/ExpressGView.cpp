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

#include "ExpressGView.h"
#include <QGLWidget>
#include <QMouseEvent>
#include <QGraphicsItem>

#include <iostream>
using namespace std;

ExpressGView::ExpressGView(QWidget *parent)
    : QGraphicsView(parent)
    , m_Scene()
{
    setViewport(new QGLWidget(parent));
    setScene(&m_Scene);
    setBackgroundBrush(QColor(54,54,76));
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect (&m_Scene, SIGNAL( descriptorDoubleClicked( const TypeDescriptor * ) ), this, SIGNAL(descriptorDoubleClicked(const TypeDescriptor*)));

}

void ExpressGView::setDescriptor(const TypeDescriptor *td)
{
    reframeOn( m_Scene.setDescriptor(td) );
}

void ExpressGView::reframeOn(QGraphicsItem * rootItem)
{
    // first we "enlarge" the scene, to allow more scrolling space
    const QRectF itemsRect = m_Scene.itemsBoundingRect();
    m_Scene.setSceneRect( itemsRect.x()-itemsRect.width()*0.5, itemsRect.y()-itemsRect.height()*0.5, 2.0*itemsRect.width(), 2.0*itemsRect.height() );

    if (rootItem)
        ensureVisible(rootItem);
}
