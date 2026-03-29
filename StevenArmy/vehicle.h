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
	std::string vehicleId;   // gg: "V-1234"
	std::string type; 	 // "sedan" | "suv" | "truck" | "motorcycle" etc. (could be used for filtering stations)
	std::string make;  // e.g. "Tesla"
	std::string model; // e.g. "Model 3"
    std::string batterySlotSpec;    // e.g. "Type-A-75kWh"
    std::string currentBatteryId; // empty stringif no battery is installed
    int ownerRating;                // 1–5, pulled from latest BatteryRating
};