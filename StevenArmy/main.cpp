#include "Vehicle.h"
#include "Battery.h"
#include "BatteryRating.h"
#include "SwapStation.h"
#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Input helpers
// -------------------------------------------------------
std::string getString(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

int getInt(const std::string& prompt) {
    int val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

float getFloat(const std::string& prompt) {
    float val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

double getDouble(const std::string& prompt) {
    double val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

// -------------------------------------------------------
// Find helpers
// -------------------------------------------------------
Vehicle* findVehicle(std::vector<Vehicle>& vehicles, const std::string& id) {
    for (auto& v : vehicles)
        if (v.getVehicleId() == id) return &v;
    return nullptr;
}

Battery* findBattery(std::vector<Battery>& batteries, const std::string& id) {
    for (auto& b : batteries)
        if (b.getBatteryId() == id) return &b;
    return nullptr;
}

// -------------------------------------------------------
// Prepopulate demo data
// -------------------------------------------------------
void prepopulate(std::vector<Vehicle>& vehicles,
    std::vector<Battery>& batteries,
    std::vector<SwapStation>& stations) {

    // 10 Vehicles
    vehicles.push_back(Vehicle("V001", "sedan", "Tesla", "Model 3", "Type-A-75kWh"));
    vehicles.push_back(Vehicle("V002", "suv", "Tesla", "Model X", "Type-B-100kWh"));
    vehicles.push_back(Vehicle("V003", "sedan", "Rivian", "R1S", "Type-A-75kWh"));
    vehicles.push_back(Vehicle("V004", "truck", "Rivian", "R1T", "Type-B-100kWh"));
    vehicles.push_back(Vehicle("V005", "sedan", "Chevy", "Bolt", "Type-A-75kWh"));
    vehicles.push_back(Vehicle("V006", "suv", "Ford", "Mach-E", "Type-A-75kWh"));
    vehicles.push_back(Vehicle("V007", "sedan", "Hyundai", "Ioniq6", "Type-C-60kWh"));
    vehicles.push_back(Vehicle("V008", "suv", "Kia", "EV9", "Type-C-60kWh"));
    vehicles.push_back(Vehicle("V009", "motorcycle", "Zero", "SR/F", "Type-D-15kWh"));
    vehicles.push_back(Vehicle("V010", "truck", "GMC", "Hummer EV", "Type-B-100kWh"));

    // Set owner ratings
    vehicles[0].setOwnerRating(5);
    vehicles[1].setOwnerRating(4);
    vehicles[2].setOwnerRating(4);
    vehicles[3].setOwnerRating(3);
    vehicles[4].setOwnerRating(5);
    vehicles[5].setOwnerRating(2);
    vehicles[6].setOwnerRating(3);
    vehicles[7].setOwnerRating(4);
    vehicles[8].setOwnerRating(5);
    vehicles[9].setOwnerRating(1);

    // 10 Batteries
    batteries.push_back(Battery("B001", "Lithium-Ion", 75.0f, "Type-A-75kWh"));
    batteries.push_back(Battery("B002", "Lithium-Ion", 75.0f, "Type-A-75kWh"));
    batteries.push_back(Battery("B003", "Lithium-Ion", 100.0f, "Type-B-100kWh"));
    batteries.push_back(Battery("B004", "Lithium-Ion", 100.0f, "Type-B-100kWh"));
    batteries.push_back(Battery("B005", "LFP", 75.0f, "Type-A-75kWh"));
    batteries.push_back(Battery("B006", "LFP", 60.0f, "Type-C-60kWh"));
    batteries.push_back(Battery("B007", "LFP", 60.0f, "Type-C-60kWh"));
    batteries.push_back(Battery("B008", "Solid-State", 100.0f, "Type-B-100kWh"));
    batteries.push_back(Battery("B009", "Lithium-Ion", 15.0f, "Type-D-15kWh"));
    batteries.push_back(Battery("B010", "Solid-State", 75.0f, "Type-A-75kWh"));

    // Rate each battery using BatteryRating
    struct BatteryData { std::string id, owner; float cap; int cycles, temp; };
    BatteryData data[] = {
        {"B001", "O001",  97.0f, 120,  0},
        {"B002", "O002",  88.0f, 430,  1},
        {"B003", "O003",  76.0f, 870,  2},
        {"B004", "O004",  62.0f, 1100, 4},
        {"B005", "O005",  95.0f, 200,  0},
        {"B006", "O006",  83.0f, 560,  1},
        {"B007", "O007",  55.0f, 1450, 7},
        {"B008", "O008",  99.0f, 50,   0},
        {"B009", "O009",  91.0f, 310,  0},
        {"B010", "O010",  70.0f, 950,  3}
    };
    for (int i = 0; i < 10; i++) {
        BatteryRating r("R-" + data[i].id, data[i].owner, data[i].id,
            data[i].cap, data[i].cycles, data[i].temp);
        batteries[i].setRating(r.getScore());
    }

    // Install batteries onto vehicles
    vehicles[0].installBattery("B001");
    vehicles[1].installBattery("B003");
    vehicles[2].installBattery("B002");
    vehicles[3].installBattery("B004");
    vehicles[4].installBattery("B005");
    vehicles[5].installBattery("B010");
    vehicles[6].installBattery("B006");
    vehicles[7].installBattery("B007");
    vehicles[8].installBattery("B009");
    vehicles[9].installBattery("B008");

    // 10 Swap Stations (US cities with real coords)
    stations.push_back(SwapStation("S001", "St. Louis Downtown", 38.6270, -90.1994));
    stations.push_back(SwapStation("S002", "St. Louis West", 38.6190, -90.3100));
    stations.push_back(SwapStation("S003", "Chicago Loop", 41.8827, -87.6233));
    stations.push_back(SwapStation("S004", "Kansas City Hub", 39.0997, -94.5786));
    stations.push_back(SwapStation("S005", "Nashville Center", 36.1627, -86.7816));
    stations.push_back(SwapStation("S006", "Memphis Depot", 35.1495, -90.0490));
    stations.push_back(SwapStation("S007", "Indianapolis North", 39.7684, -86.1581));
    stations.push_back(SwapStation("S008", "Louisville Gateway", 38.2527, -85.7585));
    stations.push_back(SwapStation("S009", "Springfield IL", 39.7817, -89.6501));
    stations.push_back(SwapStation("S010", "Bloomington Normal", 40.4842, -88.9937));

    // Stock stations with spare batteries (those not installed on vehicles)
    // S001 gets Type-A spares
    stations[0].addBattery(Battery("BS001", "Lithium-Ion", 75.0f, "Type-A-75kWh"));
    stations[0].addBattery(Battery("BS002", "LFP", 75.0f, "Type-A-75kWh"));
    // S002 gets Type-B spares
    stations[1].addBattery(Battery("BS003", "Lithium-Ion", 100.0f, "Type-B-100kWh"));
    stations[1].addBattery(Battery("BS004", "Solid-State", 100.0f, "Type-B-100kWh"));
    // S003 gets mixed
    stations[2].addBattery(Battery("BS005", "LFP", 75.0f, "Type-A-75kWh"));
    stations[2].addBattery(Battery("BS006", "LFP", 60.0f, "Type-C-60kWh"));
    // S004
    stations[3].addBattery(Battery("BS007", "Lithium-Ion", 75.0f, "Type-A-75kWh"));
    stations[3].addBattery(Battery("BS008", "Lithium-Ion", 15.0f, "Type-D-15kWh"));
    // S005
    stations[4].addBattery(Battery("BS009", "Solid-State", 75.0f, "Type-A-75kWh"));
    stations[4].addBattery(Battery("BS010", "LFP", 60.0f, "Type-C-60kWh"));

    // Rate station spare batteries (all fresh - high ratings)
    for (int i = 0; i < 10; i++) {
        std::string sid = "S00" + std::to_string(i < 9 ? i + 1 : 10);
        for (auto& s : stations) {
            if (s.getStationId() == sid) {
                auto bats = s.getAvailableBatteries();
                for (auto b : bats) {
                    BatteryRating r("R-" + b.getBatteryId(), "station", b.getBatteryId(),
                        96.0f, 100, 0);
                }
            }
        }
    }

    std::cout << "[Demo data loaded: 10 vehicles, 10 batteries, 10 stations]\n";
}

// -------------------------------------------------------
// Main
// -------------------------------------------------------
int main() {
    std::vector<Vehicle>     vehicles;
    std::vector<Battery>     batteries;
    std::vector<SwapStation> stations;

    prepopulate(vehicles, batteries, stations);

    int choice;

    do {
        std::cout << "\n=============================\n";
        std::cout << "   EV Battery Swap Platform\n";
        std::cout << "=============================\n";
        std::cout << " 1.  Create a vehicle\n";
        std::cout << " 2.  Create a battery\n";
        std::cout << " 3.  Create a swap station\n";
        std::cout << " 4.  Install battery onto vehicle\n";
        std::cout << " 5.  Check battery status\n";
        std::cout << " 6.  Rate a battery\n";
        std::cout << " 7.  View all vehicles\n";
        std::cout << " 8.  View all batteries\n";
        std::cout << " 9.  View all swap stations\n";
        std::cout << " 0.  Exit\n";
        std::cout << "-----------------------------\n";

        choice = getInt("Choice: ");

        switch (choice) {

            // ----- Create vehicle -----
        case 1: {
            std::string id = getString("Vehicle ID            : ");
            std::string type = getString("Type (sedan/suv/truck): ");
            std::string make = getString("Make                  : ");
            std::string model = getString("Model                 : ");
            std::string slot = getString("Battery slot spec     : ");
            vehicles.push_back(Vehicle(id, type, make, model, slot));
            std::cout << "Vehicle created.\n";
            break;
        }

              // ----- Create battery -----
        case 2: {
            std::string id = getString("Battery ID       : ");
            std::string type = getString("Type             : ");
            float cap = getFloat("Capacity (kWh)   : ");
            std::string slot = getString("Compatible slot  : ");
            batteries.push_back(Battery(id, type, cap, slot));
            std::cout << "Battery created with default rating 3/5.\n";
            break;
        }

              // ----- Create swap station -----
        case 3: {
            std::string id = getString("Station ID  : ");
            std::string name = getString("Name        : ");
            double lat = getDouble("Latitude    : ");
            double lng = getDouble("Longitude   : ");
            stations.push_back(SwapStation(id, name, lat, lng));
            std::cout << "Swap station created.\n";

            // Add batteries to this station's inventory
            char addMore = 'y';
            while (addMore == 'y' || addMore == 'Y') {
                std::string bid = getString("Add battery ID to station (or 'none'): ");
                if (bid != "none") {
                    Battery* b = findBattery(batteries, bid);
                    if (b) {
                        stations.back().addBattery(*b);
                        std::cout << "Battery added to station.\n";
                    }
                    else {
                        std::cout << "Battery not found.\n";
                    }
                }
                std::cout << "Add another? (y/n): ";
                std::cin >> addMore;
            }
            break;
        }

              // ----- Install battery onto vehicle -----
        case 4: {
            std::string vid = getString("Vehicle ID : ");
            std::string bid = getString("Battery ID : ");

            Vehicle* v = findVehicle(vehicles, vid);
            Battery* b = findBattery(batteries, bid);

            if (!v) { std::cout << "Vehicle not found.\n"; break; }
            if (!b) { std::cout << "Battery not found.\n"; break; }

            if (!b->isCompatibleWith(v->getBatterySlotSpec())) {
                std::cout << "Battery slot mismatch. Cannot install.\n";
                break;
            }

            try {
                v->installBattery(bid);
                std::cout << "Battery " << bid << " installed on vehicle " << vid << ".\n";
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        }

              // ----- Check battery status -----
        case 5: {
            std::string vid = getString("Vehicle ID: ");
            Vehicle* v = findVehicle(vehicles, vid);
            if (!v) { std::cout << "Vehicle not found.\n"; break; }

            std::string bid = v->getCurrentBatteryId();
            if (bid.empty()) { std::cout << "No battery installed on this vehicle.\n"; break; }

            Battery* b = findBattery(batteries, bid);
            if (!b) { std::cout << "Battery record not found.\n"; break; }

            float soc = getFloat("Current charge level (0-100%): ");

            std::cout << "\n  Battery ID : " << b->getBatteryId() << "\n";
            std::cout << "  Condition  : " << b->getConditionLabel() << "\n";
            std::cout << "  Rating     : " << b->getRating() << "/5\n";
            std::cout << "  Charge     : " << soc << "%\n";

            if (soc < 25.0f) {
                std::cout << "\n  [!] Battery below 25% - finding nearest swap station...\n";

                double lat = getDouble("  Your latitude  : ");
                double lng = getDouble("  Your longitude : ");

                const SwapStation* nearest = SwapStation::findNearest(
                    stations, lat, lng,
                    v->getBatterySlotSpec(),
                    v->getOwnerRating()
                );

                if (nearest) {
                    double dist = nearest->distanceTo(lat, lng);
                    std::cout << "\n  Nearest station : " << nearest->getName() << "\n";
                    std::cout << "  Station ID      : " << nearest->getStationId() << "\n";
                    std::cout << "  Distance        : " << dist << " miles\n";
                    std::cout << "  Swap token      : " << v->requestSwap() << "\n";
                }
                else {
                    std::cout << "\n  No compatible swap station found nearby.\n";
                }
            }
            else {
                std::cout << "  Battery level OK. No swap needed.\n";
            }
            break;
        }

              // ----- Rate a battery -----
        case 6: {
            std::string bid = getString("Battery ID             : ");
            float cap = getFloat("Capacity remaining (%) : ");
            int cycles = getInt("Charge cycles          : ");
            int tempEvents = getInt("Temp abuse events      : ");
            std::string ownerId = getString("Owner ID               : ");

            Battery* b = findBattery(batteries, bid);
            if (!b) { std::cout << "Battery not found.\n"; break; }

            BatteryRating rating("R-" + bid, ownerId, bid, cap, cycles, tempEvents);
            b->setRating(rating.getScore());

            std::cout << "\n  Score     : " << rating.getScore() << "/5\n";
            std::cout << "  Condition : " << rating.getCondition() << "\n";
            std::cout << "  Battery rating updated.\n";
            break;
        }

              // ----- View all vehicles -----
        case 7:
            if (vehicles.empty()) { std::cout << "No vehicles.\n"; break; }
            for (const auto& v : vehicles) {
                std::cout << "\n  " << v.getVehicleId()
                    << " | " << v.getMake() << " " << v.getModel()
                    << " | Slot: " << v.getBatterySlotSpec()
                    << " | Battery: " << (v.getCurrentBatteryId().empty() ? "none" : v.getCurrentBatteryId())
                    << " | Rating: " << v.getOwnerRating() << "/5\n";
            }
            break;

            // ----- View all batteries -----
        case 8:
            if (batteries.empty()) { std::cout << "No batteries.\n"; break; }
            for (const auto& b : batteries) {
                std::cout << "\n  " << b.getBatteryId()
                    << " | " << b.getType()
                    << " | " << b.getCapacityKwh() << " kWh"
                    << " | Rating: " << b.getRating() << "/5"
                    << " | " << b.getConditionLabel() << "\n";
            }
            break;

            // ----- View all swap stations -----
        case 9:
            if (stations.empty()) { std::cout << "No stations.\n"; break; }
            for (const auto& s : stations) {
                std::cout << "\n  " << s.getStationId()
                    << " | " << s.getName()
                    << " | Lat: " << s.getLatitude()
                    << " Lng: " << s.getLongitude()
                    << " | Batteries: " << s.getAvailableBatteries().size() << "\n";
            }
            break;

        case 0:
            std::cout << "Goodbye.\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}