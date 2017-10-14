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

#include <QArgumentParser/QArgumentParser.hpp>

QArgumentParser::QArgumentParser(int argc, char* argv[])
    : m_optionIndicator("-")
{
    m_firstArgument = QString(argv[0]);

    // Ignores the first argument.
    for (int i = 1; i < argc; i++)
    {
        m_arguments.append(QString(argv[i]));
    }
}

const QString& QArgumentParser::firstArgument() const
{
    return m_firstArgument;
}

const QArgumentOption QArgumentParser::option(const QString& name) const
{
    return m_options.value(name, m_defaultOption);
}

const QArgumentValidator& QArgumentParser::validator() const
{
    return m_validator;
}

const QString& QArgumentParser::optionIndicator() const
{
    return m_optionIndicator;
}

const QString& QArgumentParser::errorMessage() const
{
    return m_errorMessage;
}

void QArgumentParser::setValidator(const QArgumentValidator& validator)
{
    m_validator = validator;
}

void QArgumentParser::setOptionIndicator(const QString& indicator)
{
    if (indicator.isEmpty())
        m_optionIndicator = "-";
    else
        m_optionIndicator = indicator;
}

QArgumentParser::ResultType QArgumentParser::parse()
{
    // We could potentially get errors when having zero arguments.
    if (m_arguments.size() == 0)
    {
        return HelpRequested;
    }

    bool mustValidate = m_validator.optionCount() > 0;

    QString currentOption;
    QVector<QString> currentArgs;

    // Builds the option <> argument tree.
    for (int i = 0; i < m_arguments.size(); i++)
    {
        auto current = m_arguments.at(i).trimmed();
        if (current.startsWith(m_optionIndicator))
        {
            current = current.mid(m_optionIndicator.size());

            // TODO: Variable help identifier?
            if (current == "h")
            {
                return HelpRequested;
            }

            // Current option changed, validate the old option.
            if (!currentOption.isEmpty())
            {
                if (mustValidate)
                {
                    if (!m_validator.validate(currentOption, currentArgs, &m_errorMessage))
                        return Failure;
                }

                // Now that the validation is complete, we can add the option.
                // Warning: Without a validator, this will always be the case!
                insertOption(currentOption, currentArgs);
            }

            currentOption = current;
            currentArgs.clear();
        }
        else if (!current.isEmpty())
        {
            currentArgs.append(current);
        }
    }

    // Validates the last remaining option.
    if (mustValidate)
    {
        if (!m_validator.validate(currentOption, currentArgs, &m_errorMessage))
            return Failure;
    }

    insertOption(currentOption, currentArgs);

    // Required options must be provided.
    if (isMissingRequired(&m_errorMessage))
    {
        return Failure;
    }

    return Success;
}

void QArgumentParser::insertOption(const QString& opt, const QVector<QString>& args)
{
    QArgumentOption option;

    for (int i = 0; i < args.size(); i++)
    {
        // If the validator is invalid, option() will return an invalid option
        // and invalid options by default have null identifiers. Therefore we
        // do not have to check whether the validator is valid first.
        option.addArgument(m_validator.option(opt).argumentName(i), args.at(i));
    }

    m_options.insert(opt, option);
}

bool QArgumentParser::isMissingRequired(QString* msg)
{
    for (int i = 0; i < m_validator.optionCount(); i++)
    {
        auto opt = m_validator.optionAt(i);
        if (!opt.isOptional() && !m_options.contains(opt.option()))
        {
            *msg = QString("Missing required option \"%0\".").arg(opt.option());
            return true;
        }
    }

    return false;
}
