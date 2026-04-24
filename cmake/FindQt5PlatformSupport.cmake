#.rst:
# FindQt6PlatformSupport
# -------
#
# Try to find Qt6PlatformSupport on a Unix system.
#
# This will define the following variables:
#
# ``Qt6PlatformSupport_FOUND``
#     True if (the requested version of) Qt6PlatformSupport is available
# ``Qt6PlatformSupport_VERSION``
#     The version of Qt6PlatformSupport
# ``Qt6PlatformSupport_LIBRARIES``
#     This can be passed to target_link_libraries() instead of the ``Qt6PlatformSupport::Qt6PlatformSupport``
#     target
# ``Qt6PlatformSupport_INCLUDE_DIRS``
#     This should be passed to target_include_directories() if the target is not
#     used for linking
# ``Qt6PlatformSupport_DEFINITIONS``
#     This should be passed to target_compile_options() if the target is not
#     used for linking
#
# If ``Qt6PlatformSupport_FOUND`` is TRUE, it will also define the following imported target:
#
# ``Qt6PlatformSupport::Qt6PlatformSupport``
#     The Qt6PlatformSupport library
#
# In general we recommend using the imported target, as it is easier to use.
# Bear in mind, however, that if the target is in the link interface of an
# exported library, it must be made available by the package config file.

#=============================================================================
# Copyright 2014 Alex Merry <alex.merry@kde.org>
# Copyright 2014 Martin Gräßlin <mgraesslin@kde.org>
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
    message(FATAL_ERROR "CMake 2.8.12 is required by FindQt6PlatformSupport.cmake")
endif()
if(CMAKE_MINIMUM_REQUIRED_VERSION VERSION_LESS 2.8.12)
    message(AUTHOR_WARNING "Your project should require at least CMake 2.8.12 to use FindQt6PlatformSupport.cmake")
endif()

# Use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
find_package(PkgConfig)
pkg_check_modules(PKG_Qt6PlatformSupport QUIET Qt6Gui)

set(Qt6PlatformSupport_DEFINITIONS ${PKG_Qt6PlatformSupport_CFLAGS_OTHER})
set(Qt6PlatformSupport_VERSION ${PKG_Qt6PlatformSupport_VERSION})

find_path(Qt6PlatformSupport_INCLUDE_DIR
    NAMES
        QtPlatformSupport/private/qfontconfigdatabase_p.h
    HINTS
        ${PKG_Qt6PlatformSupport_INCLUDEDIR}/QtPlatformSupport/${PKG_Qt6PlatformSupport_VERSION}/
)
find_library(Qt6PlatformSupport_LIBRARY
    NAMES
        Qt6PlatformSupport
    HINTS
        ${PKG_Qt6PlatformSupport_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Qt6PlatformSupport
    FOUND_VAR
        Qt6PlatformSupport_FOUND
    REQUIRED_VARS
        Qt6PlatformSupport_LIBRARY
        Qt6PlatformSupport_INCLUDE_DIR
    VERSION_VAR
        Qt6PlatformSupport_VERSION
)

if(Qt6PlatformSupport_FOUND AND NOT TARGET Qt6PlatformSupport::Qt6PlatformSupport)
    add_library(Qt6PlatformSupport::Qt6PlatformSupport UNKNOWN IMPORTED)
    set_target_properties(Qt6PlatformSupport::Qt6PlatformSupport PROPERTIES
        IMPORTED_LOCATION "${Qt6PlatformSupport_LIBRARY}"
        INTERFACE_COMPILE_OPTIONS "${Qt6PlatformSupport_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${Qt6PlatformSupport_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(Qt6PlatformSupport_LIBRARY Qt6PlatformSupport_INCLUDE_DIR)

# compatibility variables
set(Qt6PlatformSupport_LIBRARIES ${Qt6PlatformSupport_LIBRARY})
set(Qt6PlatformSupport_INCLUDE_DIRS ${Qt6PlatformSupport_INCLUDE_DIR})
set(Qt6PlatformSupport_VERSION_STRING ${Qt6PlatformSupport_VERSION})


include(FeatureSummary)
set_package_properties(Qt6PlatformSupport PROPERTIES
    URL "http://www.qt.io"
    DESCRIPTION "Qt PlatformSupport module."
)

