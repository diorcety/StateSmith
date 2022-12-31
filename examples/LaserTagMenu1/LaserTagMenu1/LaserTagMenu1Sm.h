// Autogenerated with StateSmith
#pragma once
#include <stdint.h>
// any text you put in IRenderConfigC.HFileIncludes (like this comment) will be written to the generated .h file

enum LaserTagMenu1Sm_EventId
{
    LaserTagMenu1Sm_EventId_DO = 0, // The `do` event is special. State event handlers do not consume this event (ancestors all get it too) unless a transition occurs.
    LaserTagMenu1Sm_EventId_BACK_HELD = 1,
    LaserTagMenu1Sm_EventId_BACK_PRESS = 2,
    LaserTagMenu1Sm_EventId_DOWN_HELD = 3,
    LaserTagMenu1Sm_EventId_DOWN_PRESS = 4,
    LaserTagMenu1Sm_EventId_OK_PRESS = 5,
    LaserTagMenu1Sm_EventId_UP_HELD = 6,
    LaserTagMenu1Sm_EventId_UP_PRESS = 7,
};

enum
{
    LaserTagMenu1Sm_EventIdCount = 8
};

enum LaserTagMenu1Sm_StateId
{
    LaserTagMenu1Sm_StateId_ROOT = 0,
    LaserTagMenu1Sm_StateId_HOME = 1,
    LaserTagMenu1Sm_StateId_HOME1 = 2,
    LaserTagMenu1Sm_StateId_HOME2 = 3,
    LaserTagMenu1Sm_StateId_HOME3 = 4,
    LaserTagMenu1Sm_StateId_MENUS_GROUP = 5,
    LaserTagMenu1Sm_StateId_CLASS_SAVED = 6,
    LaserTagMenu1Sm_StateId_MAIN_MENU = 7,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_OPTION = 8,
    LaserTagMenu1Sm_StateId_MM_SELECT_CLASS_OPTION = 9,
    LaserTagMenu1Sm_StateId_MM_SHOW_INFO_OPTION = 10,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER = 11,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_1 = 12,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_2 = 13,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_3 = 14,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_4 = 15,
    LaserTagMenu1Sm_StateId_MM_BACK_PRESS_EATER_5 = 16,
    LaserTagMenu1Sm_StateId_MM_SELECT_CLASS = 17,
    LaserTagMenu1Sm_StateId_MM_SC_ENGINEER = 18,
    LaserTagMenu1Sm_StateId_MM_SC_MID = 19,
    LaserTagMenu1Sm_StateId_MM_SC_ARCHER = 20,
    LaserTagMenu1Sm_StateId_MM_SC_HEAVY = 21,
    LaserTagMenu1Sm_StateId_MM_SC_WIZARD = 22,
    LaserTagMenu1Sm_StateId_MM_SC_SPY = 23,
    LaserTagMenu1Sm_StateId_MM_SHOW_INFO = 24,
    LaserTagMenu1Sm_StateId_MM_SHOW_INFO_1 = 25,
    LaserTagMenu1Sm_StateId_MM_SHOW_INFO_2 = 26,
    LaserTagMenu1Sm_StateId_MM_SHOW_INFO_3 = 27,
    LaserTagMenu1Sm_StateId_WELCOME_SCREEN = 28,
};

enum
{
    LaserTagMenu1Sm_StateIdCount = 29
};

typedef struct LaserTagMenu1Sm LaserTagMenu1Sm;
typedef void (*LaserTagMenu1Sm_Func)(LaserTagMenu1Sm* sm);

struct LaserTagMenu1Sm
{
    // Used internally by state machine. Feel free to inspect, but don't modify.
    enum LaserTagMenu1Sm_StateId state_id;
    
    // Used internally by state machine. Don't modify.
    LaserTagMenu1Sm_Func ancestor_event_handler;
    
    // Used internally by state machine. Don't modify.
    LaserTagMenu1Sm_Func current_event_handlers[LaserTagMenu1Sm_EventIdCount];
    
    // Used internally by state machine. Don't modify.
    LaserTagMenu1Sm_Func current_state_exit_handler;
    
    // User variables. Can be used for inputs, outputs, user variables...
    struct
    {
        uint8_t option_value;
        uint8_t back_press_eat_count;
        uint32_t timer1_started_at_ms;
    } vars;
};

// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void LaserTagMenu1Sm_ctor(LaserTagMenu1Sm* self);

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void LaserTagMenu1Sm_start(LaserTagMenu1Sm* self);

// Dispatches an event to the state machine. Not thread safe.
void LaserTagMenu1Sm_dispatch_event(LaserTagMenu1Sm* self, enum LaserTagMenu1Sm_EventId event_id);

// Converts a state id to a string. Thread safe.
const char* LaserTagMenu1Sm_state_id_to_string(const enum LaserTagMenu1Sm_StateId id);

