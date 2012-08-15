/*  This file is part of [To be named], a STEP-Express viewer
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

#include "SCLDockWidget.h"
#include <QToolBar>
#include <QAction>

SCLDockWidget::SCLDockWidget(QWidget *parent)
    : QDockWidget ("SCL Explorer", parent)
    , m_ToolBar (new QToolBar(this))
{

    // Build ToolBar
    setTitleBarWidget(m_ToolBar);
    m_ToolBar->setContentsMargins(0, 0, 0, 0);
    toggleViewAction()->setIcon(QIcon(":/type"));
    toggleViewAction()->setShortcut( QKeySequence(Qt::Key_F3) );

    QActionGroup * contentGroup= new QActionGroup(this);
    QAction * listAction = new QAction(QIcon(":/listView"), tr("list view"), m_ToolBar);
    listAction->setCheckable(true);
    listAction->setChecked(true);
    QAction * treeAction = new QAction(QIcon(":/treeView"), tr("tree view"), m_ToolBar);
    treeAction->setCheckable(true);
    treeAction->setChecked(false);
    contentGroup->addAction(listAction);
    contentGroup->addAction(treeAction);

    QWidget * toolBarSpacer= new QWidget(m_ToolBar);
    toolBarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QAction * hideDockWidgetAction = new QAction(QIcon(":close"), tr("Hide Explorer"), this);

    m_ToolBar->addAction(listAction);
    m_ToolBar->widgetForAction(listAction)->setProperty("type", QLatin1String("dockbutton"));
    m_ToolBar->addAction(treeAction);
    m_ToolBar->widgetForAction(treeAction)->setProperty("type", QLatin1String("dockbutton"));

    m_ToolBar->addWidget(toolBarSpacer);
    m_ToolBar->addAction(hideDockWidgetAction);

    connect ( hideDockWidgetAction, SIGNAL(triggered()), this, SLOT (hide() ) );

    // content
    setContentsMargins(0,0,-1,0);

}
