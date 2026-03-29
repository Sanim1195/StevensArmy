#include "SwapStation.h"
#include <cmath>
#include <algorithm>
#include <limits>
#include <stdexcept>

static constexpr double PI = 3.14159265358979323846;

static double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

SwapStation::SwapStation(const std::string& stationId,
    const std::string& name,
    double latitude,
    double longitude)
    : stationId(stationId),
    name(name),
    latitude(latitude),
    longitude(longitude) {
}

std::string SwapStation::getStationId() const { return stationId; }
std::string SwapStation::getName() const { return name; }
double SwapStation::getLatitude() const { return latitude; }
double SwapStation::getLongitude() const { return longitude; }
const std::vector<Battery>& SwapStation::getAvailableBatteries() const {
    return availableBatteries;
}

void SwapStation::addBattery(const Battery& battery) {
    availableBatteries.push_back(battery);
}

void SwapStation::removeBattery(const std::string& batteryId) {
    auto it = std::remove_if(availableBatteries.begin(), availableBatteries.end(),
        [&batteryId](const Battery& b) {
            return b.getBatteryId() == batteryId;
        });
    if (it == availableBatteries.end())
        throw std::runtime_error("Battery not found: " + batteryId);
    availableBatteries.erase(it, availableBatteries.end());
}

double SwapStation::distanceTo(double lat, double lng) const {
    // Haversine formula — accurate to within ~0.5% for typical distances
    double dLat = toRadians(lat - latitude);
    double dLng = toRadians(lng - longitude);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2)
        + std::cos(toRadians(latitude)) * std::cos(toRadians(lat))
        * std::sin(dLng / 2) * std::sin(dLng / 2);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
    return EARTH_RADIUS_KM * c;
}

bool SwapStation::hasCompatible(const std::string& slotSpec, int minRating) const {
    for (const auto& battery : availableBatteries) {
        if (battery.isCompatibleWith(slotSpec) && battery.getRating() >= minRating)
            return true;
    }
    return false;
}

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