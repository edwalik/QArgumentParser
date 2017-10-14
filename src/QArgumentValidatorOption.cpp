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

#include <QArgumentParser/QArgumentValidator.hpp>
#include <QArgumentParser/QArgumentValidatorOption.hpp>

QArgumentValidatorOption::QArgumentValidatorOption(const QString& option)
    : m_option(option)
    , m_isOptional(false)
{
}

const QString& QArgumentValidatorOption::option() const
{
    return m_option;
}

const QString QArgumentValidatorOption::argumentName(int index) const
{
    if (index < 0 || index >= m_arguments.keys().size())
    {
        return QString();
    }

    return m_arguments.keys().at(index);
}

QArgumentValidatorOption::ArgumentType QArgumentValidatorOption::argumentType(
    const QString &arg) const
{
    return m_arguments.value(arg, QArgumentValidatorOption::Invalid);
}

QArgumentValidatorOption::ArgumentType QArgumentValidatorOption::argumentType(
    int index) const
{
    if (index < 0 || index >= m_arguments.values().size())
    {
        return QArgumentValidatorOption::Invalid;
    }

    return m_arguments.values().at(index);
}

bool QArgumentValidatorOption::isOptional() const
{
    return m_isOptional;
}

void QArgumentValidatorOption::setOptional(bool optional)
{
    m_isOptional = optional;
}

void QArgumentValidatorOption::setOption(const QString& option)
{
    m_option = option;
}

void QArgumentValidatorOption::addArgument(const QString& name, ArgumentType type)
{
    m_arguments.insert(name, type);
}
