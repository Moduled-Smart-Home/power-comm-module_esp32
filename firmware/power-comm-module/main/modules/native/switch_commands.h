#ifndef SWITCH_COMMANDS_H
#define SWITCH_COMMANDS_H

void initialize_switch_commands();

typedef enum {
    IDLE,
    WAIT_SHORT,
    WAIT_LONG
} switch_command_state_enum;

#endif