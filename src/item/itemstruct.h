#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H

#include <QMetaType>

enum class GradientType {
        Linear = 0,
        Radial = 1
};
Q_DECLARE_METATYPE(GradientType)

//    enum class ItemType{
//        Artboard = 0,
//        Rect = 1,
//        Oval = 2,
//        Triangle = 3,
//        Star = 4,
//        Polygon = 5,
//        Line = 6,
//        Text = 7,
//        Instance = 8
//};
//Q_DECLARE_METATYPE(ItemType)


enum class StrokePosition {
	Center = 0,
	Inner = 1,
	Outer = 2
};
Q_DECLARE_METATYPE(StrokePosition)

enum class FillType {
	Color = 0,
	Image = 1,
	Gradient = 2,
	Pattern = 3
};
Q_DECLARE_METATYPE(FillType)

enum class FillMode {
	Fill = 0,
	Fit = 1,
	Stretch = 2,
	Tile = 3
};
Q_DECLARE_METATYPE(FillMode)

#endif // ITEMSTRUCT_H
