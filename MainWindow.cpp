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

#include "ui_MainWindow.h"
#include "MainWindow.h"
#include "SCLDockWidget.h"
#include "ExpressViewDockWidget.h"
#include "SchemaTree.h"
#include "expressg/ExpressGView.h"
#include "ExpressTextEdit.h"
#include "NavigateCommand.h"
#include <QUndoStack>
#include <QToolButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QCompleter>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_UndoStack(new QUndoStack(this))
    , m_Registry( SchemaInit )
    , m_Current(0)
    , m_SchemaTree ( new SchemaTree(m_Registry) )
    , m_SCLDockWidget (new SCLDockWidget(m_SchemaTree, this) )
    , m_ExpressViewDockWidget( new ExpressViewDockWidget(this))
    , m_ExpressTextEdit(new ExpressTextEdit(m_Registry, m_ExpressViewDockWidget))
    , m_ExpressGView (new ExpressGView(this))
    , m_StringListModel(new QStringListModel())
    , m_SearchLineEdit(0)
{
    ui->setupUi(this);


    m_Registry.ResetSchemas();
    const Schema * sc = m_Registry.NextSchema();
    QString title = QApplication::applicationName()+ ": " + QString(sc->Name());
    setWindowTitle( title );
    buildView();
    setCentralWidget(m_ExpressGView);

    connect(m_ExpressGView, SIGNAL(descriptorDoubleClicked(const TypeDescriptor*))
            , this, SLOT(setDescriptorCommand(const TypeDescriptor*)));
    connect(m_SchemaTree, SIGNAL(selectedDescriptorChanged(const TypeDescriptor*))
            , this, SLOT(setDescriptorCommand(const TypeDescriptor*)));
    connect(m_ExpressTextEdit, SIGNAL(descriptorDoubleClicked(const TypeDescriptor*))
            , this, SLOT(setDescriptorCommand(const TypeDescriptor*)));

    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT (startSearch()));

    m_ExpressTextEdit->fillHighlighterWithTypes( typeList());
    m_ExpressTextEdit->fillHighlighterWithEntities( entityList());

    QAction * undoAction = m_UndoStack->createUndoAction(this);
    QAction * redoAction = m_UndoStack->createRedoAction(this);
    undoAction->setIcon(QIcon(":Undo"));
    redoAction->setIcon(QIcon(":Redo"));
    undoAction->setShortcut(QKeySequence(tr("Ctrl+Z")));
    redoAction->setShortcut(QKeySequence(tr("Ctrl+Y")));
    ui->mainToolBar->addAction(undoAction);
    ui->mainToolBar->addAction(redoAction);
    ui->menuEdit->insertAction(ui->actionFind,redoAction);
    ui->menuEdit->insertAction(redoAction,undoAction);
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

void MainWindow::setDescriptor(const TypeDescriptor *descriptor)
{
    m_SchemaTree->select(descriptor);
    m_ExpressGView->setDescriptor(descriptor);
    m_ExpressTextEdit->setDescriptor(descriptor);
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

void MainWindow::setDescriptorCommand(const TypeDescriptor *descriptor)
{

    NavigateCommand * navigateCommand = new NavigateCommand(this, m_Current, descriptor);
    m_UndoStack->push(navigateCommand);
    m_Current = descriptor;
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

