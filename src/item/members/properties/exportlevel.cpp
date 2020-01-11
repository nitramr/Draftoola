#include "exportlevel.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

ExportLevel::ExportLevel() : ExportLevel(-1, 1.0){}

/*!
 * \brief Exportlevel for item rendering.
 * \param id
 * \param level
 * \param fileFormat
 * \param path
 * \param pathType
 */
ExportLevel::ExportLevel(int id, double level, ExportLevel::FileFormat fileFormat, QString path, ExportLevel::PathType pathType)
{
    setID(id);
    setPathType(pathType);
    setPath(path);
    setRenderLevel(level);
    setFileFormat(fileFormat);
}

ExportLevel::ExportLevel(const ExportLevel &other)
{
    m_id = other.m_id;
    m_renderLevel = other.m_renderLevel;
    m_fileFormat = other.m_fileFormat;
    m_path = other.m_path;
    m_pathType = other.m_pathType;
}



/***************************************************
 *
 * Properties
 *
 ***************************************************/

void ExportLevel::setID(int id)
{
    m_id = id;
}

int ExportLevel::ID() const
{
    return m_id;
}


void ExportLevel::setRenderLevel(double level)
{
    m_renderLevel = level;

    if(path().isEmpty()){
        m_path = "@" + QString::number(level) + "x";
    }
}

double ExportLevel::renderLevel() const
{
    return m_renderLevel;
}

void ExportLevel::setPath(QString path)
{
    m_path = path;
}

QString ExportLevel::path() const
{
    return m_path;
}

void ExportLevel::setFileFormat(ExportLevel::FileFormat fileFormat)
{
    m_fileFormat = fileFormat;
}

ExportLevel::FileFormat ExportLevel::fileFormat() const
{
    return m_fileFormat;
}

void ExportLevel::setPathType(ExportLevel::PathType pathType)
{
    m_pathType = pathType;
}

ExportLevel::PathType ExportLevel::pathType() const
{
    return m_pathType;
}

/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool ExportLevel::operator==(const ExportLevel &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_renderLevel == other.m_renderLevel &&
            m_fileFormat == other.m_fileFormat &&
            m_path == other.m_path &&
            m_pathType == other.m_pathType;
}

QDebug operator<<(QDebug dbg, const ExportLevel &obj)
{
    dbg << "ExportLevel("
        << obj.ID()
        << obj.renderLevel()
        << (int)obj.fileFormat()
        << (int)obj.pathType()
        << obj.path()
        << ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const ExportLevel &obj)
{
    out << obj.ID()
        << obj.renderLevel()
        << (int)obj.fileFormat()
        << (int)obj.pathType()
        << obj.path();

    return out;
}

QDataStream &operator>>(QDataStream &in, ExportLevel &obj)
{
    int id;
    double renderLevel;
    int fileFormat;
    int pathType;
    QString path;

    in >> id >> renderLevel >> fileFormat >> pathType >> path;

    obj.m_id = id;
    obj.m_renderLevel = renderLevel;
    obj.m_fileFormat = ExportLevel::FileFormat(fileFormat);
    obj.m_pathType = ExportLevel::PathType(pathType);
    obj.m_path = path;

    return in;
}
