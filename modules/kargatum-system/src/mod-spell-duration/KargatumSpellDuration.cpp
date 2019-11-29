/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/LibKargatumConfig.h"
#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "../Kargatum-lib/LibKargatumScripts.h"
#include "ScriptMgr.h"

class KargatumSpellDuration : public PlayerScript
{
public:
    KargatumSpellDuration() : PlayerScript("KargatumSpellDuration") {}	
};

void AddSC_Kargatum_SpellDuration()
{
	new KargatumSpellDuration();
}
