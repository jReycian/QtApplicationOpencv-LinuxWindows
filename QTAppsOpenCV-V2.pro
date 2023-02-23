QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += link_pkgconfig
#PKGCONFIG += opencv

TARGET = opencvtest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#remove yolov5 cpp from resources
SOURCES -= \
    src/imagedetection/yolov5.cpp \
    src/imagedetection/yolov5v2.cpp \
    src/imagedetection/yolov5v3.cpp

SOURCES += \
    imagecropperdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    src/camera/opencvcamera.cpp \
    src/imagecropper/imagecropper.cpp \
    src/imageenhancement/imageenhancement.cpp \
    src/imageenhancement/imgcontrastbrightness.cpp \
    src/imagefunction/imageconverter.cpp

#remove yolov5 h from resources
HEADERS -= \
    src/imagedetection/yolov5.h \
    src/imagedetection/yolov5v2.h \
    src/imagedetection/yolov5v3.h

HEADERS += \
    imagecropperdialog.h \
    mainwindow.h \
    src/camera/opencvcamera.h \
    src/imagecropper/imagecropper.h \
    src/imagecropper/imagecropper_e.h \
    src/imagecropper/imagecropper_p.h \
    src/imageenhancement/imageenhancement.h \
    src/imageenhancement/imgcontrastbrightness.h \
    src/imagefunction/imageconverter.h

FORMS += \
    imagecropperdialog.ui \
    mainwindow.ui \
    src/camera/opencvcamera.ui \
    src/imageenhancement/imageenhancement.ui \
    src/imageenhancement/imgcontrastbrightness.ui

############ include path for Linux environment ############

#INCLUDEPATH += .
#INCLUDEPATH += -I/usr/local/include/opencv4
#LIBS += -L/usr/local/lib \
#     -lopencv_calib3d \
#     -lopencv_core \
#     -lopencv_features2d \
#     -lopencv_flann \
#     -lopencv_highgui \
#     -lopencv_imgproc \
#     -lopencv_ml \
#     -lopencv_objdetect \
#     -lopencv_photo \
#     -lopencv_stitching \
#     -lopencv_videoio \


#LIBS += $(shell pkg-config opencv --libs)

#INCLUDEPATH += /home/minebeamisumi/Desktop/OpenCV_linux/opencv/build/include

#LIBS += -L/home/minebeamisumi/Desktop/OpenCV_linux/opencv/build/lib
#LIBS += -L/usr/local/lib\
#     -lopencv_calib3d.so.4.7.0\
#     -lopencv_contrib.so.4.7.0\
#     -lopencv_core.so.4.7.0\
#     -lopencv_features2d.so.4.7.0 \
#     -lopencv_flann.so.4.7.0\
#     -lopencv_gpu.so.4.7.0\
#     -lopencv_highgui.so.4.7.0\
#     -lopencv_imgproc.so.4.7.0\
#     -lopencv_legacy.so.4.7.0\
#     -lopencv_ml.so.4.7.0\
#     -lopencv_nonfree.so.4.7.0\
#     -lopencv_objdetect.so.4.7.0\
#     -lopencv_ocl.so.4.7.0\
#     -lopencv_photo.so.4.7.0\
#     -lopencv_stitching.so.4.7.0\
#     -lopencv_superres.so.4.7.0\
#     -lopencv_ts.so.4.7.0\
#     -lopencv_video.so.4.7.0\
#     -lopencv_videostab.so.4.7.0


###########################################################


########## include Path for Windows environment ######################

INCLUDEPATH += D:\\Nestor\\Libraries\\opencv3.4.2\\build\\include \

LIBS += -LD:\\Nestor\\Libraries\\opencv3.4.2\\build\\bin \
    libopencv_calib3d342 \
    libopencv_core342 \
    libopencv_features2d342 \
    libopencv_flann342 \
    libopencv_highgui342 \
    libopencv_imgcodecs342 \
    libopencv_imgproc342 \
    libopencv_ml342 \
    libopencv_objdetect342 \
    libopencv_photo342 \
    libopencv_shape342 \
    libopencv_stitching342 \
    libopencv_superres342 \
    libopencv_video342 \
    libopencv_videoio342 \
    libopencv_videostab342

#######################################################################

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#openvino+opencv455

#INCLUDEPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build\include
#INCLUDEPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build\include\opencv2

#unix:!macx|win32: LIBS += -L$$PWD/libraries/ \
#    -lopencv_dnn455 \
#    -lopencv_core455 \
#    -lopencv_highgui455 \
#    -lopencv_imgcodecs455 \
#    -lopencv_imgproc455 \
#    -lopencv_features2d455 \
#    -lopencv_calib3d455 \
#    -lopencv_objdetect455

#INCLUDEPATH += $$PWD/libraries
#DEPENDPATH += $$PWD/libraries

#LIBS += -LC:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\x64\vc17\lib -lopencv_core455d -lopencv_imgproc455d -lopencv_highgui455d -lopencv_imgcodecs455d -lopencv_videoio455d -lopencv_video455d -lopencv_calib3d455d -lopencv_photo455d -lopencv_features2d455d -lopencv_dnn455d
#INCLUDEPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include
#DEPENDPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include

#LIBS += -LC:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\x64\vc17\lib -lopencv_core455 -lopencv_imgproc455 -lopencv_highgui455 -lopencv_imgcodecs455 -lopencv_videoio455 -lopencv_video455 -lopencv_calib3d455 -lopencv_photo455 -lopencv_features2d455 -lopencv_dnn455
#INCLUDEPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include
#DEPENDPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include

#LIBS += -LC:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build\bin -linference_engine -linference_engine_ir_reader -linference_engine_legacy -linference_engine_lp_transformations -linference_engine_transformations
#INCLUDEPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include
#DEPENDPATH += C:\Users\MinebeaMitsumi\Desktop\GreggFolder\openvinoopencv455\opencv\build_msvc\install\include
