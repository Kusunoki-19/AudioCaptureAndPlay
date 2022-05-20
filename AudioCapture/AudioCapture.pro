QT += quick multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        AudioCapturePlayer.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AudioCapturePlayer.h

darwin {
    PRODUCT_NAME = $$TARGET
    macx-xcode: PRODUCT_NAME = $${LITERAL_DOLLAR}{PRODUCT_NAME}
    INFOPLIST = \
       "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
       "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" \
       "<plist version=\"1.0\">" \
       "<dict>" \
        "    <key>CFBundleIconFile</key>" \
        "    <string></string>" \
        "    <key>CFBundlePackageType</key>" \
        "    <string>APPL</string>" \
        "    <key>CFBundleGetInfoString</key>" \
        "    <string>Created by Qt/QMake</string>" \
        "    <key>CFBundleSignature</key>" \
        "    <string>????</string>" \
        "    <key>CFBundleExecutable</key>" \
        "    <string>$$TARGET</string>" \
        "    <key>CFBundleIdentifier</key>" \
        "    <string>com.digia.$${LITERAL_DOLLAR}{PRODUCT_NAME:rfc1034identifier}</string>" \
        "    <key>CFBundleDisplayName</key>" \
        "    <string>$$PRODUCT_NAME</string>" \
        "    <key>CFBundleName</key>" \
        "    <string>$$PRODUCT_NAME</string>" \
        "    <key>CFBundleShortVersionString</key>" \
        "    <string>1.0</string>" \
        "    <key>CFBundleVersion</key>" \
        "    <string>1.0</string>" \
        "    <key>LSRequiresIPhoneOS</key>" \
        "    <true/>" \
        "    <key>UILaunchStoryboardName</key>" \
        "    <string>LaunchScreen</string>" \
        "    <key>UISupportedInterfaceOrientations</key>" \
        "    <array>" \
        "            <string>UIInterfaceOrientationPortrait</string>" \
        "            <string>UIInterfaceOrientationPortraitUpsideDown</string>" \
        "            <string>UIInterfaceOrientationLandscapeLeft</string>" \
        "            <string>UIInterfaceOrientationLandscapeRight</string>" \
        "    </array>" \
        "    <key>NSCameraUsageDescription</key>" \
        "    <string>Qt Multimedia Example</string>" \
        "    <key>NSMicrophoneUsageDescription</key>" \
        "    <string>Qt Multimedia Example</string>" \
        "    <key>com.apple.security.device.camera</key>" \
        "    <true/>" \
        "    <key>com.apple.security.device.microphone</key>" \
        "    <true/>" \
        "    <key>com.apple.security.device.usb</key>" \
        "    <true/>" \
        "</dict>" \
        "</plist>"
    write_file($$OUT_PWD/Info.plist, INFOPLIST)|error()
    QMAKE_INFO_PLIST = $$OUT_PWD/Info.plist
}
