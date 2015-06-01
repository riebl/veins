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
    mySocket.bind(3000);
    TraCIScenarioManagerLaunchd::handleSelfMsg(msg);
    if (msg == executeOneTimestepTrigger)
    {
        if (simTime() > 1)
        {
            for (std::set<std::string>::const_iterator it =subscribedVehicles.begin(); it != subscribedVehicles.end(); ++it)
            {
                for(int i = 0; i<myModCar.size();i++)
                {
                  //  myModCar.insert(getManagedHosts()); // putting hosts in a set
                     myModCar.insert(getManagedModule(subscribedVehicles)); //another way to insert into the set.Would work in the same way though.
                }

                   for(int it =myModCar.begin(); it!=myModCar.end();it++)
                   {
                       myPacket = new packetDatagram();
                       //Trying to get the data and put it in a buffer as OurMsg
                       myCarMobilityAccess = TraCIMobilityAccess().get(myModCar);
                       myCarCoord = myCarMobilityAccess->getCurrentPosition();
                       //myPacket.myCarSpeed = myCarMobilityAccess->getSpeed();
                       myPacket->myCarAngle = myCarMobilityAccess->getAngleRad();
                       myPacket->myCarID = myCarMobilityAccess->getExternalId();
                       myPacket->myCarPosX = myCarCoord->x;
                       myPacket->myCarPosY = myCarCoord->y;



                       // maybe this way we can extract the data !!!

                       // then create the json file as our buffer and send the data through our socket
                       ourMsg = new cPacket(*i);
                       mySocket.send(ourMsg);
                       mySocket.close();
                   }
             }

         }
     }
 }

        return;

    error("TraCIScenarioManager received unknown self-message");
}

Veins::TraCIOSMLaunchd::TraCIOSMLaunchd() {
}

void Veins::TraCIOSMLaunchd::initialize(int stage) {
    TraCIScenarioManagerLaunchd::initialize(stage);
}
