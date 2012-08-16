#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T21:40:49
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = SCLView
TEMPLATE = app

win32:LIBS += C:/prog/STEP/SCL0-5/ap214e3/bin/libsdai_AP214E3_2010.dll \
    C:/prog/STEP/SCL0-5/ap214e3/bin/libstepcore.dll \
    C:/prog/STEP/SCL0-5/ap214e3/bin/libstepdai.dll \
    C:/prog/STEP/SCL0-5/ap214e3/bin/libsteputils.dll \
    C:/prog/STEP/SCL0-5/ap214e3/bin/libexpress.dll \
    C:/prog/STEP/SCL0-5/ap214e3/bin/libstepeditor.dll

INCLUDEPATH += C:/prog/STEP/SCL0-5/ap214e3/AP214E3_2010 \
    C:/prog/STEP/SCL0-5/ap214e3/include \
    C:/prog/STEP/SCL0-5/include \
    C:/prog/STEP/SCL0-5/src/cleditor \
    C:/prog/STEP/SCL0-5/src/clutils \
    C:/prog/STEP/SCL0-5/src/clstepcore \
    C:/prog/STEP/SCL0-5/src/cldai


SOURCES += main.cpp\
        MainWindow.cpp \
    SchemaModel.cpp \
    EntityTypeList.cpp \
    EntityDescriptorWidget.cpp \
    manhattanstyle.cpp \
    styleanimator.cpp \
    SCLDockWidget.cpp \
    expressg/ExpressGView.cpp \
    expressg/ExpressGScene.cpp \
    expressg/EntityItem.cpp \
    expressg/TypeItem.cpp \
    expressg/LinkItem.cpp \
    expressg/ExpressgRectItem.cpp
#    TypeDescriptorListWidget.cpp

HEADERS  += MainWindow.h \
    SchemaModel.h \
    EntityTypeList.h \
    EntityDescriptorWidget.h \
    manhattanstyle.h \
    styleanimator.h \
    SCLDockWidget.h \
    expressg/ExpressGView.h \
    expressg/ExpressGScene.h \
    expressg/EntityItem.h \
    expressg/TypeItem.h \
    expressg/LinkItem.h \
    expressg/ExpressgRectItem.h
#    TypeDescriptorListWidget.h

FORMS    += MainWindow.ui \
    EntityDescriptorWidget.ui

RESOURCES += \
    sclview.qrc

win32:CONFIG *= dll
win32 {
    # Location libraries
    LIB_DIR = C:/prog/STEP/SCL0-5/ap214e3/bin
}
