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
    addcomment.cpp \
    addmember.cpp \
    createproject.cpp \
    createtask.cpp \
    createteam.cpp \
    main.cpp \
    mainwindow.cpp \
    entrancepage.cpp \
    membersetting.cpp \
    membersettingteam.cpp \
    organization.cpp \
    project.cpp \
    recovery.cpp \
    signuppage.cpp \
    loginpage.cpp \
    generics.cpp \
    home.cpp \
    createorganization.cpp \
    task.cpp \
    team.cpp

HEADERS += \
    aboutorganization.h \
    aboutproject.h \
    aboutteam.h \
    addcomment.h \
    addmember.h \
    createorganization.h \
    createproject.h \
    createtask.h \
    createteam.h \
    mainwindow.h \
    entrancepage.h \
    membersetting.h \
    membersettingteam.h \
    organization.h \
    project.h \
    recovery.h \
    signuppage.h \
    loginpage.h \
    generics.h \
    home.h \
    task.h \
    team.h

FORMS += \
    aboutorganization.ui \
    aboutproject.ui \
    aboutteam.ui \
    addcomment.ui \
    addmember.ui \
    createorganization.ui \
    createproject.ui \
    createtask.ui \
    createteam.ui \
    entrancepage.ui \
    membersetting.ui \
    membersettingteam.ui \
    project.ui \
    recovery.ui \
    signuppage.ui \
    loginpage.ui \
    home.ui \
    organization.ui \
    task.ui \
    team.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
