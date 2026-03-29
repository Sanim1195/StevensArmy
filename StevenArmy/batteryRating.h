#pragma once
#include <string>

class BatteryRating {
public:
    BatteryRating(const std::string& ratingId,
        const std::string& ownerId,
        const std::string& batteryId,
        float capacityRemainingPct,
        int chargeCycles,
        int tempAbuseEvents);

    // Getters
    std::string getRatingId() const;
    std::string getOwnerId() const;
    std::string getBatteryId() const;
    int getScore() const;
    std::string getCondition() const;

    // Core algorithm: derives 1–5 score from battery health signals
    // Weights: capacity 60%, charge cycles 25%, temp abuse 15%
    int calcScore() const;

private:
    std::string ratingId;
    std::string ownerId;
    std::string batteryId;
    int score;               // 1–5, computed by calcScore()
    std::string condition;   // "new" | "good" | "fair" | "degraded" | "poor"

    float capacityRemainingPct;  // 0.0 – 100.0
    int chargeCycles;            // total full cycles completed
    int tempAbuseEvents;         // count of out-of-range temperature events

    std::string conditionFromScore(int s) const;
}; 
