//
// Copyright (C) 2006-2012 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "modules/mobility/traci/TraCIScenarioManagerLaunchd.h"
#include "modules/mobility/traci/TraCICommandInterface.h"
#include "modules/mobility/traci/TraCIConstants.h"
#include "modules/mobility/traci/TraCIOSMLaunchd.h"
#define CMD_FILE_SEND 0x75

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

#define MYDEBUG EV

using namespace Veins;

Define_Module(Veins::TraCIOSMLaunchd);



TraCIOSMLaunchd::~TraCIOSMLaunchd() {

}

void TraCIOSMLaunchd::finish() {
    TraCIScenarioManager::finish();

}

void TraCIOSMLaunchd::handleSelfMsg(cMessage* msg)
{
    TraCIScenarioManagerLaunchd::handleSelfMsg(msg);
    if (msg == executeOneTimestepTrigger)
    {
        typedef std::map<std::string, cModule*> host_map;
        for (host_map::const_iterator it = hosts.begin(); it != hosts.end(); ++it)
        {
            const TraCIMobility* mobility = TraCIMobilityAccess().get(it->second);
            Coord car = mobility->getCurrentPosition();
            packetDatagram packet;
            packet.myCarID = mobility->getExternalId();
            packet.myCarAngle = mobility->getAngleRad();
            packet.myCarPosX = car.x;
            packet.myCarPosY = car.y;
            // if you had a proper UDP socket, then you could send a packet...
         }
    }
}

Veins::TraCIOSMLaunchd::TraCIOSMLaunchd() {
}

void Veins::TraCIOSMLaunchd::initialize(int stage) {
    TraCIScenarioManagerLaunchd::initialize(stage);
}
