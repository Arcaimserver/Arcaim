#
# Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
# Licence MIT https://opensource.org/MIT
#

# Set global dir
CU_SET_PATH("KARGATUM_SYSTEM_DIR" "${CMAKE_CURRENT_LIST_DIR}")

# Set dir
set(KARGATUM_LIB_DIR    "${CMAKE_CURRENT_LIST_DIR}/src/Kargatum-lib")
set(KARGATUM_SC_DIR     "${CMAKE_CURRENT_LIST_DIR}/src")
set(KARGATUM_CONF_DIR   "${CMAKE_CURRENT_LIST_DIR}/conf")

message("-> Loading Kargatum System")

# Add kargatum lib
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumConfig.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumConfig.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumLoadSystem.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumLoadSystem.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumScripts.cpp")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumScripts.h")
AC_ADD_SCRIPT("${KARGATUM_LIB_DIR}/LibKargatumLanguage.h")

# Add cpp files
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-anti-advertisment/KargatumAntiAdvertisment.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-auto-revive/KargatumAutoRevive.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-bg-reward/KargatumBGReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-buff-command/KargatumBuffCommand.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-faction-icons-channel/KargatumIconFaction.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-gm-chat-color/KargatumGmChatColor.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-level-reward/KargatumLevelReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-notify-muted/KargatumPlayerNotSpeak.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-online-reward/KargatumOnlineReward.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-player-info-login/KargatumPlayerInfoLogin.cpp")
AC_ADD_SCRIPT("${KARGATUM_SC_DIR}/mod-spell-duration/KargatumSpellDuration.cpp")

# Add scripts to script loader
AC_ADD_SCRIPT_LOADER("Kargatum" "${CMAKE_CURRENT_LIST_DIR}/src/KargatumSCLoad.h")

# Add config file
AC_ADD_CONFIG_FILE("${KARGATUM_CONF_DIR}/KargatumSystem.conf.dist")
