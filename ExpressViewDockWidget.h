#ifndef EXPRESSVIEWDOCKWIDGET_H
#define EXPRESSVIEWDOCKWIDGET_H

#include <QDockWidget>

class ExpressTextEdit;
class QToolBar;

class ExpressViewDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ExpressViewDockWidget(QWidget *parent = 0);
    inline ExpressTextEdit * expressTextEdit() { return m_ExpressTextEdit; }

signals:
    
public slots:

private:
    ExpressTextEdit * m_ExpressTextEdit;
    QToolBar * m_ToolBar;
    
};

#endif // EXPRESSVIEWDOCKWIDGET_H
