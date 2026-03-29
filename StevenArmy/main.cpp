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
// Main
// -------------------------------------------------------
int main() {
    std::vector<Vehicle>     vehicles;
    std::vector<Battery>     batteries;
    std::vector<SwapStation> stations;

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