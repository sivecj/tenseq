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

	enum sequence_mode {
		SEQUENCE,
		DRUM,
	};

	byte get_note_sequence_coll_size();
	byte get_sequence_step();
	void set_sequence_mode(sequence_mode mode);
	void set_sequence_step_size(const byte& size);
	void add_sequence_note(const midi_note& note);
	void set_sequence_note(const midi_note& note);
	midi_note get_sequence_note();
	void run_sequence_step();
private:
	midi_note note_sequence_coll[MAX_SEQUENCE_SIZE]; // Note & velocity
	byte note_sequence_coll_size;
	byte sequence_step;
	byte sequence_step_size;
	sequence_mode sequence_set_mode;
};
#endif /* SEQUENCER_H */
