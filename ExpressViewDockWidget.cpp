#include "ExpressViewDockWidget.h"
#include "ExpressTextEdit.h"
#include <QToolBar>
#include <QAction>

ExpressViewDockWidget::ExpressViewDockWidget(QWidget *parent)
    : QDockWidget(tr("Express View"), parent)
    , m_ExpressTextEdit (new ExpressTextEdit(this))
    , m_ToolBar (new QToolBar(this))
{
    setWidget(m_ExpressTextEdit);
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
