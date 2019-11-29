/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/LibKargatumConfig.h"
#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Player.h"
#include "Chat.h"
#include <vector>

class KargatumBuffCommand : public CommandScript
{
public:
    KargatumBuffCommand() : CommandScript("KargatumBuffCommand") {}

	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> commandTable = // .commands
		{
			{ "buff",				SEC_PLAYER,			false, &HandleBuffCommand,	""}
		};

		return commandTable;
	}

	static bool HandleBuffCommand(ChatHandler *handler, const char *args)
	{
        if (!CONF_BOOL(conf::BUFF_COMMAND_ENABLE))
        {
			handler->SendSysMessage("Команда отключена");
			handler->SetSentErrorMessage(true);
            return false;
        }

        Player* player = handler->GetSession()->GetPlayer();
		std::string ArgStr = (char*)args;

		if (ArgStr == "reload" && AccountMgr::IsAdminAccount(player->GetSession()->GetSecurity()))
		{
			sLog->outString("Перезагрузка баффов для команды .buff...");
			sKargatumLoad->LoadBuffData();
			handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `player_buff` |cFFFF0000перезагружена.|r");
			return true;
		}
		else
		{
			if (player->duel || player->GetMap()->IsBattleArena() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead(), player->IsInCombat() || player->IsInFlight())
			{
				handler->SendSysMessage("Сейчас вы не можете этого сделать");			
				handler->SetSentErrorMessage(true);
				return false;
			}

			player->RemoveAurasByType(SPELL_AURA_MOUNTED);

			KargatumLoad::BuffDataContainer& buffStore = sKargatumLoad->GetBuffData();
		
            for (auto i : buffStore)
                player->CastSpell(player, i, true);
			
			return true;
		}
	}
};

void AddSC_Kargatum_BuffCommand()
{
	new KargatumBuffCommand();
}
