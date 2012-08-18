#     This file is part of [To be named], a STEP-Express viewer
#     Copyright (C) 2012 Mark Pictor mpictor@gmail.com
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Library General Public
#     License as published by the Free Software Foundation; version 2
#     of the License.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Library General Public License for more details.
#
#     You should have received a copy of the GNU Library General Public License
#     along with this library; see the file COPYING.LIB.  If not, write to
#     the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
#     Boston, MA 02110-1301, USA.

PROJECT( SCView )
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set( CMAKE_BUILD_TYPE "Debug" )
set( SCL_IS_SUBBUILD TRUE )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# qt4
find_package( Qt4 REQUIRED QtCore QtGui QtOpenGL )
include( ${QT_USE_FILE} )
add_definitions( ${QT4_DEFINITIONS} )

# STEPcode
set( STEPCODE_ROOT_DIR "" CACHE PATH "Path to STEPcode, required" )
if( NOT IS_DIRECTORY ${STEPCODE_ROOT_DIR} )
    message( FATAL_ERROR "STEPcode root dir must be set, either through the GUI or on the command line with '-DSTEPCODE_ROOT_DIR=/path/to/sc'" )
endif( NOT IS_DIRECTORY ${STEPCODE_ROOT_DIR} )
set( STEPCODE_BUILD_DIR ${CMAKE_BINARY_DIR}/sc CACHE PATH "STEPcode build subdir" )

# schemas
if( NOT DEFINED SCHEMAS )
    set( SCHEMAS "ap214e3" CACHE STRING "Schema(s) to compile and link to; use the names of directories under STEPcode/data." )
    message( "** SCHEMAS undefined. Using ${SCHEMAS}" )
endif( NOT DEFINED SCHEMAS )
set( SCL_BUILD_SCHEMAS ${SCHEMAS} CACHE INTERNAL "Schema, internal, immutable" FORCE )
add_subdirectory( ${STEPCODE_ROOT_DIR} "${CMAKE_CURRENT_BINARY_DIR}/sc" EXCLUDE_FROM_ALL )

# QT ui files and MOCable headers
set( MOC_HDRS
     MainWindow.h EntityDescriptorWidget.h SCLDockWidget.h expressg/ExpressGView.h
     expressg/ExpressGScene.h EntityTypeList.h manhattanstyle.h styleanimator.h
)
set( UI_FILES
     EntityDescriptorWidget.ui  MainWindow.ui
)
set( RESOURCE_FILES sclview.qrc )
QT4_WRAP_UI(  UI_HDRS  ${UI_FILES} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HDRS} )
QT4_ADD_RESOURCES( RESOURCE_SRCS ${RESOURCE_FILES} )

# app sources and headers
set( SRCS
    EntityDescriptorWidget.cpp     expressg/ExpressGView.cpp  manhattanstyle.cpp
    EntityTypeList.cpp             expressg/LinkItem.cpp      SchemaModel.cpp
    expressg/EntityItem.cpp        expressg/TypeItem.cpp      SCLDockWidget.cpp
    expressg/ExpressgRectItem.cpp  main.cpp                   styleanimator.cpp
    expressg/ExpressGScene.cpp     MainWindow.cpp
)

set( HDRS
    EntityDescriptorWidget.h     expressg/ExpressGView.h  SchemaModel.h
    EntityTypeList.h             expressg/LinkItem.h      SCLDockWidget.h
    expressg/EntityItem.h        expressg/TypeItem.h      styleanimator.h
    expressg/ExpressgRectItem.h  MainWindow.h
    expressg/ExpressGScene.h     manhattanstyle.h
)
include_directories( ${STEPCODE_ROOT_DIR}/src/base ${STEPCODE_ROOT_DIR}/src/clstepcore
                     ${STEPCODE_ROOT_DIR}/src/cldai ${STEPCODE_ROOT_DIR}/src/clutils
                     ${STEPCODE_ROOT_DIR}/src/cleditor ${STEPCODE_BUILD_DIR}/include
                     ${STEPCODE_ROOT_DIR}/include ${CMAKE_BINARY_DIR} )

# this function builds SCView for a single schema
function( BUILD_SCVIEW schema )
    # Set SCHEMA_LINK_NAME. Logic below is derived from STEPcode/data/CMakeLists.txt; I (MP) am the author.
    # lib will be in ${CMAKE_BINARY_DIR}/lib/, named sdai_${SCHEMA_LINK_NAME}. Prefix/suffix depend on platform, of course.
    # lib source will be at ${CMAKE_BINARY_DIR}/${SCHEMA_LINK_NAME}/
    file( GLOB SCHEMA_FILE "${STEPCODE_ROOT_DIR}/data/${schema}/*.exp" )
    if( NOT EXISTS ${SCHEMA_FILE} )
        message( FATAL_ERROR "Expected one express file. Found '${SCHEMA_FILE}' instead." )
    endif( NOT EXISTS ${SCHEMA_FILE} )
    get_filename_component( SCHEMA_SN ${SCHEMA_FILE} NAME )
    string( REGEX REPLACE "\(.*\).[Ee][Xx][Pp]" "\\1" SCHEMA_LINK_NAME ${SCHEMA_SN} )

    message( "** Building ${PROJECT_NAME} for ${SCHEMA_LINK_NAME}" )
    add_executable( ${PROJECT_NAME}_${SCHEMA_LINK_NAME} ${SRCS} ${HDRS} ${UI_HDRS} ${MOC_SRCS} ${RESOURCE_SRCS} )
    target_link_libraries( ${PROJECT_NAME}_${SCHEMA_LINK_NAME} ${QT_LIBRARIES} base stepcore stepeditor stepdai steputils sdai_${SCHEMA_LINK_NAME} )
    #can't use include_directories for the schema headers because each target would see the headers from all previous targets
    set_target_properties( ${PROJECT_NAME}_${SCHEMA_LINK_NAME} PROPERTIES COMPILE_FLAGS "-I${STEPCODE_BUILD_DIR}/data/${SCHEMA_LINK_NAME}" )
endfunction( BUILD_SCVIEW schema )

foreach( schema ${SCHEMAS} )
    BUILD_SCVIEW( ${schema} )
endforeach( schema ${SCHEMAS} )
