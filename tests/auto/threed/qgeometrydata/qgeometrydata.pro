load(qttest_p4.prf)
TEMPLATE=app
QT += testlib
CONFIG += unittest warn_on qt3d

INCLUDEPATH += ../../../shared
INCLUDEPATH += ../../../../src/threed/geometry

SOURCES += tst_qgeometrydata.cpp
QT+=widgets
