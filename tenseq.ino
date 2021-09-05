/*
 * tenseq: Teensy sequencer
 * Notes:
 *  - Midi note '0' is used as "no note"
 */

// Define settings
#define MIDI_INPUT_DEFAULT_CHANNEL 2
#define MIDI_OUTPUT_DEFAULT_CHANNEL 1
#define DEFAULT_BPM 120
#define GATE_LENGTH 50  // Like the "Gate" feature on the Arturia Keystep, in %
#define DEFAULT_DIV 16
#define DEFAULT_STEP_SIZE 32
#define DEBOUNCE_TIME 40
#define SERIAL_RATE 9600

#include "src/Sequencer/Sequencer.h"

Sequencer seq;

void setup()
{
    delay(1000);
    Serial.begin(SERIAL_RATE);

    seq.set_sequence_size(DEFAULT_STEP_SIZE-1);

    hardware_init();
    midi_init();
    clock_init();
}

void loop()
{
    midi_run_procedure();
}
