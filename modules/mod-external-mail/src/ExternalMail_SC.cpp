/*
 *  Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan 
*/

#include "ExternalMail.h"
#include "ScriptMgr.h"
#include "Log.h"

// Custom script
class ExternalMail_World : public WorldScript
{
public:
    ExternalMail_World() : WorldScript("ExternalMail_World") { }

    void OnAfterConfigLoad(bool /*Reload*/) override
    {
        sEM->LoadConfig();
    }

    void OnUpdate(uint32 Diff) override
    {
        if (!sEM->IsSystemEnable())
            return;

        uint32 TimeInterval = sEM->GetCheckTimeInterval();

        if (CheckTimeInterval < Diff)
        {
            sEM->SendMails();
            CheckTimeInterval = TimeInterval;
        }
        else
            CheckTimeInterval -= Diff;
    }

private:
    uint32 CheckTimeInterval = sEM->GetCheckTimeInterval();
};

void AddSC_ExternalMail()
{
    new ExternalMail_World();
}
