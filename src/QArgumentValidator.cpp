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

Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_01 = "Invalid option \"%0\".")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_02 = "Invalid argument count for option \"%0\". Expected: %1. Got %2.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_03 = "Argument at index %0 does not exist. File an issue on Github!")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_04 = "Argument \"%0\" is not of type 'char'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_05 = "Argument \"%0\" is not of type 'unsigned char'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_06 = "Argument \"%0\" is not of type 'short'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_07 = "Argument \"%0\" is not of type 'unsigned short'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_08 = "Argument \"%0\" is not of type 'int'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_09 = "Argument \"%0\" is not of type 'unsigned int'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_10 = "Argument \"%0\" is not of type 'long long'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_11 = "Argument \"%0\" is not of type 'unsigned long long'.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_12 = "File at \"%0\" does not exist.")
Anonymous(QARGUMENTPARSER_CONSTEXPR auto e_13 = "Directory at \"%0\" does not exist.")

int QArgumentValidator::optionCount() const
{
    return m_options.count();
}

QArgumentValidatorOption QArgumentValidator::optionAt(int index) const
{
    if (index < 0 || index >= m_options.values().size())
    {
        return QArgumentValidatorOption();
    }

    return m_options.values().at(index);
}

QArgumentValidatorOption QArgumentValidator::option(const QString& name) const
{
    return m_options.value(name);
}

void QArgumentValidator::addOption(const QArgumentValidatorOption& option)
{
    m_options.insert(option.option(), option);
}

bool QArgumentValidator::validate(
    const QString& name,
    const QVector<QString>& args,
    QString* msg) const
{
    QArgumentValidatorOption opt = option(name);

    // Option and argument count validation.
    if (opt.option().isEmpty())
    {
        *msg = QString(e_01).arg(name);
        return false;
    }
    else if (opt.m_arguments.size() != args.size())
    {
        *msg = QString(e_02).arg(name,
            QString::number(args.size()),
            QString::number(opt.m_arguments.size()));

        return false;
    }

    // Validates every argument itself.
    for (int i = 0; i < args.size(); i++)
    {
        auto arg = args.at(i);
        auto result = true;

        // ! Expand when supporting new types !
        switch (opt.argumentType(i))
        {
            case QArgumentValidatorOption::Invalid:
                result = false;
               *msg = QString(e_03).arg(QString::number(i));
                break;

            case QArgumentValidatorOption::Char:
                result = validateChar(arg, msg);
                break;

            case QArgumentValidatorOption::UInt8:
                result = validateUChar(arg, msg);
                break;

            case QArgumentValidatorOption::Int16:
                result = validateShort(arg, msg);
                break;

            case QArgumentValidatorOption::UInt16:
                result = validateUShort(arg, msg);
                break;

            case QArgumentValidatorOption::Int32:
                result = validateInt(arg, msg);
                break;

            case QArgumentValidatorOption::UInt32:
                result = validateUInt(arg, msg);
                break;

            case QArgumentValidatorOption::Int64:
                result = validateInt64(arg, msg);
                break;

            case QArgumentValidatorOption::UInt64:
                result = validateUInt64(arg, msg);
                break;

            case QArgumentValidatorOption::File:
                result = validateFile(arg, msg);
                break;

            case QArgumentValidatorOption::Directory:
                result = validateDirectory(arg, msg);
                break;

            default:
                break;
        }

        if (result != true)
        {
            return false;
        }
    }

    return true;
}

bool QArgumentValidator::validateChar(const QString &s, QString *msg) const
{
    auto unicode = s.at(0).unicode(); // ensured to be not empty!
    if (unicode < 32 || unicode > 127)
    {
        *msg = QString(e_04).arg(s);
        return false;
    }

    return true;
}

bool QArgumentValidator::validateUChar(const QString& s, QString* msg) const
{
    auto result = false;
    auto byte = s.toInt(&result);
    if (!result || (byte < 0 || byte > 255))
    {
        *msg = QString(e_05).arg(s);
        return false;
    }

    return true;
}

bool QArgumentValidator::validateShort(const QString& s, QString* msg) const
{
    auto result = false; s.toShort(&result);
    if (!result)
    {
        *msg = QString(e_06).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateUShort(const QString& s, QString* msg) const
{
    auto result = false; s.toUShort(&result);
    if (!result)
    {
        *msg = QString(e_07).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateInt(const QString& s, QString* msg) const
{
    auto result = false; s.toInt(&result);
    if (!result)
    {
        *msg = QString(e_08).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateUInt(const QString& s, QString* msg) const
{
    auto result = false; s.toUInt(&result);
    if (!result)
    {
        *msg = QString(e_09).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateInt64(const QString& s, QString* msg) const
{
    auto result = false; s.toLongLong(&result);
    if (!result)
    {
        *msg = QString(e_10).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateUInt64(const QString& s, QString* msg) const
{
    auto result = false; s.toULongLong(&result);
    if (!result)
    {
        *msg = QString(e_11).arg(s);
    }

    return result;
}

bool QArgumentValidator::validateFile(const QString& s, QString* msg) const
{
    if (!QFileInfo(s).exists())
    {
        *msg = QString(e_12).arg(s);
        return false;
    }

    return true;
}

bool QArgumentValidator::validateDirectory(const QString& s, QString* msg) const
{
    if (!QDir(s).exists())
    {
        *msg = QString(e_13).arg(s);
        return false;
    }

    return true;
}
