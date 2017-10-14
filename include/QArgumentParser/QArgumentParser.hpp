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
#ifndef QARGUMENTPARSER_QARGUMENTPARSER_HPP
#define QARGUMENTPARSER_QARGUMENTPARSER_HPP

#include <QArgumentParser/QArgumentOption.hpp>
#include <QArgumentParser/QArgumentValidator.hpp>

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentParser
/// \brief Parses arguments from the command line.
/// \author Nicolas Kogler (nicolas.kogler@hotmail.com)
/// \date October 13, 2017
///
////////////////////////////////////////////////////////////////////////////////
class QARGUMENTPARSER_API QArgumentParser
{
public:

    enum ResultType
    {
        Success,
        Failure,
        HelpRequested
    };

    QArgumentParser(const QArgumentParser& other);
    QArgumentParser& operator=(const QArgumentParser& other);

    ////////////////////////////////////////////////////////////////////////////
    /// Initializes a new argument parser with the given argument count and
    /// argument array. Note that you are required to pass the exact parameters
    /// of 'int main(int argc, char* argv[])' to this constructor.
    ///
    /// \param[in] argc The argument count.
    /// \param[in] argv The arguments themselves.
    ///
    /// \remarks The first argument will not be parsed, but can be retrieved via
    ///          QArgumentParser::firstArgument.
    ///
    ////////////////////////////////////////////////////////////////////////////
    QArgumentParser(int argc, char* argv[]);

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the first argument (argv[0]).
    ///
    /// \return The first argument (usually the executable path).
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& firstArgument() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the option with the given \p name. This function will solely
    /// return invalid QArgumentOption instances before QArgumentParser::parse
    /// was called.
    ///
    /// \param[in] option The option to retrieve.
    /// \return The option with the given name.
    ///
    /// \remarks Determine whether the option is invalid by checking
    ///          QArgumentOption::option against a null QString.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QArgumentOption option(const QString& name) const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the validator of this parser.
    ///
    /// \return The validator.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QArgumentValidator& validator() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the option indicator. By default, this is a dash ('-').
    ///
    /// \return The option indicator.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& optionIndicator() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Retrieves the error message along with result QArgumentParser::Failure.
    ///
    /// \return The error message.
    ///
    ////////////////////////////////////////////////////////////////////////////
    const QString& errorMessage() const;

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies a new validator for the options and their arguments. In order
    /// to guarantee type safety and validity, one must use a validator.
    ///
    /// \param[in] validator The new validator to use.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setValidator(const QArgumentValidator& validator);

    ////////////////////////////////////////////////////////////////////////////
    /// Specifies the option indicator. By default, this is a dash ('-'). Users
    /// developing Windows-only applications may use a slash ('/') or something
    /// else.
    ///
    /// \param[in] indicator The new option indicator.
    ///
    ////////////////////////////////////////////////////////////////////////////
    void setOptionIndicator(const QString& indicator);

    ////////////////////////////////////////////////////////////////////////////
    /// Attempts to parse all the options and arguments according to the rules
    /// specified by a validator set through QArgumentParser::setValidator.
    ///
    /// \return The type of the result.
    ///
    /// \remarks In case the return value is QArgumentParser::Failure, retrieve
    ///          the error message by calling QArgumentParser::errorMessage in
    ///          order to get the exact cause of the failure.
    ///
    ////////////////////////////////////////////////////////////////////////////
    ResultType parse();

private:

    ////////////////////////////////////////////////////////////////////////////
    // Functions
    ////////////////////////////////////////////////////////////////////////////
    void insertOption(const QString&, const QVector<QString>&);
    bool isMissingRequired(QString*);

    ////////////////////////////////////////////////////////////////////////////
    // Members
    ////////////////////////////////////////////////////////////////////////////
    QVector<QString>               m_arguments;
    QArgumentValidator             m_validator;
    QArgumentOption                m_defaultOption;
    QMap<QString, QArgumentOption> m_options;
    QString                        m_optionIndicator;
    QString                        m_firstArgument;
    QString                        m_errorMessage;
};

#endif

////////////////////////////////////////////////////////////////////////////////
/// \class QArgumentParser
///
/// This class parses the command line arguments and validates them on request.
/// Use it as follows:
///
/// \code
/// QArgumentParser parser(argc, argv);
/// QArgumentValidator validator;
/// QArgumentValidatorOption file("file"), amount("amount");
///
/// // Builds the validator.
/// file.addArgument("f", QArgumentValidatorOption::File);
/// amount.addArgument("s", QArgumentValidatorOption::Int64);
/// validator.addOption(file);
/// validator.addOption(amount);
/// parser.setValidator(validator);
///
/// // Attempts to parse the arguments.
/// auto result = parser.parse();
/// if (result == QArgumentParser::Failure)
/// {
///     qDebug().noquote() << parser.errorMessage();
/// }
/// else if (result == QArgumentParser::HelpRequested)
/// {
///     qDebug().noquote() << "Usage: [...]";
/// }
/// else
/// {
///     // [process the file]
/// }
/// \endcode
///
////////////////////////////////////////////////////////////////////////////////
