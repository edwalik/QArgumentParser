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

#include <QArgumentParser/QArgumentOption.hpp>

QArgumentOption::~QArgumentOption()
{
    for (auto* handle : m_fileHandles)
    {
        delete handle;
    }
}

const QString& QArgumentOption::option() const
{
    return m_option;
}

void QArgumentOption::setOption(const QString& option)
{
    m_option = option;
}

void QArgumentOption::addArgument(const QString& arg, const QString& value)
{
    m_arguments.insert(arg, value);
}
