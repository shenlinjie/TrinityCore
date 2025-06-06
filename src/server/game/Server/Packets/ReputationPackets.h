/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_REPUTATION_PACKETS_H
#define TRINITYCORE_REPUTATION_PACKETS_H

#include "Packet.h"

namespace WorldPackets
{
    namespace Reputation
    {
        struct FactionData
        {
            int32 FactionID = 0;
            uint16 Flags = 0;
            int32 Standing = 0;
        };

        struct FactionBonusData
        {
            int32 FactionID = 0;
            bool FactionHasBonus = false;
        };

        class InitializeFactions final : public ServerPacket
        {
        public:
            InitializeFactions() : ServerPacket(SMSG_INITIALIZE_FACTIONS, 0x1000) { }

            WorldPacket const* Write() override;

            std::vector<FactionData> Factions;
            std::vector<FactionBonusData> Bonuses;
        };

        struct FactionStandingData
        {
            FactionStandingData() { }
            FactionStandingData(int32 index, int32 standing, int32 factionId) : Index(index), Standing(standing), FactionID(factionId) { }

            int32 Index = 0;
            int32 Standing = 0;
            int32 FactionID = 0;
        };

        class SetFactionStanding final : public ServerPacket
        {
        public:
            SetFactionStanding() : ServerPacket(SMSG_SET_FACTION_STANDING) { }

            WorldPacket const* Write() override;

            float BonusFromAchievementSystem = 0.0f;
            std::vector<FactionStandingData> Faction;
            bool ShowVisual = false;
        };
    }
}

#endif // TRINITYCORE_REPUTATION_PACKETS_H
