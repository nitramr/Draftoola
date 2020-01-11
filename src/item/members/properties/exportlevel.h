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
