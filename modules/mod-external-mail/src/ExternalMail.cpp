/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
 * Licence MIT https://opensource.org/MIT
 */

#include "ExternalMail.h"
#include "Config.h"
#include "Log.h"
#include "ScriptMgr.h"
#include "Util.h"
#include "Mail.h"
#include "ObjectMgr.h"

ExternalMail* ExternalMail::instance()
{
    static ExternalMail instance;
    return &instance;
}

void ExternalMail::LoadConfig()
{
    _IsEnableSystem = sConfigMgr->GetBoolDefault("External.Mail.Enable", false);
    _IntervalTime = sConfigMgr->GetIntDefault("External.Mail.Interval", 1) * 1000 * 60;
}

uint32 ExternalMail::GetCheckTimeInterval()
{
    return _IntervalTime;
}

bool ExternalMail::IsSystemEnable()
{
    return _IsEnableSystem;
}

void ExternalMail::SendMails()
{
    QueryResult result = CharacterDatabase.PQuery("SELECT ID, PlayerName, Subject, Message, Money, ItemID, ItemCount, CreatureEntry FROM mail_external ORDER BY id ASC");
    if (!result)
        return;

    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    MailDraft* mail = nullptr;

    uint32 MessagesCount = 0;

    do
    {
        Field* fields           = result->Fetch();
        uint32 ID               = fields[0].GetUInt32();
        std::string PlayerName  = fields[1].GetString();
        std::string Subject     = fields[2].GetString();
        std::string Body        = fields[3].GetString();
        uint32 Money            = fields[4].GetUInt32();
        uint32 ItemID           = fields[5].GetUInt32();
        uint32 ItemCount        = fields[6].GetUInt32();
        uint32 CreatureEntry    = fields[7].GetUInt32();

        if (!normalizePlayerName(PlayerName))
        {
            sLog->outErrorDb("> External Mail: Неверное имя персонажа (%s)", PlayerName.c_str());
            continue;
        }

        uint64 PlayerGuid = sObjectMgr->GetPlayerGUIDByName(PlayerName);
        if (!PlayerGuid)
            continue;

        Player* receiver = ObjectAccessor::FindPlayer(PlayerGuid);

        mail = new MailDraft(Subject, Body);

        if (Money)
            mail->AddMoney(Money);

        bool _error = false;

        // Проверка
        ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(ItemID);
        if (!itemTemplate)
        {
            sLog->outErrorDb("Предмета под номером %u не существует. Пропуск", ItemID);
            _error = true;
        }

        auto const* creature = sObjectMgr->GetCreatureTemplate(CreatureEntry);
        if (!creature)
        {
            sLog->outErrorDb("НПС под номером %u не существует. Пропуск", CreatureEntry);
            _error = true;
        }

        if (_error)
        {
            CharacterDatabase.PExecute("UPDATE `mail_external` SET `SystemComment` = '%s' WHERE `ID` = %u", "Предмета либо НПС не существует!", ID);
            continue;
        }

        if (ItemID)
        {
            /*if (!ItemCount)
                ItemCount = 1;*/

            if(Item* mailItem = Item::CreateItem(ItemID, ItemCount))
            {
                mailItem->SaveToDB(trans);
                mail->AddItem(mailItem);
            }
        }

        mail->SendMailTo(trans, receiver ? receiver : MailReceiver(PlayerGuid), MailSender(MAIL_CREATURE, CreatureEntry, MAIL_STATIONERY_DEFAULT), MAIL_CHECK_MASK_RETURNED);
        delete mail;

        trans->PAppend("DELETE FROM mail_external WHERE id = %u", ID);

        MessagesCount++;

    } while (result->NextRow());

   CharacterDatabase.CommitTransaction(trans);

   if (MessagesCount)
   {
       sLog->outString("> External Mail: Отправлено (%u) писем", MessagesCount);
       sLog->outString();
   }   
}
