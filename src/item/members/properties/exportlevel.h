/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#ifndef EXPORTLEVEL_H
#define EXPORTLEVEL_H

#include <QString>
#include <QDebug>
#include <QDataStream>


class ExportLevel
{

public:

    enum FileFormat{
        JPG = 0,
        PNG = 1,
        SVG = 2,
        PDF = 3
    };

    enum PathType{
        prefix = 0,
        suffix = 1
    };

    ExportLevel();
    ExportLevel(int id, double level, FileFormat fileFormat = FileFormat::PNG, QString path = "", PathType pathType = PathType::suffix);
    ExportLevel(const ExportLevel &other);
    //    virtual ~ExportLevel(){}

    bool operator==( const ExportLevel & other ) const;
    inline bool operator!=(const ExportLevel &exportLevel) const { return !(operator==(exportLevel)); }
    friend QDataStream &operator<<(QDataStream &out, const ExportLevel &obj);
    friend QDataStream &operator>>(QDataStream &in, ExportLevel &obj);

#ifndef QT_NO_DEBUG_STREAM
    friend QDebug operator<<(QDebug dbg, const ExportLevel &obj);
#endif

    void setID(int id);
    int ID() const;

    void setRenderLevel(double level);
    double renderLevel () const;

    void setPath(QString path);
    QString path() const;

    void setFileFormat(FileFormat fileFormat);
    FileFormat fileFormat() const;

    void setPathType(PathType pathType);
    PathType pathType() const;


private:
    int m_id;
    double m_renderLevel;
    QString m_path;
    FileFormat m_fileFormat;
    PathType m_pathType;

};

Q_DECLARE_METATYPE(ExportLevel)
Q_DECLARE_METATYPE(ExportLevel::FileFormat)
Q_DECLARE_METATYPE(ExportLevel::PathType)


#endif // EXPORTLEVEL_H
