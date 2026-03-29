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

std::string Vehicle::getVehicleId() const { return vehicleId; }
std::string Vehicle::getType() const { return type; }
std::string Vehicle::getMake() const { return make; }
std::string Vehicle::getModel() const { return model; }
std::string Vehicle::getBatterySlotSpec() const { return batterySlotSpec; }
std::string Vehicle::getCurrentBatteryId() const { return currentBatteryId; }
int Vehicle::getOwnerRating() const { return ownerRating; }

void Vehicle::installBattery(const std::string& batteryId) {
    if (batteryId.empty())
        throw std::invalid_argument("Battery ID cannot be empty.");
    currentBatteryId = batteryId;
}

void Vehicle::setOwnerRating(int rating) {
    if (rating < 1 || rating > 5)
        throw std::invalid_argument("Owner rating must be between 1 and 5.");
    ownerRating = rating;
}

bool Vehicle::canAcceptSlot(const std::string& slotSpec) const {
    return batterySlotSpec == slotSpec;
}

std::string Vehicle::requestSwap() const {
    // Generates a simple swap request token:
    // "<vehicleId>-<batterySlotSpec>-<ownerRating>"
    // In production this would call a SwapService and return a full request ID
    return vehicleId + "-" + batterySlotSpec + "-" + std::to_string(ownerRating);
}