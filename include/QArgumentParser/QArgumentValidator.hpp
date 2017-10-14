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
#ifndef QARGUMENTPARSER_QARGUMENTVALIDATOR_HPP
#define QARGUMENTPARSER_QARGUMENTVALIDATOR_HPP

#include <QArgumentParser/QArgumentValidatorOption.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentValidator
/// \brief Defines the structure and type of the options and their arguments.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 13, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QARGUMENTPARSER_API QArgumentValidator
{
public:

    QArgumentValidator() = default;
    QArgumentValidator(const QArgumentValidator& other) = default;
    QArgumentValidator& operator=(const QArgumentValidator& other) = default;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the amount of options.
    ///
    /// \return The amount of options.
    ///
    ////////////////////////////////////////////////////////////////////////////
    int optionCount() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the validator option at the given \p index.
    ///
    /// \param[in] index The index of the option.
    /// \return The instance of an option with the given index.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QArgumentValidatorOption optionAt(int index) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the validator option with the given \p name.
    ///
    /// \param[in] name The name of the option.
    /// \return The instance of an option with the given name.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QArgumentValidatorOption option(const QString& name) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Adds a new option for the validator to validate.
    ///
    /// \param[in] option The option to add.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void addOption(const QArgumentValidatorOption& option);

    ////////////////////////////////////////////////////////////////////////////
    /// Validates the option with the given \p name.
    ///
    /// \param[in] name The option to validate.
    /// \param[out] msg The error message.
    /// \return True if valid, false otherwise.
    ///
    ////////////////////////////////////////////////////////////////////////////
    bool validate(
        const QString& name,
        const QVector<QString>& args,
        QString* msg) const;

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////
    bool validateChar(const QString&, QString*) const;
    bool validateUChar(const QString&, QString*) const;
    bool validateShort(const QString&, QString*) const;
    bool validateUShort(const QString&, QString*) const;
    bool validateInt(const QString&, QString*) const;
    bool validateUInt(const QString&, QString*) const;
    bool validateInt64(const QString&, QString*) const;
    bool validateUInt64(const QString&, QString*) const;
    bool validateFile(const QString&, QString*) const;
    bool validateDirectory(const QString&, QString*) const;

    ////////////////////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////////////////////
    QMap<QString, QArgumentValidatorOption> m_options;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentValidator
///
/// The argument validator is the core feature of QArgumentParser, as it ensures
/// that the user provided a valid list of arguments for options.
///
/// \code
/// QArgumentValidator validator;
/// QArgumentValidatorOption option1("f");
///
/// option1.addArgument("file", QArgumentValidatorOption::File);
/// option1.addArgument("size", QArgumentValidatorOption::Int64);
/// validator.addOption(option1);
///
/// parser.setValidator(validator);
/// \endcode
///
/// In order to know how to receive the arguments with their correct types, see
/// the documentation of the ::QArgumentOption class.
///
////////////////////////////////////////////////////////////////////////////////
