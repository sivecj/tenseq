/*
 * Clock stuff
 */

#include <uClock.h>

unsigned long note_off_millis;
elapsedMillis tMillis;

/* Callback function for 16 pulses per quarter note */
void clock_run_16_ppqn(uint32_t *tick)
{
    seq.run_sequence_step();
    midi_send_sequence_note();
    note_off_millis = (1000.0/((DEFAULT_BPM/60.0)*4.0))*(GATE_LENGTH/100.0) + tMillis;
}

void clock_init()
{
    note_off_millis = 0;

    uClock.init();
    uClock.setClock16PPQNOutput(clock_run_16_ppqn);
    //uClock.setOnClockStartOutput(onClockStart);
    //uClock.setOnClockStopOutput(onClockStop);
    uClock.setTempo(DEFAULT_BPM);
    uClock.start();
}
