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

#include "ExpressViewDockWidget.h"
#include "ExpressTextEdit.h"
#include <QToolBar>
#include <QAction>

ExpressViewDockWidget::ExpressViewDockWidget(QWidget *parent)
    : QDockWidget(tr("Express View"), parent)
    , m_ToolBar (new QToolBar(this))
{
    // Build ToolBar
    setTitleBarWidget(m_ToolBar);
    m_ToolBar->setContentsMargins(0, 0, 0, 0);
    toggleViewAction()->setIcon(QIcon(":/Express"));
    toggleViewAction()->setShortcut( QKeySequence(Qt::Key_F4) );

    QWidget * toolBarSpacer= new QWidget(m_ToolBar);
    toolBarSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    QAction * hideDockWidgetAction = new QAction(QIcon(":close"), tr("Hide Explorer"), this);

    m_ToolBar->addWidget(toolBarSpacer);
    m_ToolBar->addAction(hideDockWidgetAction);

    connect ( hideDockWidgetAction, SIGNAL(triggered()), this, SLOT (hide() ) );

    // content
    setContentsMargins(0,0,-1,0);

}
