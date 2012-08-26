#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T21:40:49
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = SCLView
TEMPLATE = app

STEPCODE_DIR = C:/prog/STEP/SCL0-5
STEPCODE_BUILD_DIR = C:/prog/STEP/SCL0-5/ap214e3


win32:LIBS += $${STEPCODE_BUILD_DIR}/bin/libsdai_AP214E3_2010.dll \
    $${STEPCODE_BUILD_DIR}/bin/libstepcore.dll \
    $${STEPCODE_BUILD_DIR}/bin/libstepdai.dll \
    $${STEPCODE_BUILD_DIR}/bin/libsteputils.dll \
    $${STEPCODE_BUILD_DIR}/bin/libexpress.dll \
    $${STEPCODE_BUILD_DIR}/bin/libstepeditor.dll

INCLUDEPATH += $${STEPCODE_BUILD_DIR}/AP214E3_2010 \
    $${STEPCODE_BUILD_DIR}/include \
    $${STEPCODE_DIR}/include \
    $${STEPCODE_DIR}/src/cleditor \
    $${STEPCODE_DIR}/src/clutils \
    $${STEPCODE_DIR}/src/clstepcore \
    $${STEPCODE_DIR}/src/cldai


SOURCES += main.cpp\
        MainWindow.cpp \
    EntityDescriptorWidget.cpp \
    manhattanstyle.cpp \
    styleanimator.cpp \
    SCLDockWidget.cpp \
    expressg/ExpressGView.cpp \
    expressg/ExpressGScene.cpp \
    expressg/EntityItem.cpp \
    expressg/TypeItem.cpp \
    expressg/LinkItem.cpp \
    expressg/ExpressgRectItem.cpp \
    ExpressViewDockWidget.cpp \
    ExpressTextEdit.cpp \
    ExpressSyntaxHighlighter.cpp \
    SchemaTree.cpp \
    NavigateCommand.cpp

HEADERS  += MainWindow.h \
    EntityDescriptorWidget.h \
    manhattanstyle.h \
    styleanimator.h \
    SCLDockWidget.h \
    expressg/ExpressGView.h \
    expressg/ExpressGScene.h \
    expressg/EntityItem.h \
    expressg/TypeItem.h \
    expressg/LinkItem.h \
    expressg/ExpressgRectItem.h \
    ExpressViewDockWidget.h \
    ExpressTextEdit.h \
    ExpressSyntaxHighlighter.h \
    SchemaTree.h \
    NavigateCommand.h

FORMS    += MainWindow.ui \
    EntityDescriptorWidget.ui

RESOURCES += \
    sclview.qrc

win32:CONFIG *= dll
win32 {
    # Location libraries
    LIB_DIR = C:/prog/STEP/SCL0-5/ap214e3/bin
}
