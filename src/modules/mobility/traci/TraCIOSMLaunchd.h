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

#ifndef WORLD_TRACI_TRACIOSMLAUNCHD_H
#define WORLD_TRACI_TRACIOSMLAUNCHD_H

#include <omnetpp.h>
#include <UDPSocket.h>
#include <cmessage.h>

#include "modules/mobility/traci/TraCIMobility.h"
#include "modules/mobility/traci/TraCIScenarioManager.h"
#include "modules/mobility/traci/TraCIScenarioManagerLaunchd.h"


/**
 * @brief
 * Extends the TraCIScenarioManager for use with OSM in a browser.
 *
 *
 * All other functionality is provided by the TraCIScenarioManager.
 *
 * See the Veins website <a href="http://veins.car2x.org/"> for a tutorial, documentation, and publications </a>.
 *
 * @author Christoph Sommer, David Eckhoff
 *
 * @see TraCIMobility
 * @see TraCIScenarioManager
 *
 */
namespace Veins {
class TraCIOSMLaunchd: public TraCIScenarioManagerLaunchd
{
	public:
        TraCIOSMLaunchd();
		virtual ~TraCIOSMLaunchd();
	    virtual void handleSelfMsg(cMessage *msg);
	    virtual void initialize(int stage);
	    virtual void finish();
	    char* osmBuf;
	    std::set<cModule*> myModCar;
	    Coord* myCarCoord;
	    //Coord* myCarSpeed;
	    //string myCarID;
	    double myCarPosX,myCarPosY,myCarPosZ,myCarAngle;
	    TraCIMobility* myCarMobilityAccess;
	    cPacket* ourMsg;
	    UDPSocket mySocket;
	    struct packetDatagram
	    {
	        double myCarPosX,myCarPosY,myCarAngle;

	        std::string myCarID;

	    };
	    packetDatagram* myPacket;
};
}

namespace Veins {
class TraCIOSMLaunchdAccess
{
	public:
		TraCIOSMLaunchd* get() {
			return FindModule<TraCIOSMLaunchd*>::findGlobalModule();
		};
};
}

#endif
