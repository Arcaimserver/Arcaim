/*
 *  Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
*/

#include "NpcProfessions.h"
#include "ScriptMgr.h"
#include "Log.h"

class Kargatum_NPC_Profession : public CreatureScript
{
public:
    Kargatum_NPC_Profession() : CreatureScript("Kargatum_NPC_Profession") {}

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        ClearGossipMenuFor(player);

        AddGossipItemFor(player, 9, "Изучить профессию", GOSSIP_SENDER_MAIN, 50);
        AddGossipItemFor(player, 9, "Изучить вторичный навык", GOSSIP_SENDER_MAIN, 51);
        SendGossipMenuFor(player, 1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 Sender, uint32 Action) override
    {
        if (Sender != GOSSIP_SENDER_MAIN)
            return true;

        ClearGossipMenuFor(player);
        ChatHandler handler(player->GetSession());

        switch (Action)
        {
        case 50: // основные профы
            AddGossipItemFor(player, 5, "Алхимия", GOSSIP_SENDER_MAIN, 1);
            AddGossipItemFor(player, 5, "Кузнечное дело", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 5, "Кожевничество", GOSSIP_SENDER_MAIN, 3);
            AddGossipItemFor(player, 5, "Портняжное дело", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, 5, "Инженерное дело", GOSSIP_SENDER_MAIN, 5);
            AddGossipItemFor(player, 5, "Наложение чар", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, 5, "Ювелирное дело", GOSSIP_SENDER_MAIN, 7);
            AddGossipItemFor(player, 5, "Начертание", GOSSIP_SENDER_MAIN, 8);
            AddGossipItemFor(player, 5, "Травничество", GOSSIP_SENDER_MAIN, 9);
            AddGossipItemFor(player, 5, "Снятие шкур", GOSSIP_SENDER_MAIN, 10);
            AddGossipItemFor(player, 5, "Горное дело", GOSSIP_SENDER_MAIN, 11);
            SendGossipMenuFor(player, 1, creature->GetGUID());
            break;
        case 51: // Второстепенные профы
            AddGossipItemFor(player, 5, "Рыболовное дело", GOSSIP_SENDER_MAIN, 12);
            AddGossipItemFor(player, 5, "Кулинария", GOSSIP_SENDER_MAIN, 13);
            AddGossipItemFor(player, 5, "Первая помощь", GOSSIP_SENDER_MAIN, 14);
            SendGossipMenuFor(player, 1, creature->GetGUID());
            break;
        case 1: // Алхимия
            if (!player->HasSkill(SKILL_ALCHEMY))
                CompleteLearnProfession(player, SKILL_ALCHEMY);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Алхимия");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 2: // Кузнечное дело
            if (!player->HasSkill(SKILL_BLACKSMITHING))
                CompleteLearnProfession(player, SKILL_BLACKSMITHING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Кузнечное дело");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 3: // Кожевничество
            if (!player->HasSkill(SKILL_LEATHERWORKING))
                CompleteLearnProfession(player, SKILL_LEATHERWORKING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Кожевничество");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 4: // Портняжное дело
            if (!player->HasSkill(SKILL_TAILORING))
                CompleteLearnProfession(player, SKILL_TAILORING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Портняжное дело");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 5: // Инженерное дело
            if (!player->HasSkill(SKILL_ENGINEERING))
                CompleteLearnProfession(player, SKILL_ENGINEERING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Инженерное дело");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 6: // Наложение чар
            if (!player->HasSkill(SKILL_ENCHANTING))
                CompleteLearnProfession(player, SKILL_ENCHANTING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Наложение чар");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 7: // Ювелирное дело
            if (!player->HasSkill(SKILL_JEWELCRAFTING))
                CompleteLearnProfession(player, SKILL_JEWELCRAFTING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Ювелирное дело");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 8: // Начертание
            if (!player->HasSkill(SKILL_INSCRIPTION))
                CompleteLearnProfession(player, SKILL_INSCRIPTION);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Начертание");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 9: // Травничество
            if (!player->HasSkill(SKILL_HERBALISM))
                CompleteLearnProfession(player, SKILL_HERBALISM);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Травничество");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 10: // Снятие шкур
            if (!player->HasSkill(SKILL_SKINNING))
                CompleteLearnProfession(player, SKILL_SKINNING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Снятие шкур");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 11: // Горное дело
            if (!player->HasSkill(SKILL_MINING))
                CompleteLearnProfession(player, SKILL_MINING);
            else
                handler.PSendSysMessage("Вы уже знаете проферссию: Горное дело");

            OnGossipSelect(player, creature, Sender, 50);
            break;
        case 12: // Рыболовное дело
            if (!player->HasSkill(SKILL_FISHING))
                CompleteLearnProfession(player, SKILL_FISHING);
            else
                handler.PSendSysMessage("Вы уже знаете навык: Рыболовное дело");

            OnGossipSelect(player, creature, Sender, 51);
            break;
        case 13: // Кулинария
            if (!player->HasSkill(SKILL_COOKING))
                CompleteLearnProfession(player, SKILL_COOKING);
            else
                handler.PSendSysMessage("Вы уже знаете навык: Кулинария");

            OnGossipSelect(player, creature, Sender, 51);
            break;
        case 14: // Первая помощь
            if (!player->HasSkill(SKILL_FIRST_AID))
                CompleteLearnProfession(player, SKILL_FIRST_AID);
            else
                handler.PSendSysMessage("Вы уже знаете навык: Первая помощь");

            OnGossipSelect(player, creature, Sender, 51);
            break;
        default:
            handler.SendSysMessage("Ошибка выбора о.о");
            break;
        }

        return true;
    }

private:
    bool IsPlayerHasMaxProfession(Player* player)
    {
        int8 ProfCount = 0;
        int8 MaxProfCount = sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL);

        if (player->HasSkill(SKILL_MINING))
            ProfCount++;

        if (player->HasSkill(SKILL_SKINNING))
            ProfCount++;
            
        if (player->HasSkill(SKILL_HERBALISM))
            ProfCount++;

        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
            if (!SkillInfo)
                continue;

            if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                continue;

            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                continue;

            const uint32 skillID = SkillInfo->id;
            if (player->HasSkill(skillID))
                ProfCount++;
        }

        if (ProfCount >= MaxProfCount)
            return true;

        return false;
    }

    // void LearnStartSpellProfession(Player* player, uint32 SkillID)
    // {
    //     switch (SkillID)
    //     {
    //     case SKILL_ALCHEMY:
    //         player->learnSpell(2259);
    //         break;
    //     case SKILL_BLACKSMITHING:
    //         player->learnSpell(2018);
    //         break;
    //     case SKILL_LEATHERWORKING:
    //         player->learnSpell(2108);
    //         break;
    //     case SKILL_TAILORING:
    //         player->learnSpell(3908);
    //         break;
    //     case SKILL_ENGINEERING:
    //         player->learnSpell(4036);
    //         break;
    //     case SKILL_ENCHANTING:
    //         player->learnSpell(7411);
    //         break;
    //     case SKILL_JEWELCRAFTING:
    //         player->learnSpell(25229);
    //         break;
    //     case SKILL_INSCRIPTION:
    //         player->learnSpell(45357);
    //         break;
    //     case SKILL_HERBALISM:
    //         player->learnSpell(2372);
    //         break;
    //     case SKILL_SKINNING:
    //         player->learnSpell(8613);
    //         break;
    //     case SKILL_MINING:
    //         player->learnSpell(2575);
    //         break;
    //     case SKILL_FISHING:
    //         player->learnSpell(63275);
    //         break;
    //     case SKILL_COOKING:
    //         player->learnSpell(2550);
    //         break;
    //     case SKILL_FIRST_AID:
    //         player->learnSpell(3273);
    //         break;
    //     default:
    //         break;
    //     }
    // }

    void LearnSkillRecipesHelper(Player* player, uint32 SkillID)
    {
        // if (!CONF_BOOL(conf::NPC_PROF_LEARN_ALL_PROF_SPELL_ENABLE))
        // {
        //     LearnStartSpellProfession(player, SkillID);
        //     return;
        // }

        uint32 classmask = player->getClassMask();

        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;

            // wrong skill
            if (skillLine->skillId != SkillID)
                continue;

            // not high rank
            if (skillLine->forward_spellid)
                continue;

            // skip racial skills
            if (skillLine->racemask != 0)
                continue;

            // skip wrong class skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;

            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;

            if (!player->HasSpell(skillLine->spellId))
                player->learnSpell(skillLine->spellId);
        }
    }

    bool IsSecondarySkill(SkillType skill)
    {
        return skill == SKILL_COOKING || skill == SKILL_FIRST_AID || skill == SKILL_FISHING;
    }

    void CompleteLearnProfession(Player* player, SkillType skillid)
    {
        if (IsPlayerHasMaxProfession(player) && !IsSecondarySkill(skillid))
            ChatHandler(player->GetSession()).PSendSysMessage("Вы имеете максимально возможное количество профессий");
        else
        {
            SkillLineEntry const* SkillInfo = sSkillLineStore.LookupEntry(skillid);
            if (!SkillInfo)
                return;

            uint16 SetSkillPoint = 450;
            uint16 SkillStep = player->GetSkillStep(SkillInfo->id);

            LearnSkillRecipesHelper(player, SkillInfo->id);
            player->SetSkill(SkillInfo->id, SkillStep, SetSkillPoint, 450);
        }
    }
};

void AddSC_NpcProfessions()
{
    new Kargatum_NPC_Profession();
}
