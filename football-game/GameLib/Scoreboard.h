/**
 * @file Scoreboard.h
 * @author Brennan Eagle
 *
 *
 */
 
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard
{
private:
    ///StopWatch to track time
    wxStopWatch* mStopWatch = nullptr;
    ///Current score
    double mScore = 0;
    ///Time since last score
    long mLastScore = 0;
    ///Point decay over time
    const double mDecay = 1.;
    ///PowerUp active?
    bool mPowerUp = false;
    ///Time power up started
    long mPowerUpStart = 0;
    ///power up duration
    const long mPowerUpDuration = 10000;

public:
    Scoreboard();

    void Initialize(wxStopWatch* stopWatch);
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);
    void Update(double elapsed);
    void Reset();
    /**
     * Add points to score
     * @param points to add
     */
    void AddScore(int points);
    /**
     * Get Score
     * @return current score
     */
    int GetScore() const { return static_cast<int>(mScore); }

    void PowerUp();
    /**
     * Check if power up is active
     * @return mPowerUp
     */
    bool isPowered() const { return mPowerUp; }
};



#endif //SCOREBOARD_H
