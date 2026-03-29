#include "Battery.h"
#include <stdexcept>


//Constructor initializes all members, with a default rating of 3 (fair condition)
Battery::Battery(const std::string& batteryId,
    const std::string& type,
    float capacityKwh,
    const std::string& compatibleSlots)
    : batteryId(batteryId),
    type(type),
    capacityKwh(capacityKwh),
    rating(3),
    compatibleSlots(compatibleSlots) {
}

// Getters
std::string Battery::getBatteryId() const { return batteryId; }
std::string Battery::getType() const { return type; }
float Battery::getCapacityKwh() const { return capacityKwh; }
int Battery::getRating() const { return rating; }
std::string Battery::getCompatibleSlots() const { return compatibleSlots; }

// Setters
void Battery::setRating(int r) {
    if (r < 1 || r > 5)
        throw std::invalid_argument("Rating must be between 1 and 5.");
    rating = r;
}

std::string Battery::getConditionLabel() const {
    switch (rating) {
    case 5: return "new";
    case 4: return "good";
    case 3: return "fair";
    case 2: return "degraded";
    case 1: return "poor";
    default: return "unknown";
    }
}

bool Battery::isCompatibleWith(const std::string& slotSpec) const {
    return compatibleSlots.find(slotSpec) != std::string::npos;
}


