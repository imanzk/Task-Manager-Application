QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutorganization.cpp \
    aboutproject.cpp \
    aboutteam.cpp \
    archived.cpp \
    createproject.cpp \
    createteam.cpp \
    main.cpp \
    mainwindow.cpp \
    entrancepage.cpp \
    membertask.cpp \
    organization.cpp \
    project.cpp \
    recovery.cpp \
    signuppage.cpp \
    loginpage.cpp \
    generics.cpp \
    home.cpp \
    createorganization.cpp \
    tasks.cpp \
    team.cpp

HEADERS += \
    aboutorganization.h \
    aboutproject.h \
    aboutteam.h \
    archived.h \
    createorganization.h \
    createproject.h \
    createteam.h \
    mainwindow.h \
    entrancepage.h \
    membertask.h \
    organization.h \
    project.h \
    recovery.h \
    signuppage.h \
    loginpage.h \
    generics.h \
    home.h \
    tasks.h \
    team.h

FORMS += \
    aboutorganization.ui \
    aboutproject.ui \
    aboutteam.ui \
    archived.ui \
    createorganization.ui \
    createproject.ui \
    createteam.ui \
    entrancepage.ui \
    membertask.ui \
    project.ui \
    recovery.ui \
    signuppage.ui \
    loginpage.ui \
    home.ui \
    organization.ui \
    tasks.ui \
    team.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
