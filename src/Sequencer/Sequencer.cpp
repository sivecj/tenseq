#include "Sequencer.h"

Sequencer::Sequencer()
{
    sequence_step_size = MAX_SEQUENCE_SIZE;
    note_sequence_coll_size = 0;
    sequence_step = 0;
}

byte Sequencer::get_note_sequence_coll_size()
{
	return note_sequence_coll_size;
}

byte Sequencer::get_sequence_step()
{
	return sequence_step;
}

void Sequencer::set_sequence_mode(sequence_mode mode)
{
	sequence_set_mode = mode;
}

void Sequencer::set_sequence_step_size(const byte& sequence_step_size)
{
    if (sequence_step_size <= MAX_SEQUENCE_SIZE)
        Sequencer::sequence_step_size = sequence_step_size;
}

void Sequencer::add_sequence_note(const midi_note& note)
{
	byte size = get_note_sequence_coll_size();

	if (size < sequence_step_size) {
		note_sequence_coll[size] = note;
		note_sequence_coll_size++;
	}
}

void Sequencer::set_sequence_note(const midi_note& note)
{
	note_sequence_coll[sequence_step] = note;
}

Sequencer::midi_note Sequencer::get_sequence_note()
{
	return note_sequence_coll[sequence_step];
}

void Sequencer::run_sequence_step()
{
	byte size;
	if (sequence_set_mode == Sequencer::sequence_mode::SEQUENCE)
		size = get_note_sequence_coll_size();
	else if (sequence_set_mode == Sequencer::sequence_mode::DRUM)
		size = sequence_step_size;
	if (size == 0)
		return;

	if (sequence_step >= size-1)
		sequence_step = 0;
	else
		sequence_step++;
}
