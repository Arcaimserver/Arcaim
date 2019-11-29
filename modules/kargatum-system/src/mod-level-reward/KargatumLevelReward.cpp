/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/LibKargatumConfig.h"
#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "../Kargatum-lib/LibKargatumScripts.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "LootMgr.h"
#include "World.h"

class KargatumLevelReward : public PlayerScript
{
public:
    KargatumLevelReward() : PlayerScript("KargatumLevelReward") { }

    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        if (!CONF_BOOL(conf::LEVEL_REWARD_ENABLE))
            return;

        uint8 PlayerLevel = player->getLevel();
        int32 Diff = PlayerLevel - oldLevel;

        if (Diff <= 0 || PlayerLevel == 1)
            return;

        while (Diff)
        {
            RewardForLevel(player, PlayerLevel + 1 - Diff);
            Diff--;
        }
    }

private:
    LevelReward const* GetLevelReward(uint32 Level)
    {
        KargatumLoad::LevelRewardContainer& _store = sKargatumLoad->GetRewardLevel();
        KargatumLoad::LevelRewardContainer::const_iterator itr = _store.find(Level);
        if (itr != _store.end())
            return &(itr->second);

        return nullptr;
    }

    void RewardForLevel(Player* player, uint8 Level)
    {
        if (Level > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
            return;

        LevelReward const* levelReward = GetLevelReward(Level);
        if (!levelReward)
            return;

        ChatHandler handler(player->GetSession());
        std::string Subject, Text, SelfMessage;

        KargatumMailVector ListItemPairs;
        ListItemPairs.push_back(KargatumMailItemPair(levelReward->ItemID, levelReward->ItemCount));        

        Subject = sKargatumScript->GetFormatString("Награда за повышение уровня до %u", Level);
        Text = sKargatumScript->GetFormatString("Вы повысили свой уровень до %u и получаете за это награду!", Level);
        SelfMessage = sKargatumScript->GetFormatString("Вы повысили уровень до %u и получаете награду!", Level);
        handler.PSendSysMessage("%s", SelfMessage.c_str());
        sKargatumScript->SendMoreItemsMail(player, Subject, Text, levelReward->Money, ListItemPairs);
    }
};

void AddSC_Kargatum_LevelReward()
{
	new KargatumLevelReward();
}
