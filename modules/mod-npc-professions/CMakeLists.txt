#
# Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
# Licence MIT https://opensource.org/MIT
#

# Add cpp files
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/NpcProfessions_SC.cpp")

# Add scripts to script loader
AC_ADD_SCRIPT_LOADER("NpcProfessions" "${CMAKE_CURRENT_LIST_DIR}/src/NpcProfessionsLoad.h")
