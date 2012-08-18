#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SCLDockWidget.h"
#include "EntityTypeList.h"
#include "expressg/ExpressGView.h"
#include <QToolButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QCompleter>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_EntityTypeTree ( new EntityTypeTree() )
    , m_SCLDockWidget (new SCLDockWidget(m_EntityTypeTree, this) )
    , m_ExpressGView (new ExpressGView(this))
    , m_SearchLineEdit(0)
    , m_StringListModel(new QStringListModel())
{
    ui->setupUi(this);
    QString title = QApplication::applicationName()+ ": " + m_EntityTypeTree->getSchemaName();
    setWindowTitle( title );
    buildView();
    setCentralWidget(m_ExpressGView);

    connect(m_ExpressGView, SIGNAL(entityDescriptorDoubleClicked(const EntityDescriptor*)), m_EntityTypeTree, SLOT(select( const EntityDescriptor * )));
    connect(m_ExpressGView, SIGNAL(typeDescriptorDoubleClicked(const TypeDescriptor*)), m_EntityTypeTree, SLOT(select( const TypeDescriptor * )));
    connect(m_EntityTypeTree, SIGNAL(selectedEntityChanged(const EntityDescriptor*)), m_ExpressGView, SLOT(setEntityDescriptor(const EntityDescriptor*)));
    connect(m_EntityTypeTree, SIGNAL(selectedTypeChanged(const TypeDescriptor*)), m_ExpressGView, SLOT(setTypeDescriptor(const TypeDescriptor*)));
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT (startSearch()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSearch()
{
    m_SearchLineEdit->setFocus();
    m_SearchLineEdit->clear();
}

void MainWindow::buildView()
{
    addDockWidget(Qt::LeftDockWidgetArea, m_SCLDockWidget);
    ui->menuWindows->addAction(m_SCLDockWidget->toggleViewAction());

    // Search
    QWidget * searchWidget = new QWidget(ui->menuBar);
    m_SearchLineEdit = new QLineEdit(searchWidget);
    QLabel * label = new QLabel(searchWidget);
    label->setPixmap(QPixmap(":/Find"));
    QHBoxLayout * layout = new QHBoxLayout(searchWidget);
    layout->addWidget(label);
    layout->addWidget(m_SearchLineEdit);
    layout->setContentsMargins(0,0,0,0);
    searchWidget->setLayout(layout);
    ui->menuBar->setCornerWidget(searchWidget);

    m_EntityTypeTree->fillStringListModel(m_StringListModel);
    m_SearchLineEdit->setText("Search");
    QCompleter * completer = new QCompleter(m_StringListModel);
    completer->setMaxVisibleItems(10);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_SearchLineEdit->setCompleter(completer);
    connect(completer, SIGNAL(highlighted(QString)), this, SLOT(selectSearchResult(QString)));

}


void MainWindow::selectSearchResult(QString highlighted)
{
    QList<QTreeWidgetItem * > results = m_EntityTypeTree->findItems(highlighted, Qt::MatchFixedString |Qt::MatchCaseSensitive| Qt::MatchRecursive);
    if (!results.isEmpty())
    {
        QTreeWidgetItem * item = results.first();
        m_EntityTypeTree->clearSelection();
        item->setSelected(true);
        m_EntityTypeTree->expandItem(item);
        m_EntityTypeTree->scrollToItem(item);
    }
}
