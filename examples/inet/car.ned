import inet.applications.traci.TraCIDemo;
import inet.linklayer.ieee80211.Ieee80211Nic;
import inet.networklayer.common.InterfaceTable;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;
import org.car2x.veins.modules.application.traci.TraCIDemo11p;

module car
{
    parameters:
        @node();
        *.interfaceTableModule = default(absPath(".interfaceTable"));

    gates:
        input radioIn @directIn;

    submodules:
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=140,326");
        }

        app: TraCIDemo11p {
            parameters:
                @display("p=384,46");
        }

        mobility: TraCIMobility {
            parameters:
                @display("p=60,459");
        }

        wlan: Ieee80211Nic {
            parameters:
                @display("p=304,461;q=queue");
        }

    connections allowunconnected:
        wlan.upperLayerOut --> app.lowerLayerIn;
        wlan.upperLayerIn <-- app.lowerLayerOut;

        radioIn --> wlan.radioIn;
}
