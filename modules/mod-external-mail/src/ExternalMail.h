/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#ifndef _DUNGEON_BUFF_H_
#define _DUNGEON_BUFF_H_

#include "Common.h"
#include "Player.h"
#include <unordered_map>
#include <vector>

class ExternalMail
{
public:
    static ExternalMail* instance();

    // Config load
    void LoadConfig();

    // Manage system
    void SendMails();
    uint32 GetCheckTimeInterval();
    bool IsSystemEnable();

private:
    
    // From config
    bool _IsEnableSystem;
    uint32 _IntervalTime;
};

#define sEM ExternalMail::instance()

#endif // _DUNGEON_BUFF_H_
