////////////////////////////////////////////////////////////////////////////////
//
// QArgumentParser - Command line argument parser using the QtCore module.
// Copyright (C) 2017 Nicolas Kogler
//
// This file is part of QArgumentParser.
//
// QArgumentParser is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// QArgumentParser is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with QArgumentParser. If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef QARGUMENTPARSER_QARGUMENTOPTION_INL
#define QARGUMENTPARSER_QARGUMENTOPTION_INL

template<typename T> inline T QArgumentOption::argument(int index) const
{
    if (index < 0 || index >= m_arguments.size())
    {
        return T();
    }

    return argument<T>(m_arguments.keys().at(index));
}

template<> inline char QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].at(0).toLatin1();
}

template<> inline uchar QArgumentOption::argument(const QString& name) const
{
    return static_cast<uchar>(m_arguments[name].toUInt());
}

template<> inline short QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toShort();
}

template<> inline ushort QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toUShort();
}

template<> inline int QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toInt();
}

template<> inline uint QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toUInt();
}

template<> inline qint64 QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toLongLong();
}

template<> inline quint64 QArgumentOption::argument(const QString& name) const
{
    return m_arguments[name].toULongLong();
}

template<> inline QString QArgumentOption::argument(const QString& name) const
{
    return m_arguments.value(name);
}

template<> inline QFile* QArgumentOption::argument(const QString& name) const
{
    m_fileHandles.append(new QFile(m_arguments[name]));

    return m_fileHandles.last();
}

template<> inline QDir QArgumentOption::argument(const QString& name) const
{
    return QDir(m_arguments[name]);
}

#endif
