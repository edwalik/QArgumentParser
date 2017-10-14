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

////////////////////////////////////////////////////////////////////////////////
/// \file Config.hpp
/// \brief This header provides useful macroes for QArgumentParser.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef QARGUMENTPARSER_CONFIG_HPP
#define QARGUMENTPARSER_CONFIG_HPP

#include <QtCore>

#define MSVC_2015 1900
#define MSVC_2017 2000

#if defined(QARGUMENTPARSER_BUILD_STATIC)
    // If you want to statically link against QArgumentParser, contact a lawyer to
    // retrieve information about the LGPL and what you can do or can not do.
    #define QARGUMENTPARSER_API
#else
    #if defined(QARGUMENTPARSER_BUILD_SHARED)
        // Export symbols to shared library.
        #define QARGUMENTPARSER_API Q_DECL_EXPORT
    #else
        // Import symbols to link symbols.
        #define QARGUMENTPARSER_API Q_DECL_IMPORT
    #endif
#endif

#if defined(Q_CC_MSVC) && Q_CC_MSVC < MSVC_2015
    // MSVC is missing some C++11 keywords.
    #define QARGUMENTPARSER_NOEXCEPT
    #define QARGUMENTPARSER_CONSTEXPR const
#else
    #define QARGUMENTPARSER_NOEXCEPT noexcept
    #define QARGUMENTPARSER_CONSTEXPR constexpr
#endif

// Snippets put into the anonymous namespace.
#define Anonymous(...) namespace { __VA_ARGS__; }

#endif
