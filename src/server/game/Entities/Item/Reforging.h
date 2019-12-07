#ifndef REFORGING_H
#define REFORGING_H

#include "Common.h"
#include "Player.h"
#include "Item.h"
#include <vector>

// Supply lowguid or reforge! (or both)
// Warning, this function may modify player->reforgeMap when lowguid is supplied
void SendReforgePacket(Player* player, uint32 entry, uint32 lowguid = 0, const ReforgeData* reforge = nullptr);
void SendReforgePackets(Player* player);
void RemoveReforge(Player* player, uint32 itemguid, bool update);
std::vector<Item*> GetItemList(const Player* player);

#endif