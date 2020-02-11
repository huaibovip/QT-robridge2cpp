QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rosbridge/src/client/socket_tcp_connection.cpp \
    rosbridge/src/ros_bridge.cpp \
    rosbridge/src/ros_service.cpp \
    rosbridge/src/ros_tf_broadcaster.cpp \
    rosbridge/src/ros_time.cpp \
    rosbridge/src/ros_topic.cpp

HEADERS += \
    mainwindow.h \
    rosbridge/include/client/socket_tcp_connection.h \
    rosbridge/include/helper.h \
    rosbridge/include/messages/rosbridge_advertise_msg.h \
    rosbridge/include/messages/rosbridge_advertise_service_msg.h \
    rosbridge/include/messages/rosbridge_call_service_msg.h \
    rosbridge/include/messages/rosbridge_msg.h \
    rosbridge/include/messages/rosbridge_publish_msg.h \
    rosbridge/include/messages/rosbridge_service_response_msg.h \
    rosbridge/include/messages/rosbridge_subscribe_msg.h \
    rosbridge/include/messages/rosbridge_unadvertise_msg.h \
    rosbridge/include/messages/rosbridge_unadvertise_service_msg.h \
    rosbridge/include/messages/rosbridge_unsubscribe_msg.h \
    rosbridge/include/rapidjson/allocators.h \
    rosbridge/include/rapidjson/document.h \
    rosbridge/include/rapidjson/encodedstream.h \
    rosbridge/include/rapidjson/encodings.h \
    rosbridge/include/rapidjson/error/en.h \
    rosbridge/include/rapidjson/error/error.h \
    rosbridge/include/rapidjson/filereadstream.h \
    rosbridge/include/rapidjson/filewritestream.h \
    rosbridge/include/rapidjson/fwd.h \
    rosbridge/include/rapidjson/internal/biginteger.h \
    rosbridge/include/rapidjson/internal/diyfp.h \
    rosbridge/include/rapidjson/internal/dtoa.h \
    rosbridge/include/rapidjson/internal/ieee754.h \
    rosbridge/include/rapidjson/internal/itoa.h \
    rosbridge/include/rapidjson/internal/meta.h \
    rosbridge/include/rapidjson/internal/pow10.h \
    rosbridge/include/rapidjson/internal/regex.h \
    rosbridge/include/rapidjson/internal/stack.h \
    rosbridge/include/rapidjson/internal/strfunc.h \
    rosbridge/include/rapidjson/internal/strtod.h \
    rosbridge/include/rapidjson/internal/swap.h \
    rosbridge/include/rapidjson/istreamwrapper.h \
    rosbridge/include/rapidjson/memorybuffer.h \
    rosbridge/include/rapidjson/memorystream.h \
    rosbridge/include/rapidjson/msinttypes/inttypes.h \
    rosbridge/include/rapidjson/msinttypes/stdint.h \
    rosbridge/include/rapidjson/ostreamwrapper.h \
    rosbridge/include/rapidjson/pointer.h \
    rosbridge/include/rapidjson/prettywriter.h \
    rosbridge/include/rapidjson/rapidjson.h \
    rosbridge/include/rapidjson/reader.h \
    rosbridge/include/rapidjson/schema.h \
    rosbridge/include/rapidjson/stream.h \
    rosbridge/include/rapidjson/stringbuffer.h \
    rosbridge/include/rapidjson/writer.h \
    rosbridge/include/ros_bridge.h \
    rosbridge/include/ros_message_factory.h \
    rosbridge/include/ros_service.h \
    rosbridge/include/ros_tf_broadcaster.h \
    rosbridge/include/ros_time.h \
    rosbridge/include/ros_topic.h \
    rosbridge/include/types.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /home/charles/Projects/QTProjects/rosbridge2cpp/rosbridge/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

