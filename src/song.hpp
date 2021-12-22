#ifndef SONG_HPP
#define SONG_HPP
#include <Arduino.h>
#include <stdint.h>

class Song {
  private:
    const uint16_t * notes;
    const uint8_t    size;
    uint8_t currentPitchIdx;
  public:
    Song(const uint16_t *, const uint8_t&);

    void prev();
    void next();
    void reset();
    bool isFinished() const;
    const uint16_t& getCurrentPitch() const;

};


#endif
