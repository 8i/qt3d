!include( ../examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

SOURCE += main.cpp

QT += qml quick 3dcore 3drender 3dinput 3dquick

OTHER_FILES += main.qml

SOURCES += \
    main.cpp

RESOURCES += \
    lights.qrc \
    ../exampleresources/obj.qrc