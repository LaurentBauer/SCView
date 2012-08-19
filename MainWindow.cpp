#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SCLDockWidget.h"
#include "ExpressViewDockWidget.h"
#include "EntityTypeList.h"
#include "expressg/ExpressGView.h"
#include "ExpressTextEdit.h"
#include <QToolButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QCompleter>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Registry( SchemaInit )
    , m_EntityTypeTree ( new EntityTypeTree(m_Registry) )
    , m_SCLDockWidget (new SCLDockWidget(m_EntityTypeTree, this) )
    , m_ExpressViewDockWidget( new ExpressViewDockWidget(this))
    , m_ExpressTextEdit(new ExpressTextEdit(m_Registry, m_ExpressViewDockWidget))
    , m_ExpressGView (new ExpressGView(this))
    , m_StringListModel(new QStringListModel())
    , m_SearchLineEdit(0)
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

    connect(m_EntityTypeTree, SIGNAL(selectedEntityChanged(const EntityDescriptor*))
            , m_ExpressTextEdit, SLOT(setEntityDescriptor(const EntityDescriptor*)));
    connect(m_EntityTypeTree, SIGNAL(selectedTypeChanged(const TypeDescriptor*))
            , m_ExpressTextEdit, SLOT(setTypeDescriptor(const TypeDescriptor*)));

    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT (startSearch()));
    m_ExpressTextEdit->fillHighlighterWithTypes( typeList());
    m_ExpressTextEdit->fillHighlighterWithEntities( entityList());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::typeList()
{
    QStringList list;
    const TypeDescriptor * typeDescriptor;
    m_Registry.ResetTypes();
    while ( (typeDescriptor= m_Registry.NextType() ) )
        list << typeDescriptor->Name();
    return list;
}

QStringList MainWindow::entityList()
{
    QStringList list;
    const EntityDescriptor * entityDescriptor;
    m_Registry.ResetEntities();
    while ( (entityDescriptor= m_Registry.NextEntity() ) )
        list << entityDescriptor->Name();
    return list;
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

    m_ExpressViewDockWidget->setWidget(m_ExpressTextEdit);
    addDockWidget(Qt::LeftDockWidgetArea, m_ExpressViewDockWidget);
    ui->menuWindows->addAction(m_ExpressViewDockWidget->toggleViewAction());

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
