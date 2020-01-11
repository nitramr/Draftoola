#ifndef ITEMSTRUCT_H
#define ITEMSTRUCT_H

#include <QMetaType>

enum class FillType {
    Color = 0,
    Image = 1,
    LinearGradient = 2,
    RadialGradient = 3,
    ConicalGradient = 4,
    Pattern = 5

};
Q_DECLARE_METATYPE(FillType)


#endif // ITEMSTRUCT_H
