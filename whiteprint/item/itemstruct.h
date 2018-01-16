#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H


enum class GradientType {
	Linear = 0,
	Radial = 1
};

enum class ItemType {
	Rect = 0,
	Oval = 1,
	Triangle = 2,
	Star = 3,
	Polygon = 4,
	Line = 5,
	Text = 6,
	Instance = 7
};

enum class StrokePosition {
	Center = 0,
	Inner = 1,
	Outer = 2
};

#endif // ITEMSTRUCT_H
