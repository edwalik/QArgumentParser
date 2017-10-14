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
#ifndef QARGUMENTPARSER_QARGUMENTVALIDATOROPTION_HPP
#define QARGUMENTPARSER_QARGUMENTVALIDATOROPTION_HPP

#include <QArgumentParser/Config.hpp>
#include <QMap>

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentValidatorOption
/// \brief Defines one validator option.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 13, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QARGUMENTPARSER_API QArgumentValidatorOption
{
public:

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Defines all argument types supported as of today.
    /// \enum ArgumentType
    ///
    ////////////////////////////////////////////////////////////////////////////
    enum ArgumentType
    {
        Invalid = -1,
        Char,
        UInt8,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        String,
        File,
        Directory
    };

    QArgumentValidatorOption(const QArgumentValidatorOption& other) = default;
    QArgumentValidatorOption& operator=(const QArgumentValidatorOption& other) = default;

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new validator option with the given \p name.
    ///
    /// \param[in] option The option's identifier, without dash.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QArgumentValidatorOption(const QString& option = QString());

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the option identifier.
    ///
    /// \return The option identifier as string.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& option() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the argument name at the given \p index.
    ///
    /// \param[in] index The index of the argument name to get.
    /// \returns The argument name at \p index.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString argumentName(int index) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the type of the named argument \p arg.
    ///
    /// \param[in] The named argument.
    /// \return The type of the given argument.
    ///
    /// \remarks If QArgumentValidator::Invalid is returned, the named argument
    ///          does not exist.
    ///
    ////////////////////////////////////////////////////////////////////////////
    ArgumentType argumentType(const QString& arg) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the type of the argument at \p index.
    ///
    /// \param[in] The index of the argument.
    /// \return The type of the argument at \p index.
    ///
    /// \remarks If QArgumentValidator::Invalid is returned, the index was not
    ///          a valid index within this validator.
    ///
    ////////////////////////////////////////////////////////////////////////////
   ArgumentType argumentType(int index) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Determines whether this option is optional.
    ///
    /// \return True if optional, false if required.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool isOptional() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies whether this option should be optional. This property is
    /// 'false' by default.
    ///
    /// \param[in] optional True if optional, false if required.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setOptional(bool optional);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the option identifier of this validator option.
    ///
    /// \param[in] The option identifier, without dash.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setOption(const QString& option);

    ////////////////////////////////////////////////////////////////////////////
    /// Adds the named argument \p name with the given \p type.
    ///
    /// \param[in] name The name of the argument internally.
    /// \param[in] type The type of the argument.
    ///
    /// \remarks The type determines the validation method. A QDir or QFile type
    ///          for example will actually check whether a file or dir exists!
    ///
    ////////////////////////////////////////////////////////////////////////////
    void addArgument(const QString& name, ArgumentType type);

private:

    ////////////////////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////////////////////
    QString                     m_option;
    QMap<QString, ArgumentType> m_arguments;
    bool                        m_isOptional;

    friend class QArgumentValidator;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentValidatorOption
///
/// This class is used to specify the type of an argument. It then uses one of
/// its validation methods to validate the argument. These methods range from
/// simple conversions to actual checking of a file path.
///
/// \code
/// QArgumentValidatorOption option;
/// option.addArgument("file", QArgumentValidator::File);
/// option.addArgument("size", QArgumentValidator::Int64);
/// \endcode
///
/// Example: MyProgram -f /home/user/myfile.txt 100<br/>
/// The parser will throw an error if "/home/user/myfile.txt" does not exist.
///
////////////////////////////////////////////////////////////////////////////////
