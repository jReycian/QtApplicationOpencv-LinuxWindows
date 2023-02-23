#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include "imagecropper_p.h"
#include "imagecropper_e.h"

#include <QWidget>

class ImageCropper : public QWidget
{
    Q_OBJECT

public:
    ImageCropper(QWidget *parent = 0);
    ~ImageCropper();

public slots:
    // Set image to crop
	void setImage(const QPixmap& _image);
	// Установить цвет фона виджета обрезки
	void setBackgroundColor(const QColor& _backgroundColor);
    // Set crop widget background color
	void setCroppingRectBorderColor(const QColor& _borderColor);
    // Set selection area proportions
	void setProportion(const QSizeF& _proportion);
    // Use fixed area of ​​view proportions
	void setProportionFixed(const bool _isFixed);

public:
    // crop image
	const QPixmap cropImage();

protected:
	virtual void paintEvent(QPaintEvent* _event);
	virtual void mousePressEvent(QMouseEvent* _event);
	virtual void mouseMoveEvent(QMouseEvent* _event);
	virtual void mouseReleaseEvent(QMouseEvent* _event);

private:
    // Positioning the cursor over a widget
	CursorPosition cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition);
    // Update cursor icon to match mouse location
	void updateCursorIcon(const QPointF& _mousePosition);

	const QRectF calculateGeometry(
			const QRectF& _sourceGeometry,
			const CursorPosition _cursorPosition,
			const QPointF& _mouseDelta
            );

	const QRectF calculateGeometryWithCustomProportions(
			const QRectF& _sourceGeometry,
			const CursorPosition _cursorPosition,
			const QPointF& _mouseDelta
			);

	const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry,
												 const CursorPosition _cursorPosition,
												 const QPointF &_mouseDelta,
												 const QSizeF &_deltas
                                                 );

private:
	// Private data implementation
	ImageCropperPrivate* pimpl;
};

#endif // IMAGECROPPER_H
