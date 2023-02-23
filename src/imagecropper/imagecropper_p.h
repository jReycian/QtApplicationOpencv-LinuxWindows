#ifndef IMAGECROPPER_P_H
#define IMAGECROPPER_P_H

#include "imagecropper_e.h"

#include <QtCore/QRect>
#include <QtGui/QPixmap>
#include <QtGui/QColor>

namespace {
	const QRect INIT_CROPPING_RECT = QRect();
	const QSizeF INIT_PROPORTION = QSizeF(1.0, 1.0);
}

class ImageCropperPrivate {
public:
	ImageCropperPrivate() :
		imageForCropping(QPixmap()),
		croppingRect(INIT_CROPPING_RECT),
		lastStaticCroppingRect(QRect()),
		cursorPosition(CursorPositionUndefined),
		isMousePressed(false),
		isProportionFixed(false),
		startMousePos(QPoint()),
		proportion(INIT_PROPORTION),
        deltas(INIT_PROPORTION),
		backgroundColor(Qt::black),
		croppingRectBorderColor(Qt::white)
	{}

public:
    // Image to crop
	QPixmap imageForCropping;
    // crop area
	QRectF croppingRect;
    // Last fixed crop area
	QRectF lastStaticCroppingRect;
    // Cursor position relative to crop area
	CursorPosition cursorPosition;
    // Is the left mouse button pressed
	bool isMousePressed;
    // Lock the aspect ratio of the crop area
	bool isProportionFixed;
    // Initial cursor position when resizing the crop area
	QPointF startMousePos;
    // Proportions
	QSizeF proportion;
    // Increments
    // width  - increment by x
    // height - increment by y
    QSizeF deltas;
    // background fill color below image
	QColor backgroundColor;
    // Crop area frame color
	QColor croppingRectBorderColor;
};

#endif // IMAGECROPPER_P_H
