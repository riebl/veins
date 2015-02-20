import inet.physicallayer.ieee80211.Ieee80211ScalarRadioMedium;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import org.car2x.veins.modules.mobility.traci.TraCIScenarioManagerLaunchd;

network scenario
{
    submodules:
        radioMedium: Ieee80211ScalarRadioMedium {
        }

        manager: TraCIScenarioManagerLaunchd {
        }

        configurator: IPv4NetworkConfigurator {
        }
}
