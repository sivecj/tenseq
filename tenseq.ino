/*
 * tenseq: Teensy sequencer
 * Notes:
 *  - Midi note '0' is used as "no note"
 */

#include <Bounce.h>
#include <uClock.h>

// Define settings
#define MIDI_INPUT_DEFAULT_CHANNEL 2
#define MIDI_OUTPUT_DEFAULT_CHANNEL 1
#define DEFAULT_BPM 120
#define GATE_LENGTH 50  // Like the "Gate" feature on the Arturia Keystep, in %
#define DEFAULT_DIV 16
#define BUTTON_EMPTY_NOTE 2
#define MAX_STEPS_SIZE 32
#define DEBOUNCE_TIME 40
#define SERIAL_RATE 9600

// Global vars
bool isNoteActive = false;
byte midi_array[MAX_STEPS_SIZE][2];  // 32 Steps - midi note & velocity
byte size_of_midi_array = 0;
byte current_step = 0;
unsigned long note_off_millis = 0;
elapsedMillis tMillis;

// Button debounce
Bounce pushbutton = Bounce(BUTTON_EMPTY_NOTE, DEBOUNCE_TIME);

void runSequence()
{
    if (size_of_midi_array == 0)
        return;

    if (current_step < size_of_midi_array-1)
        current_step++;
    else if (current_step == size_of_midi_array-1)
        current_step = 0;

    usbMIDI.sendNoteOn(midi_array[current_step][0], midi_array[current_step][1],
                       MIDI_OUTPUT_DEFAULT_CHANNEL);
}

void myNoteOn(byte channel, byte note, byte velocity)
{
    if (size_of_midi_array != 31 && !isNoteActive) {
        isNoteActive = true;
        midi_array[size_of_midi_array][0] = note;
        midi_array[size_of_midi_array][1] = velocity;
        size_of_midi_array++;
    }
}

void myNoteOff(byte channel, byte note, byte velocity)
{
    isNoteActive = false;
}

void ClockOut16PPQN(uint32_t *tick)
{
    runSequence();
    note_off_millis = (1000/((DEFAULT_BPM/60)*4))*(GATE_LENGTH/100.0) + tMillis;
}

void initClock()
{
    uClock.init();
    uClock.setClock16PPQNOutput(ClockOut16PPQN);
    //uClock.setOnClockStartOutput(onClockStart);
    //uClock.setOnClockStopOutput(onClockStop);
    uClock.setTempo(DEFAULT_BPM);
    uClock.start();
}

void setup() {
    usbMIDI.setHandleNoteOff(myNoteOff);
    usbMIDI.setHandleNoteOn(myNoteOn);

    pinMode(BUTTON_EMPTY_NOTE, INPUT_PULLUP);

    Serial.begin(SERIAL_RATE);

    initClock();
}

void loop() {
    usbMIDI.read(MIDI_INPUT_DEFAULT_CHANNEL);

    if (pushbutton.update() && pushbutton.fallingEdge() && !isNoteActive) {
        myNoteOn(MIDI_INPUT_DEFAULT_CHANNEL, 0, 0);
        myNoteOff(MIDI_INPUT_DEFAULT_CHANNEL, 0, 0);
    }

    if (note_off_millis != 0 && tMillis >= note_off_millis) {
        usbMIDI.sendNoteOff(midi_array[current_step][0], 0,
                            MIDI_OUTPUT_DEFAULT_CHANNEL);
        note_off_millis = 0;
    }
}
