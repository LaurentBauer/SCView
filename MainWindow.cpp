#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SCLDockWidget.h"
#include "EntityTypeList.h"
#include "expressg/ExpressGView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_EntityTypeTree ( new EntityTypeTree() )
    , m_SCLDockWidget (new SCLDockWidget(m_EntityTypeTree, this) )
    , m_ExpressGView (new ExpressGView(this))
{
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    buildView();
    setCentralWidget(m_ExpressGView);

    connect(m_ExpressGView, SIGNAL(entityDescriptorDoubleClicked(const EntityDescriptor*)), m_EntityTypeTree, SLOT(select( const EntityDescriptor * )));
    connect(m_ExpressGView, SIGNAL(typeDescriptorDoubleClicked(const TypeDescriptor*)), m_EntityTypeTree, SLOT(select( const TypeDescriptor * )));
    connect(m_EntityTypeTree, SIGNAL(selectedEntityChanged(const EntityDescriptor*)), m_ExpressGView, SLOT(setEntityDescriptor(const EntityDescriptor*)));
    connect(m_EntityTypeTree, SIGNAL(selectedTypeChanged(const TypeDescriptor*)), m_ExpressGView, SLOT(setTypeDescriptor(const TypeDescriptor*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildView()
{
    addDockWidget(Qt::LeftDockWidgetArea, m_SCLDockWidget);
    ui->menuWindows->addAction(m_SCLDockWidget->toggleViewAction());
}
