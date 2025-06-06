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

#include "AreaTriggerPackets.h"
#include "PacketOperators.h"

namespace WorldPackets::AreaTrigger
{
ByteBuffer& operator<<(ByteBuffer& data, AreaTriggerSplineInfo const& areaTriggerSpline)
{
    data << uint32(areaTriggerSpline.TimeToTarget);
    data << uint32(areaTriggerSpline.ElapsedTimeForMovement);

    data << BitsSize<16>(areaTriggerSpline.Points);
    data.FlushBits();

    for (TaggedPosition<Position::XYZ> const& point : areaTriggerSpline.Points)
        data << point;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, AreaTriggerOrbitInfo const& areaTriggerCircularMovement)
{
    data << OptionalInit(areaTriggerCircularMovement.PathTarget);
    data << OptionalInit(areaTriggerCircularMovement.Center);
    data << Bits<1>(areaTriggerCircularMovement.CounterClockwise);
    data << Bits<1>(areaTriggerCircularMovement.CanLoop);

    data << uint32(areaTriggerCircularMovement.TimeToTarget);
    data << int32(areaTriggerCircularMovement.ElapsedTimeForMovement);
    data << uint32(areaTriggerCircularMovement.StartDelay);
    data << float(areaTriggerCircularMovement.Radius);
    data << float(areaTriggerCircularMovement.BlendFromRadius);
    data << float(areaTriggerCircularMovement.InitialAngle);
    data << float(areaTriggerCircularMovement.ZOffset);

    if (areaTriggerCircularMovement.PathTarget)
        data << *areaTriggerCircularMovement.PathTarget;

    if (areaTriggerCircularMovement.Center)
        data << *areaTriggerCircularMovement.Center;

    return data;
}

ByteBuffer& operator<<(ByteBuffer& data, AreaTriggerMovementScriptInfo const& areaTriggerMovementScript)
{
    data << int32(areaTriggerMovementScript.SpellScriptID);
    data << areaTriggerMovementScript.Center;

    return data;
}

void AreaTrigger::Read()
{
    _worldPacket >> AreaTriggerID;
    _worldPacket >> Bits<1>(Entered);
    _worldPacket >> Bits<1>(FromClient);
}

WorldPacket const* AreaTriggerDenied::Write()
{
    _worldPacket << int32(AreaTriggerID);
    _worldPacket << Bits<1>(Entered);
    _worldPacket.FlushBits();

    return &_worldPacket;
}

WorldPacket const* AreaTriggerRePath::Write()
{
    _worldPacket << TriggerGUID;
    _worldPacket << Unused_1100;

    _worldPacket << OptionalInit(AreaTriggerSpline);
    _worldPacket << OptionalInit(AreaTriggerOrbit);
    _worldPacket << OptionalInit(AreaTriggerMovementScript);
    _worldPacket.FlushBits();

    if (AreaTriggerSpline)
        _worldPacket << *AreaTriggerSpline;

    if (AreaTriggerMovementScript)
        _worldPacket << *AreaTriggerMovementScript;

    if (AreaTriggerOrbit)
        _worldPacket << *AreaTriggerOrbit;

    return &_worldPacket;
}

WorldPacket const* AreaTriggerPlaySpellVisual::Write()
{
    _worldPacket << AreaTriggerGUID;
    _worldPacket << uint32(SpellVisualID);

    return &_worldPacket;
}
}
