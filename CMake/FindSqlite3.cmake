# Find Sqlite3
# Defines the following variables
# SQLITE3_INCLUDE_DIRS
# SQLITE3_LIBRARIES
# SQLITE3_FOUND

find_path(SQLITE3_INCLUDE_DIR sqlite3.h)

find_library(SQLITE3_LIBRARY NAMES sqlite3)

set (SQLITE3_INCLUDE_LIBRARIES ${SQLITE3_INCLUDE_DIR})
set (SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Sqlite3 DEFAULT_MSG SQLITE3_INCLUDE_DIR SQLITE3_LIBRARY)

mark_as_advanced(SQLITE3_INCLUDE_DIR SQLITE3_LIBRARY)