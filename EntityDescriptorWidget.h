/*  This file is part of [To be named], a STEP-Express viewer
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

#ifndef ENTITYDESCRIPTORWIDGET_H
#define ENTITYDESCRIPTORWIDGET_H

#include <QWidget>
#include <ExpDict.h>
#include <QListWidgetItem>

namespace Ui {
class EntityDescriptorWidget;
}

class EntityDescriptorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EntityDescriptorWidget(QWidget *parent = 0);
    ~EntityDescriptorWidget();

public slots:
    void fill(EntityDescriptor* ed);
    void findEntityDescriptor(QListWidgetItem* item);

signals:
    void entityDescriptorDoubleClicked( EntityDescriptor * );
private:
    Ui::EntityDescriptorWidget *ui;
};

#endif // ENTITYDESCRIPTORWIDGET_H
