/*
 * tenseq: Teensy sequencer
 * Notes:
 *  - Midi note '0' is used as "no note"
 */

// Define settings
#define MIDI_INPUT_DEFAULT_CHANNEL 1
#define MIDI_OUTPUT_DEFAULT_CHANNEL 1
#define DEFAULT_BPM 120
#define GATE_LENGTH 50  // Like the "Gate" feature on the Arturia Keystep, in %
#define DEFAULT_DIV 16
#define DEFAULT_STEP_SIZE_SEQ 32
#define DEFAULT_STEP_SIZE_DRUM 32
#define DEBOUNCE_TIME 40
#define SERIAL_RATE 9600

// Define either sequencer or drum mode
//#define SEQ_MODE
#define DRUM_MODE

#include "src/Sequencer/Sequencer.h"

Sequencer seq;

void setup()
{
    delay(1000);
    Serial.begin(SERIAL_RATE);

#ifdef SEQ_MODE
    seq.set_sequence_mode(Sequencer::sequence_mode::SEQUENCE);
    seq.set_sequence_step_size(DEFAULT_STEP_SIZE_SEQ);
#endif
#ifdef DRUM_MODE
    seq.set_sequence_mode(Sequencer::sequence_mode::DRUM);
    seq.set_sequence_step_size(DEFAULT_STEP_SIZE_DRUM);
#endif

    hardware_init();
    midi_init();
    clock_init();
}

void loop()
{
    midi_run_procedure();
}
