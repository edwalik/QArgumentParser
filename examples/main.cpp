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
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QArgumentParser parser(argc, argv);
    QArgumentValidator validator;
    QArgumentValidatorOption file("file"), amount("amount");

    // Builds the validator.
    file.addArgument("f", QArgumentValidatorOption::File);
    amount.addArgument("s", QArgumentValidatorOption::Int64);
    validator.addOption(file);
    validator.addOption(amount);
    parser.setValidator(validator);

    // Attempts to parse the arguments.
    auto result = parser.parse();
    if (result == QArgumentParser::Failure)
    {
        qDebug().noquote() << parser.errorMessage();
    }
    else if (result == QArgumentParser::HelpRequested)
    {
        qDebug().noquote() << "Usage: QArgumentParserExample -file [file] -amount [bytecount]";
    }
    else
    {
        auto fileOption = parser.option("file");
        auto sizeOption = parser.option("amount");

        QFile*  file = fileOption.argument<QFile*>("f");
        qint64  size = sizeOption.argument<qint64>("s");
        QString base = "Reading %1 bytes from \"%0\":\n";

        file->open(QFile::ReadOnly);

        qDebug().noquote() << QString(base).arg(file->fileName(), QString::number(size));
        qDebug().noquote() << "-------- start --------";
        qDebug().noquote() << QString(file->read(size));
        qDebug().noquote() << "--------- end ---------";
    }

    return a.exec();
}
