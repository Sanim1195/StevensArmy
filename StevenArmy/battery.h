#pragma once
#include <string>
#include <vector> 



class Battery {
public:
    Battery(const std::string& batteryId,
        const std::string& type,
        float capacityKwh,
        const std::string& compatibleSlots);

    // Getters
    std::string getBatteryId() const;
    std::string getType() const;
    float getCapacityKwh() const;
    int getRating() const;
    std::string getCompatibleSlots() const;

    // Setters
    void setRating(int rating);

    // Returns human-readable condition label from rating
    std::string getConditionLabel() const;

    // Checks if this battery fits a given slot spec
    bool isCompatibleWith(const std::string& slotSpec) const;

private:
    std::string batteryId;
    std::string type;
    float capacityKwh;
    int rating;           // 1–5
    std::string compatibleSlots;
};