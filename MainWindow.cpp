#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SCLDockWidget.h"
#include "EntityTypeList.h"
//#include "EntityDescriptorWidget.h"
#include "expressg/ExpressGView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_SCLDockWidget (new SCLDockWidget(this) )
    , m_EntityTypeList ( new EntityTypeList(m_SCLDockWidget) )
//    , m_EntityDescriptorWidget ( new EntityDescriptorWidget(this) )
    , m_ExpressGView (new ExpressGView(this))
{
    ui->setupUi(this);
    setWindowTitle(QApplication::applicationName());
    buildView();
//    setCentralWidget(m_EntityDescriptorWidget);
    setCentralWidget(m_ExpressGView);

    // connect(m_EntityTypeList, SIGNAL(entityChanged(EntityDescriptor*)), m_EntityDescriptorWidget, SLOT(fill(EntityDescriptor*)));
    //connect(m_EntityDescriptorWidget, SIGNAL(entityDescriptorDoubleClicked(EntityDescriptor*)), m_EntityTypeList, SLOT(select( EntityDescriptor * )));
    connect(m_ExpressGView, SIGNAL(entityDescriptorDoubleClicked(const EntityDescriptor*)), m_EntityTypeList, SLOT(select( const EntityDescriptor * )));
    connect(m_EntityTypeList, SIGNAL(entityChanged(const EntityDescriptor*)), m_ExpressGView, SLOT(setEntityDescriptor(const EntityDescriptor*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buildView()
{
    m_SCLDockWidget->setWidget(m_EntityTypeList);
    addDockWidget(Qt::LeftDockWidgetArea, m_SCLDockWidget);
}
