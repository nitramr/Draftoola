#include "exportlevel.h"
#include <QDebug>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

ExportLevel::ExportLevel() : ExportLevel(-1.0, 1){}

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

//    qDebug() << this->staticMetaObject.className();
}

ExportLevel::ExportLevel(const ExportLevel &other)
{
    m_id = other.m_id;
    m_renderLevel = other.m_renderLevel;
    m_fileFormat = other.m_fileFormat;
    m_path = other.m_path;
    m_pathType = other.m_pathType;
}

bool ExportLevel::operator==(const ExportLevel &other) const
{
    if(this == &other) return true;

    return m_id == other.m_id &&
            m_renderLevel == other.m_renderLevel &&
            m_fileFormat == other.m_fileFormat &&
            m_path == other.m_path &&
            m_pathType == other.m_pathType;
}

void ExportLevel::setID(int id)
{
    m_id = id;
}

int ExportLevel::ID() const
{
    return m_id;
}

QDebug operator<<(QDebug dbg, const ExportLevel &exportLevel)
{
    int fType = QVariant::fromValue(exportLevel.fileFormat()).value<int>();
    int pType = QVariant::fromValue(exportLevel.pathType()).value<int>();


    dbg << "ExportLevel("  <<
           "ID:" << exportLevel.ID() <<
           ", RenderLevel:" << exportLevel.renderLevel() <<
           ", FileFormat:" << fType <<
           ", PathType:" << pType <<
           ", Path:" << exportLevel.path() <<
           ")";
    return dbg.maybeSpace();
}

/***************************************************
 *
 * Properties
 *
 ***************************************************/

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

