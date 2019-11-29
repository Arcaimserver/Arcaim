/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "../Kargatum-lib/LibKargatumLoadSystem.h"
#include "../Kargatum-lib/LibKargatumConfig.h"
#include "Log.h"
#include "World.h"
#include "ObjectMgr.h"
#include "DBCStores.h"
#include "DatabaseEnv.h"

KargatumLoad* KargatumLoad::instance()
{
    static KargatumLoad instance;
    return &instance;
}

void KargatumLoad::LoadMessageAntiAD()
{
	uint32 oldMSTime = getMSTime();

	_AntiAdMessageStore.clear();

	QueryResult result = WorldDatabase.PQuery("SELECT message FROM `anti_ad_message`");
	if (!result)
	{
        sLog->outString(">> Загружено 0 слов. Таблица `anti_ad_message` возможно пустая.");
        sLog->outString();
		return;
	}

	do
	{
		std::string message = result->Fetch()->GetString();
		_AntiAdMessageStore.push_back(message);

	} while (result->NextRow());

    sLog->outString(">> Загружено запретных слов %u за %u мс", uint32(_AntiAdMessageStore.size()), GetMSTimeDiffToNow(oldMSTime));
	sLog->outString();
}

void KargatumLoad::LoadBuffData()
{
	uint32 oldMSTime = getMSTime();

	_BuffDataStore.clear();

	QueryResult result = WorldDatabase.PQuery("SELECT SpellID FROM `player_buff`");
	if (!result)
	{
        sLog->outString(">> Загружено 0 баффов. Таблица `player_buff` возможно пустая.");
        sLog->outString();
		return;
	}

	do
	{
		Field* fields = result->Fetch();

        uint32 SpellID = fields[0].GetInt32();

        auto spell = sSpellStore.LookupEntry(SpellID);
        if (!spell)
        {
            sLog->outError("-> Заклинания под номером (%u) не существует. Пропуск.", SpellID);   
            continue;
        }

        _BuffDataStore.push_back(SpellID);

	} while (result->NextRow());

    sLog->outString(">> Загружено %u баффов за %u мс", (uint32)_BuffDataStore.size(), GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

/*
void KargatumLoad::LoadLevelUPItem()
{
	uint32 oldMSTime = getMSTime();

	_LevelUPItemDataStore.clear();

	QueryResult result = WorldDatabase.PQuery("SELECT Entry, MinLevel, MaxLevel FROM `item_levelup`");
	if (!result)
	{
		sLog->outString(">> Загружено 0 предметов. Таблица `item_levelup` возможно пустая.");
		sLog->outString();
		return;
	}

	do
	{
		Field* fields = result->Fetch();
		uint32 Entry = fields[0].GetUInt32();
        uint32 Minlevel = fields[1].GetUInt32();
        uint32 Maxlevel = fields[2].GetUInt32();

		// Проверка
		ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(Entry);

		if (!itemTemplate)
		{
			sLog->outErrorDb("Предмета под номером %u не существует. Пропуск", Entry);
			continue;
		}

		if (itemTemplate->ScriptId != sObjectMgr->GetScriptId("Kargatum_LevelUP_Item"))
		{
			sLog->outErrorDb("В предмете %u не прописано название скрипта(Kargatum_LevelUP_Item). Пропуск", Entry);
			continue;
		}

		if (Maxlevel > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
		{
			sLog->outErrorDb("В предмете %u требуемый максимальный уровень(%u) большем чем максимальный уровень на сервере (%u). Установлено %u", Entry, Maxlevel, sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL), sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL));
			Maxlevel = sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
		}

		if (Minlevel > Maxlevel)
		{
			sLog->outErrorDb("В предмете %u требуемый минимальный уровень(%u) > требуемого максимального(%u). Установлено %u", Entry, Minlevel, Maxlevel, Maxlevel);
			Minlevel = Maxlevel;
		}

		LevelUPItem& db_info = _LevelUPItemDataStore[Entry];
		db_info.MinLevel = Minlevel;
		db_info.MaxLevel = Maxlevel;

	} while (result->NextRow());

	sLog->outString(">> Загружено предметов %i за %u мс", int32(_LevelUPItemDataStore.size()), GetMSTimeDiffToNow(oldMSTime));
	sLog->outString();
}*/

void KargatumLoad::LoadPlayedTimeReward()
{
    uint32 msTime = getMSTime();
    _RewardPlayedTimeStore.clear();

    QueryResult result = WorldDatabase.Query("SELECT RewardPlayedTime, ItemID, Count FROM online_reward");
    if (!result)
    {
        sLog->outErrorDb(">> В таблице `online_reward` нет данных. Загрузка отменена");
        sLog->outString();
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        uint32 Seconds = fields[0].GetUInt32();

        RewardPlayedTime RPT;
        RPT.ItemID = fields[1].GetUInt32();
        RPT.Count = fields[2].GetUInt32();

        // Проверка
        if (Seconds == 0)
        {
            sLog->outErrorDb("-> Время = 0? Серьёзно? Пропуск однозначно...");   
            continue;
        }

        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(RPT.ItemID);
        if (!itemTemplate)
        {
            sLog->outErrorDb("-> Предмета под номером %u не существует. Пропуск", RPT.ItemID);      
            continue;
        }

        if (RPT.Count <= 0)
        {
            sLog->outErrorDb("-> Количество выдаваемого предмета под номером %u - %u. Изменено на 1", RPT.ItemID, RPT.Count);     
            RPT.Count = 1;
        }

        _RewardPlayedTimeStore[Seconds] = RPT;

    } while (result->NextRow());

    sLog->outString(">> Загружено %u наград за %u мс", (uint32)_RewardPlayedTimeStore.size(), GetMSTimeDiffToNow(msTime));
    sLog->outString();
}

void KargatumLoad::LoadLevelReward()
{
    uint32 msTime = getMSTime();
    _levelRewardStore.clear();

    //                                                  0      1      2       3
    QueryResult result = WorldDatabase.Query("SELECT Level, Money, ItemID, ItemCount FROM level_reward ORDER BY Level");
    if (!result)
    {
        sLog->outErrorDb("В таблице `level_reward` нет данных. Загрузка отменена");
        sLog->outString();
        return;
    }

    do
    {
        Field* fields = result->Fetch();

        LevelReward levelReward;

        uint32 Level = fields[0].GetUInt32();

        levelReward.Money       = fields[1].GetUInt32();
        levelReward.ItemID      = fields[2].GetUInt32();
        levelReward.ItemCount   = fields[3].GetUInt32();

        // Проверка
        if (Level > sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL))
        {
            sLog->outErrorDb("-> Уровень (%u) больше, чем максимальный уровень на сервере (%u). Пропуск", Level, sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL));   
            continue;
        }

        if (levelReward.ItemID)
        {
            ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(levelReward.ItemID);
            if (!itemTemplate)
            {
                sLog->outErrorDb("-> Для уровня (%u) предмета под номером %u не существует. Предмет убран из награды", Level, levelReward.ItemID);   
                levelReward.ItemID = 0;
            }
        }

        if (levelReward.ItemID && !levelReward.ItemCount)
        {
            sLog->outErrorDb("-> Для уровня (%u) предмет под номером %u выдаётся в количестве 0 штук - это бессмыслено. Установлено 1", Level, levelReward.ItemID);
            levelReward.ItemCount = 1;
        }

        _levelRewardStore[Level] = levelReward;

    } while (result->NextRow());

    sLog->outString(">> Загружено %u наград за уровни %u мс", (uint32)_levelRewardStore.size(), GetMSTimeDiffToNow(msTime));
    sLog->outString();
}

void KargatumLoad::LoadKargatumSystem()
{
    if (CONF_BOOL(conf::BUFF_COMMAND_ENABLE))
    {    
        sLog->outString("Загрузка баффов для команды .buff...");
        LoadBuffData();
    }

	if (CONF_BOOL(conf::ANTIAD_ENABLE))
    {
        sLog->outString("Загрузка запретных слов...");
        LoadMessageAntiAD();
    }

	// sLog->outString("Загрузка предметов для повышения уровня персонажа");
	// LoadLevelUPItem();

    if (CONF_BOOL(conf::SPELL_DURATION_ENABLE))
    {
        // sLog->outString("Загрузка времени действия заклинаний...");
        // sKargatumSpell->LoadSpellMaxDurationFromDB();
    }

    if (CONF_BOOL(conf::ONLINE_REWARD_ENABLE))
    {
        sLog->outString("Загрузка награды за онлайн...");
        LoadPlayedTimeReward();
    }
    
    if (CONF_BOOL(conf::LEVEL_REWARD_ENABLE))
    {
        sLog->outString("Загрузка наград за уровни...");
        LoadLevelReward();
    }
}
