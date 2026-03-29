#include "SwapStation.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <stdexcept>


// Constructor
SwapStation::SwapStation(const std::string& stationId,
    const std::string& name,
    double latitude,
    double longitude)
    : stationId(stationId),
    name(name),
    latitude(latitude),
    longitude(longitude) {
}

// Getters
std::string SwapStation::getStationId() const { return stationId; }
std::string SwapStation::getName() const { return name; }
double SwapStation::getLatitude() const { return latitude; }
double SwapStation::getLongitude() const { return longitude; }
const std::vector<Battery>& SwapStation::getAvailableBatteries() const {
    return availableBatteries;
}

// Inventory management
void SwapStation::addBattery(const Battery& battery) {
    availableBatteries.push_back(battery);
}


// Removes a battery by ID. Throws if not found.
void SwapStation::removeBattery(const std::string& batteryId) {
    auto it = std::remove_if(availableBatteries.begin(), availableBatteries.end(),
        [&batteryId](const Battery& b) {
            return b.getBatteryId() == batteryId;
        });
    if (it == availableBatteries.end())
        throw std::runtime_error("Battery not found: " + batteryId);
    availableBatteries.erase(it, availableBatteries.end());
}


// For simplicity, we use straight-line distance. 
double SwapStation::distanceTo(double lat, double lng) const {
    // Straight-line distance in miles (1 degree lat/lng 69 miles)
    double dLat = lat - latitude;
    double dLng = lng - longitude;
    return std::sqrt(dLat * dLat + dLng * dLng) * 69.0;
}


// Checks if this station has a compatible battery for the given slot spec and minimum rating
bool SwapStation::hasCompatible(const std::string& slotSpec, int minRating) const {
    for (const auto& battery : availableBatteries) {
        if (battery.isCompatibleWith(slotSpec) && battery.getRating() >= minRating)
            return true;
    }
    return false;
}

// Static method to find the nearest compatible station
const SwapStation* SwapStation::findNearest(const std::vector<SwapStation>& stations,
    double vehicleLat,
    double vehicleLng,
    const std::string& slotSpec,
    int minRating) {
    const SwapStation* best = nullptr;
    double bestDist = std::numeric_limits<double>::max();

    for (const auto& station : stations) {
        if (!station.hasCompatible(slotSpec, minRating))
            continue;

        double dist = station.distanceTo(vehicleLat, vehicleLng);
        if (dist < bestDist) {
            bestDist = dist;
            best = &station;
        }
    }

    return best;  // nullptr if no compatible station found
}