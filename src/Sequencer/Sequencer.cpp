#include "Sequencer.h"

Sequencer::Sequencer()
{
    Sequencer::sequence_size = MAX_SEQUENCE_SIZE;
    note_sequence_coll_size = 0;
    sequence_step = 0;
}

byte Sequencer::get_note_sequence_coll_size()
{
	return note_sequence_coll_size;
}

void Sequencer::set_sequence_size(const byte& sequence_size)
{
    if (sequence_size <= MAX_SEQUENCE_SIZE)
        Sequencer::sequence_size = sequence_size;
}

void Sequencer::add_sequence_note(const midi_note& note)
{
	byte size = get_note_sequence_coll_size();

	if (size < sequence_size) {
		note_sequence_coll[size] = note;
		note_sequence_coll_size++;
	}
}

Sequencer::midi_note Sequencer::get_sequence_note()
{
	return note_sequence_coll[sequence_step];
}

void Sequencer::run_sequence_step()
{
	byte size = get_note_sequence_coll_size();
	if (size == 0)
		return;

	if (sequence_step < size-1)
		sequence_step++;
	else if(sequence_step == size-1)
		sequence_step = 0;
}
