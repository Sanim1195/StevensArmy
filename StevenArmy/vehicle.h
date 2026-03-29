#pragma once
#include <string>

class Vehicle {
public:
    Vehicle(const std::string& vehicleId,
        const std::string& type,
        const std::string& make,
        const std::string& model,
        const std::string& batterySlotSpec);

    // Getters
    std::string getVehicleId() const;
    std::string getType() const;       // "sedan" | "suv" | "truck" | "motorcycle" etc.
    std::string getMake() const;
    std::string getModel() const;
    std::string getBatterySlotSpec() const;
    std::string getCurrentBatteryId() const;
    int getOwnerRating() const;

    // Setters
    void installBattery(const std::string& batteryId);
    void setOwnerRating(int rating);

    // Returns true if this vehicle can accept the given slot spec
    bool canAcceptSlot(const std::string& slotSpec) const;

    // Initiates a swap request — returns a request token string
    std::string requestSwap() const;

private:
    std::string vehicleId;
    std::string type;
    std::string make;
    std::string model;
    std::string batterySlotSpec;    // e.g. "Type-A-75kWh"
    std::string currentBatteryId;
    int ownerRating;                // 1–5, pulled from latest BatteryRating
};
