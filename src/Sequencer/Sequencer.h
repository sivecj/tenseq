#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>

#define MAX_SEQUENCE_SIZE 64

class Sequencer {
public:
	Sequencer();

	struct midi_note {
		byte note;
		byte velocity;
	};

	byte get_note_sequence_coll_size();
	void set_sequence_size(const byte& size);
	void add_sequence_note(const midi_note& note);
	midi_note get_sequence_note();
	void run_sequence_step();
private:
	midi_note note_sequence_coll[MAX_SEQUENCE_SIZE]; // Note & velocity
	byte note_sequence_coll_size;
	byte sequence_step;
	byte sequence_size;
};

#endif /* SEQUENCER_H */
