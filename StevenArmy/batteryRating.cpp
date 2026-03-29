#include "BatteryRating.h"
#include <cmath>
#include <stdexcept>

BatteryRating::BatteryRating(const std::string& ratingId,
    const std::string& ownerId,
    const std::string& batteryId,
    float capacityRemainingPct,
    int chargeCycles,
    int tempAbuseEvents)
    : ratingId(ratingId),
    ownerId(ownerId),
    batteryId(batteryId),
    capacityRemainingPct(capacityRemainingPct),
    chargeCycles(chargeCycles),
    tempAbuseEvents(tempAbuseEvents) {
    score = calcScore();
    condition = conditionFromScore(score);
}

std::string BatteryRating::getRatingId() const { return ratingId; }
std::string BatteryRating::getOwnerId() const { return ownerId; }
std::string BatteryRating::getBatteryId() const { return batteryId; }
int BatteryRating::getScore() const { return score; }
std::string BatteryRating::getCondition() const { return condition; }

int BatteryRating::calcScore() const {
    // --- Capacity score (60% weight) ---
    // Full capacity = 5 pts, degrades with remaining %
    int capacityScore;
    if (capacityRemainingPct >= 95.0f)      capacityScore = 5;
    else if (capacityRemainingPct >= 85.0f) capacityScore = 4;
    else if (capacityRemainingPct >= 75.0f) capacityScore = 3;
    else if (capacityRemainingPct >= 60.0f) capacityScore = 2;
    else                                    capacityScore = 1;

    // --- Cycle score (25% weight) ---
    // Typical EV battery rated for ~1500–2000 full cycles
    int cycleScore;
    if (chargeCycles < 200)       cycleScore = 5;
    else if (chargeCycles < 500)  cycleScore = 4;
    else if (chargeCycles < 900)  cycleScore = 3;
    else if (chargeCycles < 1400) cycleScore = 2;
    else                          cycleScore = 1;

    // --- Temp abuse score (15% weight) ---
    // Any temp abuse event is a red flag
    int tempScore;
    if (tempAbuseEvents == 0)      tempScore = 5;
    else if (tempAbuseEvents == 1) tempScore = 4;
    else if (tempAbuseEvents <= 3) tempScore = 3;
    else if (tempAbuseEvents <= 6) tempScore = 2;
    else                           tempScore = 1;

    // Weighted average, rounded to nearest int
    float weighted = (capacityScore * 0.60f)
        + (cycleScore * 0.25f)
        + (tempScore * 0.15f);

    int result = static_cast<int>(weighted + 0.5f);
    if (result < 1) result = 1;
    if (result > 5) result = 5;
    return result;
}

std::string BatteryRating::conditionFromScore(int s) const {
    switch (s) {
    case 5: return "new";
    case 4: return "good";
    case 3: return "fair";
    case 2: return "degraded";
    case 1: return "poor";
    default: return "unknown";
    }
}