/*
 * MIDI stuff
 */

static bool is_note_active;

void midi_cb_note_on(byte channel, byte note, byte velocity)
{
    if (!is_note_active) {
        is_note_active = true;
        Sequencer::midi_note n;
        n.note = note;
        n.velocity = velocity;
        seq.add_sequence_note(n);
    }
}

void midi_cb_note_off(byte channel, byte note, byte velocity)
{
    is_note_active = false;
}

void midi_send_sequence_note()
{
    Sequencer::midi_note n = seq.get_sequence_note();
    usbMIDI.sendNoteOn(n.note, n.velocity, MIDI_OUTPUT_DEFAULT_CHANNEL);
}

/* Execute MIDI related stuff on every loop() */
void midi_run_procedure()
{
    usbMIDI.read(MIDI_INPUT_DEFAULT_CHANNEL);

    // Check if the "no note" button is pressed
    if (hardware_check_button(2) && !is_note_active) {
        midi_cb_note_on(MIDI_INPUT_DEFAULT_CHANNEL, 0, 0);
        midi_cb_note_off(MIDI_INPUT_DEFAULT_CHANNEL, 0, 0);
    }

    // Check
    if (note_off_millis != 0 && tMillis >= note_off_millis) {
        Sequencer::midi_note n = seq.get_sequence_note();
        usbMIDI.sendNoteOff(n.note, 0, MIDI_OUTPUT_DEFAULT_CHANNEL);
        note_off_millis = 0;
    }
}

void midi_init()
{
    is_note_active = false;

    // functions for usbMIDI...
    usbMIDI.setHandleNoteOn(midi_cb_note_on);
    usbMIDI.setHandleNoteOff(midi_cb_note_off);
}
