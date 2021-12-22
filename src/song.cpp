#include "song.hpp"

Song::Song(const uint16_t * notesArr, const uint8_t& n) : notes(notesArr), size(n), currentPitchIdx(0) {}

void Song::prev()  { currentPitchIdx = max(0, currentPitchIdx -1);         }
void Song::next()  { currentPitchIdx = min(size - 1, currentPitchIdx + 1); }
void Song::reset() { currentPitchIdx = 0; }

bool Song::isFinished() const { return (currentPitchIdx == size - 1); }
const uint16_t& Song::getCurrentPitch() const { return notes[currentPitchIdx]; }

