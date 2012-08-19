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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern void SchemaInit( class Registry & );
#include <schema.h>

class SCLDockWidget;
class EntityTypeTree;
class EntityDescriptorWidget;
class ExpressGView;
class ExpressGScene;
class QLineEdit;
class QStringListModel;
class ExpressViewDockWidget;
class ExpressTextEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QStringList typeList();
    QStringList entityList();

private slots:
    void startSearch();
    void selectSearchResult(QString highlighted);
    void setEntity(const EntityDescriptor * entityDescriptor);
    void setType(const TypeDescriptor * typeDescriptor);

private:
    void buildView();
private:
    Ui::MainWindow *ui;
    Registry m_Registry;
    EntityTypeTree * m_EntityTypeTree;
    SCLDockWidget * m_SCLDockWidget;
    ExpressViewDockWidget * m_ExpressViewDockWidget;
    ExpressTextEdit * m_ExpressTextEdit;
    ExpressGView * m_ExpressGView;
    QStringListModel * m_StringListModel;
    QLineEdit * m_SearchLineEdit;

};

#endif // MAINWINDOW_H
