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

#ifndef NAVIGATECOMMAND_H
#define NAVIGATECOMMAND_H

#include <QUndoCommand>
class TypeDescriptor;
class MainWindow;

class NavigateCommand : public QUndoCommand
{
public:
    NavigateCommand(MainWindow *controler, const TypeDescriptor *oldDescriptor,  const TypeDescriptor *newDescriptor, QUndoCommand *parent=0);
    void undo();
    void redo();

private:
    MainWindow * m_Controler;
    const TypeDescriptor *m_OldDescriptor, *m_NewDescriptor;
};

#endif // NAVIGATECOMMAND_H
