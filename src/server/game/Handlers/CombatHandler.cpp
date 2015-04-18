/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
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

#include "Common.h"
#include "Log.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ObjectAccessor.h"
#include "CreatureAI.h"
#include "ObjectDefines.h"
#include "Vehicle.h"
#include "VehicleDefines.h"
#include "Player.h"
#include "Opcodes.h"

void WorldSession::HandleAttackSwingOpcode(WorldPacket& recvData)
{
    ObjectGuid guid;
    recvData >> guid;

    TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_ATTACKSWING Message guidlow:%u guidhigh:%u", GUID_LOPART(guid), GUID_HIPART(guid));

    Unit* pEnemy = ObjectAccessor::GetUnit(*_player, guid);

    if (!pEnemy)
    {
        // stop attack state at client
        SendAttackStop(NULL);
        return;
    }

    if (!_player->IsValidAttackTarget(pEnemy))
    {
        // stop attack state at client
        SendAttackStop(pEnemy);
        return;
    }

    //! Client explicitly checks the following before sending CMSG_ATTACKSWING packet,
    //! so we'll place the same check here. Note that it might be possible to reuse this snippet
    //! in other places as well.
    if (Vehicle* vehicle = _player->GetVehicle())
    {
        VehicleSeatEntry const* seat = vehicle->GetSeatForPassenger(_player);
        ASSERT(seat);
        if (!(seat->m_flags & VEHICLE_SEAT_FLAG_CAN_ATTACK))
        {
            SendAttackStop(pEnemy);
            return;
        }
    }

    _player->Attack(pEnemy, true);
}

void WorldSession::HandleAttackStopOpcode(WorldPacket & /*recvData*/)
{
    GetPlayer()->AttackStop();
}

void WorldSession::HandleSetSheathedOpcode(WorldPacket& recvData)
{
    uint32 sheathed;
    bool hasData = false;

    recvData >> sheathed;
    hasData = recvData.ReadBit();

    //TC_LOG_DEBUG("network", "WORLD: Recvd CMSG_SETSHEATHED Message guidlow:%u value1:%u", GetPlayer()->GetGUIDLow(), sheathed);

    if (hasData)
    {
        if (sheathed >= MAX_SHEATH_STATE)
        {
            TC_LOG_ERROR("network", "Unknown sheath state %u ??", sheathed);
            return;
        }

        GetPlayer()->SetSheath(SheathState(sheathed));
    }
}

void WorldSession::SendAttackStop(Unit const* enemy)
{
    WorldPacket data(SMSG_ATTACKSTOP, 16 + 16);

    ObjectGuid attackerGuid = GetPlayer()->GetGUID128();
    ObjectGuid victimGuid = enemy ? enemy->GetGUID128() : 0;

    data << attackerGuid;
    data << victimGuid;
    data.WriteBit(0); // NowDead
    data.FlushBits();

    SendPacket(&data);
}
