#include "Vehicle.h"
#include <stdexcept>

Vehicle::Vehicle(const std::string& vehicleId,
    const std::string& type,
    const std::string& make,
    const std::string& model,
    const std::string& batterySlotSpec)
    : vehicleId(vehicleId),
    type(type),
    make(make),
    model(model),
    batterySlotSpec(batterySlotSpec),
    currentBatteryId(""),
    ownerRating(3) {
}

//
std::string Vehicle::getVehicleId() const { return vehicleId; }

std::string Vehicle::getType() const { return type; }

std::string Vehicle::getMake() const { return make; }

std::string Vehicle::getModel() const { return model; }

std::string Vehicle::getBatterySlotSpec() const { return batterySlotSpec; }

std::string Vehicle::getCurrentBatteryId() const { return currentBatteryId; }

int Vehicle::getOwnerRating() const { return ownerRating; }

void Vehicle::installBattery(const std::string& batteryId) {
	// In production, we would verify the battery ID exists and is compatible before installing 

    if (batteryId.empty())
        throw std::invalid_argument("Battery ID cannot be empty.");
    currentBatteryId = batteryId;
}


// Vehicle owner can rate their battery condition after a swap or over time. This is a simple setter, but in production it would likely be more complex and involve validation and possibly updating the battery's overall rating in the system.

void Vehicle::setOwnerRating(int rating) {
    if (rating < 1 || rating > 5)
        throw std::invalid_argument("Owner rating must be between 1 and 5.");
    ownerRating = rating;
}

// This method checks if the vehicle's battery slot spec matches the given slot spec. In a real system, this might involve more complex compatibility logic, but for simplicity we just check for an exact match.
bool Vehicle::canAcceptSlot(const std::string& slotSpec) const {
    return batterySlotSpec == slotSpec;
}

std::string Vehicle::requestSwap() const {
    // Generates a simple swap request token:
    // "<vehicleId>-<batterySlotSpec>-<ownerRating>"
    // In production this would call a SwapService and return a full request ID
    return vehicleId + "-" + batterySlotSpec + "-" + std::to_string(ownerRating);
}