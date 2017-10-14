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

#pragma once
#ifndef QARGUMENTPARSER_QARGUMENTOPTION_HPP
#define QARGUMENTPARSER_QARGUMENTOPTION_HPP

#include <QArgumentParser/Config.hpp>

#include <QDir>
#include <QFile>
#include <QMap>
#include <QVector>

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentOption
/// \brief Defines one option and all its arguments.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 13, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QARGUMENTPARSER_API QArgumentOption
{
public:

    QArgumentOption() = default;
   ~QArgumentOption();
    QArgumentOption(const QArgumentOption& other) = default;
    QArgumentOption& operator=(const QArgumentOption& other) = default;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the option of this instance as string.
    ///
    /// \return The option.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& option() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the argument at the given \p index, with the specified type.
    /// Supported types as of today: char, uchar, short, ushort, int, uint,
    /// qint64, quint64, QString, QFile, QDir.
    ///
    /// It is recommended to use the QArgumentValidator in order to ensure that
    /// the argument is converted successfully.
    ///
    /// \param[in] index Index of the argument.
    /// \return An instance of the specified template type.
    ///
    /// \remarks Passing QFile as template argument will return a valid file
    ///          handle to the user-specified file. One still needs to open it
    ///          with the desired OpenMode, though.
    ///
    ////////////////////////////////////////////////////////////////////////////
    template<typename T> T argument(int index) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the named argument called \p name with the specified type.
    /// Supported types as of today: char, uchar, short, ushort int, uint,
    /// qint64, quint64, QString, QFile, QDir.
    ///
    /// It is required to use a QArgumentValidator in order to have named
    /// arguments.
    ///
    /// \param name[in] The name of the argument from a QArgumentValidatorOption.
    /// \return An instance of the specified template type.
    ///
    /// \remarks Passing QFile as template argument will return a valid file
    ///          handle to the user-specified file. One still needs to open it
    ///          with the desired OpenMode, though.
    ///
    ////////////////////////////////////////////////////////////////////////////
    template<typename T> T argument(const QString& name) const;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////
    void setOption(const QString&);
    void addArgument(const QString&, const QString&);

    ////////////////////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////////////////////
    QString                 m_option;
    QMap<QString, QString>  m_arguments;
    mutable QVector<QFile*> m_fileHandles;

    friend class QArgumentParser;
};

// Template specializations
#include "QArgumentOption.inl"

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentOption
///
/// The QArgumentOption class is capable of directly converting arguments to
/// their desired type. It is recommended to use a QArgumentValidator to parse
/// the command line arguments in order to have named arguments and a type
/// validation.
///
/// \code
/// if (argumentParser.parse() == QArgumentParser::Success)
/// {
///     QArgumentOption file = argumentParser["f"];
///     QFile* handle  = file.argument<QFile*>("path");
///     qint64 toRead = file.argument<qint64>("size");
///
///     handle->open(QFile::ReadOnly);
///
///     // process 'handle' and read 'toRead' amount of bytes/characters
///     // if used with a QArgumentValidator, the 'handle' is valid for sure
/// }
/// \endcode
///
/// Note: Since QFile does unfortunately not support copy construction, it must
/// be retrieved as a pointer. You do not need to delete it, though, because the
/// QArgumentOption class handles it.
///
////////////////////////////////////////////////////////////////////////////////
