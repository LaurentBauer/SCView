#include "ui_MainWindow.h"
#include "MainWindow.h"
#include "SCLDockWidget.h"
#include "ExpressViewDockWidget.h"
#include "SchemaTree.h"
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
    , m_SchemaTree ( new SchemaTree(m_Registry) )
    , m_SCLDockWidget (new SCLDockWidget(m_SchemaTree, this) )
    , m_ExpressViewDockWidget( new ExpressViewDockWidget(this))
    , m_ExpressTextEdit(new ExpressTextEdit(m_Registry, m_ExpressViewDockWidget))
    , m_ExpressGView (new ExpressGView(this))
    , m_StringListModel(new QStringListModel())
    , m_SearchLineEdit(0)
{
    ui->setupUi(this);
    QString title = QApplication::applicationName()+ ": " + m_SchemaTree->getSchemaName();
    setWindowTitle( title );
    buildView();
    setCentralWidget(m_ExpressGView);

    connect(m_ExpressGView, SIGNAL(entityDescriptorDoubleClicked(const EntityDescriptor*))
            , this, SLOT(setEntity(const EntityDescriptor*)));
    connect(m_SchemaTree, SIGNAL(selectedEntityChanged(const EntityDescriptor*))
            , this, SLOT(setEntity(const EntityDescriptor*)));
    connect(m_ExpressTextEdit, SIGNAL(entityDoubleClicked(const EntityDescriptor*))
            , this, SLOT(setEntity(const EntityDescriptor*)));

    connect(m_ExpressGView, SIGNAL(typeDescriptorDoubleClicked(const TypeDescriptor*))
            , this, SLOT(setType(const TypeDescriptor*)));
    connect(m_SchemaTree, SIGNAL(selectedTypeChanged(const TypeDescriptor*))
            , this, SLOT(setType(const TypeDescriptor*)));
    connect(m_ExpressTextEdit, SIGNAL(typeDoubleClicked(const TypeDescriptor*))
            , this, SLOT(setType(const TypeDescriptor*)));

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

void MainWindow::selectSearchResult(QString highlighted)
{
    QList<QTreeWidgetItem * > results = m_SchemaTree->findItems(highlighted, Qt::MatchFixedString |Qt::MatchCaseSensitive| Qt::MatchRecursive);
    if (!results.isEmpty())
    {
        QTreeWidgetItem * item = results.first();
        m_SchemaTree->clearSelection();
        item->setSelected(true);
        m_SchemaTree->expandItem(item);
        m_SchemaTree->scrollToItem(item);
    }
}

void MainWindow::setEntity(const EntityDescriptor *entityDescriptor)
{
    QObject * sender = QObject::sender();
    if (sender!=m_SchemaTree)
        m_SchemaTree->select(entityDescriptor);
    m_ExpressGView->setEntityDescriptor(entityDescriptor);
    m_ExpressTextEdit->setEntityDescriptor(entityDescriptor);
}

void MainWindow::setType(const TypeDescriptor *typeDescriptor)
{
    QObject * sender = QObject::sender();
    if (sender!=m_SchemaTree)
        m_SchemaTree->select(typeDescriptor);
    m_ExpressGView->setTypeDescriptor(typeDescriptor);
    m_ExpressTextEdit->setTypeDescriptor(typeDescriptor);

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

    m_SchemaTree->fillStringListModel(m_StringListModel);
    m_SearchLineEdit->setText("Search");
    QCompleter * completer = new QCompleter(m_StringListModel);
    completer->setMaxVisibleItems(10);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_SearchLineEdit->setCompleter(completer);
    connect(completer, SIGNAL(highlighted(QString)), this, SLOT(selectSearchResult(QString)));

}

