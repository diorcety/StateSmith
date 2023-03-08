// Autogenerated with StateSmith
// Autogenerated with StateSmith
#pragma once
#include <stdint.h>

// any text you put in IRenderConfigC.HFileIncludes (like this comment) will be written to the generated .h file
typedef enum __attribute__((packed)) ButtonSm1Cpp_EventId
{
    ButtonSm1Cpp_EventId_DO = 0, // The `do` event is special. State event handlers do not consume this event (ancestors all get it too) unless a transition occurs.
} ButtonSm1Cpp_EventId;

enum
{
    ButtonSm1Cpp_EventIdCount = 1
};

typedef enum __attribute__((packed)) ButtonSm1Cpp_StateId
{
    ButtonSm1Cpp_StateId_ROOT = 0,
    ButtonSm1Cpp_StateId_NOT_PRESSED = 1,
    ButtonSm1Cpp_StateId_PRESSED = 2,
    ButtonSm1Cpp_StateId_CONFIRMING_HELD = 3,
    ButtonSm1Cpp_StateId_HELD = 4,
} ButtonSm1Cpp_StateId;

enum
{
    ButtonSm1Cpp_StateIdCount = 5
};


// Generated state machine
// forward declaration
typedef struct ButtonSm1Cpp ButtonSm1Cpp;

// State machine variables. Can be used for inputs, outputs, user variables...
typedef struct ButtonSm1Cpp_Vars
{
    // Note! This example below uses bitfields just to show that you can. They aren't required.
    
    // This can be made to be 11 bits if RAM is at a premium. See laser tag menu example.
    uint32_t debounce_started_at_ms;
    
    uint16_t input_is_pressed : 1; // input
    uint16_t output_event_press : 1; // output
    uint16_t output_event_release : 1; // output
    uint16_t output_event_held : 1; // output
    uint16_t output_event_tap : 1; // output
} ButtonSm1Cpp_Vars;


// event handler type
typedef void (*ButtonSm1Cpp_Func)(ButtonSm1Cpp* sm);

// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void ButtonSm1Cpp_ctor(ButtonSm1Cpp* sm);

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void ButtonSm1Cpp_start(ButtonSm1Cpp* sm);

// Dispatches an event to the state machine. Not thread safe.
void ButtonSm1Cpp_dispatch_event(ButtonSm1Cpp* sm, ButtonSm1Cpp_EventId event_id);

// Thread safe.
char const * const ButtonSm1Cpp_state_id_to_string(ButtonSm1Cpp_StateId id);

// Thread safe.
char const * const ButtonSm1Cpp_event_id_to_string(ButtonSm1Cpp_EventId id);

// Generated state machine
struct ButtonSm1Cpp
{
    // Used internally by state machine. Feel free to inspect, but don't modify.
    ButtonSm1Cpp_StateId state_id;
    
    // Used internally by state machine. Don't modify.
    ButtonSm1Cpp_Func ancestor_event_handler;
    
    // Used internally by state machine. Don't modify.
    ButtonSm1Cpp_Func current_event_handlers[ButtonSm1Cpp_EventIdCount];
    
    // Used internally by state machine. Don't modify.
    ButtonSm1Cpp_Func current_state_exit_handler;
    
    // Variables. Can be used for inputs, outputs, user variables...
    ButtonSm1Cpp_Vars vars;
};

