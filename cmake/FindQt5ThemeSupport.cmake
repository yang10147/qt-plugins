#.rst:
# FindQt6ThemeSupport
# -------
#
# Try to find Qt6ThemeSupport on a Unix system.
#
# This will define the following variables:
#
# ``Qt6ThemeSupport_FOUND``
#     True if (the requested version of) Qt6ThemeSupport is available
# ``Qt6ThemeSupport_VERSION``
#     The version of Qt6ThemeSupport
# ``Qt6ThemeSupport_LIBRARIES``
#     This can be passed to target_link_libraries() instead of the ``Qt6ThemeSupport::Qt6ThemeSupport``
#     target
# ``Qt6ThemeSupport_INCLUDE_DIRS``
#     This should be passed to target_include_directories() if the target is not
#     used for linking
# ``Qt6ThemeSupport_DEFINITIONS``
#     This should be passed to target_compile_options() if the target is not
#     used for linking
#
# If ``Qt6ThemeSupport_FOUND`` is TRUE, it will also define the following imported target:
#
# ``Qt6ThemeSupport::Qt6ThemeSupport``
#     The Qt6ThemeSupport library
#
# In general we recommend using the imported target, as it is easier to use.
# Bear in mind, however, that if the target is in the link interface of an
# exported library, it must be made available by the package config file.

#=============================================================================
# Copyright 2014 Alex Merry <alex.merry@kde.org>
# Copyright 2014 Martin Gräßlin <mgraesslin@kde.org>
# Copyright 2016 Takahiro Hashimoto <kenya888@gmail.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#=============================================================================

if(CMAKE_VERSION VERSION_LESS 2.8.12)
    message(FATAL_ERROR "CMake 2.8.12 is required by FindQt6ThemeSupport.cmake")
endif()
if(CMAKE_MINIMUM_REQUIRED_VERSION VERSION_LESS 2.8.12)
    message(AUTHOR_WARNING "Your project should require at least CMake 2.8.12 to use FindQt6ThemeSupport.cmake")
endif()

# Use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig)
pkg_check_modules(PKG_Qt6ThemeSupport QUIET Qt6Gui)

set(Qt6ThemeSupport_DEFINITIONS ${PKG_Qt6ThemeSupport_CFLAGS_OTHER})
set(Qt6ThemeSupport_VERSION ${PKG_Qt6ThemeSupport_VERSION})

find_path(Qt6ThemeSupport_INCLUDE_DIR
    NAMES
        QtThemeSupport/private/qgenericunixthemes_p.h
    HINTS
        ${PKG_Qt6ThemeSupport_INCLUDEDIR}/QtThemeSupport/${PKG_Qt6ThemeSupport_VERSION}/
)
find_library(Qt6ThemeSupport_LIBRARY
    NAMES
        Qt6ThemeSupport
    HINTS
        ${PKG_Qt6ThemeSupport_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qt6ThemeSupport
    FOUND_VAR
        Qt6ThemeSupport_FOUND
    REQUIRED_VARS
        Qt6ThemeSupport_LIBRARY
        Qt6ThemeSupport_INCLUDE_DIR
    VERSION_VAR
        Qt6ThemeSupport_VERSION
)

if(Qt6ThemeSupport_FOUND AND NOT TARGET Qt6ThemeSupport::Qt6ThemeSupport)
    add_library(Qt6ThemeSupport::Qt6ThemeSupport UNKNOWN IMPORTED)
    set_target_properties(Qt6ThemeSupport::Qt6ThemeSupport PROPERTIES
        IMPORTED_LOCATION "${Qt6ThemeSupport_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS "${Qt6ThemeSupport_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${Qt6ThemeSupport_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(Qt6ThemeSupport_LIBRARY Qt6ThemeSupport_INCLUDE_DIR)

# compatibility variables
set(Qt6ThemeSupport_LIBRARIES ${Qt6ThemeSupport_LIBRARY})
set(Qt6ThemeSupport_INCLUDE_DIRS ${Qt6ThemeSupport_INCLUDE_DIR})
set(Qt6ThemeSupport_VERSION_STRING ${Qt6ThemeSupport_VERSION})


include(FeatureSummary)
set_package_properties(Qt6ThemeSupport PROPERTIES
    URL "http://www.qt.io"
    DESCRIPTION "Qt ThemeSupport module."
)

