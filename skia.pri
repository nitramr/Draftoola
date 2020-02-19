DISTFILES += skia.pri

QMAKE_SKIA_DIR = $$(SKIA_DIR)

exists ($$QMAKE_SKIA_DIR) {
  INCLUDEPATH += $$QMAKE_SKIA_DIR
  INCLUDEPATH += $$QMAKE_SKIA_DIR/include/pathops/
  INCLUDEPATH += $$QMAKE_SKIA_DIR/include/core/
  INCLUDEPATH += $$QMAKE_SKIA_DIR/include/config/
  INCLUDEPATH += $$QMAKE_SKIA_DIR/include/effects/
  Release {
    QMAKE_LIBDIR += $$QMAKE_SKIA_DIR/out/Release
  }
  Debug {
    QMAKE_LIBDIR += $$QMAKE_SKIA_DIR/out/Debug
  }

} else {
  message ("Please, specify skia dir using environment variable SKIA_DIR")
}


LIBS += -L$$QMAKE_SKIA_DIR/out/Release/
INCLUDEPATH += $$QMAKE_SKIA_DIR/out/Release
DEPENDPATH += $$QMAKE_SKIA_DIR/out/Release

win32:*msvc* {
  LIBS *=  skia.lib
}

*g++* | *clang* {
  LIBS *= -lskia
}

