#pragma once
#include <string>
#include <vector>
#include "Battery.h"

class SwapStation {
public:
    SwapStation(const std::string& stationId,
        const std::string& name,
        double latitude,
        double longitude);

    // Getters
    std::string getStationId() const;
    std::string getName() const;
    double getLatitude() const;
    double getLongitude() const;
    const std::vector<Battery>& getAvailableBatteries() const;

    // Inventory management
    void addBattery(const Battery& battery);
    void removeBattery(const std::string& batteryId);

    // Returns distance in kilometers from this station to given coordinates
    // Uses the Haversine formula
    double distanceTo(double lat, double lng) const;

    // Returns true if this station has a battery matching the slot spec AND rating tier
    bool hasCompatible(const std::string& slotSpec, int minRating) const;

    // Finds the nearest SwapStation from a list that has a compatible battery
    // Returns a pointer to the best match, or nullptr if none found
    static const SwapStation* findNearest(const std::vector<SwapStation>& stations,
        double vehicleLat,
        double vehicleLng,
        const std::string& slotSpec,
        int minRating);

private:
    std::string stationId;
    std::string name;
    double latitude;
    double longitude;
	// For simplicity, we store batteries directly in the station. In a real system, this might be more complex.
    std::vector<Battery> availableBatteries;


};