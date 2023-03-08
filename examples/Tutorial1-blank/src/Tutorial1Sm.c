// Autogenerated with StateSmith
// Autogenerated with StateSmith
#include "Tutorial1Sm.h"
// Some user .c file comment...
#include "light.h"
#include <stdbool.h> // required for `consume_event` flag
#include <string.h> // for memset

// This function is used when StateSmith doesn't know what the active leaf state is at
// compile time due to sub states or when multiple states need to be exited.
static void exit_up_to_state_handler(Tutorial1Sm* sm, Tutorial1Sm_Func desired_state_exit_handler);

static void ROOT_enter(Tutorial1Sm* sm);

static void ROOT_exit(Tutorial1Sm* sm);

static void OFF_enter(Tutorial1Sm* sm);

static void OFF_exit(Tutorial1Sm* sm);

static void OFF_increase(Tutorial1Sm* sm);

static void ON1_enter(Tutorial1Sm* sm);

static void ON1_exit(Tutorial1Sm* sm);

static void ON1_dim(Tutorial1Sm* sm);


// State machine constructor. Must be called before start or dispatch event functions. Not thread safe.
void Tutorial1Sm_ctor(Tutorial1Sm* sm)
{
    memset(sm, 0, sizeof(*sm));
}

// Starts the state machine. Must be called before dispatching events. Not thread safe.
void Tutorial1Sm_start(Tutorial1Sm* sm)
{
    ROOT_enter(sm);
    // ROOT behavior
    // uml: TransitionTo(ROOT.InitialState)
    {
        // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition). Already at LCA, no exiting required.
        
        // Step 2: Transition action: ``.
        
        // Step 3: Enter/move towards transition target `ROOT.InitialState`.
        // ROOT.InitialState is a pseudo state and cannot have an `enter` trigger.
        
        // ROOT.InitialState behavior
        // uml: TransitionTo(OFF)
        {
            // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition). Already at LCA, no exiting required.
            
            // Step 2: Transition action: ``.
            
            // Step 3: Enter/move towards transition target `OFF`.
            OFF_enter(sm);
            
            // Step 4: complete transition. Ends event dispatch. No other behaviors are checked.
            sm->state_id = Tutorial1Sm_StateId_OFF;
            // No ancestor handles event. Can skip nulling `ancestor_event_handler`.
            return;
        } // end of behavior for ROOT.InitialState
    } // end of behavior for ROOT
}

// Dispatches an event to the state machine. Not thread safe.
void Tutorial1Sm_dispatch_event(Tutorial1Sm* sm, Tutorial1Sm_EventId event_id)
{
    Tutorial1Sm_Func behavior_func = sm->current_event_handlers[event_id];
    
    while (behavior_func != NULL)
    {
        sm->ancestor_event_handler = NULL;
        behavior_func(sm);
        behavior_func = sm->ancestor_event_handler;
    }
}

// This function is used when StateSmith doesn't know what the active leaf state is at
// compile time due to sub states or when multiple states need to be exited.
static void exit_up_to_state_handler(Tutorial1Sm* sm, Tutorial1Sm_Func desired_state_exit_handler)
{
    while (sm->current_state_exit_handler != desired_state_exit_handler)
    {
        sm->current_state_exit_handler(sm);
    }
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state ROOT
////////////////////////////////////////////////////////////////////////////////

static void ROOT_enter(Tutorial1Sm* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = ROOT_exit;
}

static void ROOT_exit(Tutorial1Sm* sm)
{
    // State machine root is a special case. It cannot be exited. Mark as unused.
    (void)sm;
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state OFF
////////////////////////////////////////////////////////////////////////////////

static void OFF_enter(Tutorial1Sm* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = OFF_exit;
    sm->current_event_handlers[Tutorial1Sm_EventId_INCREASE] = OFF_increase;
    
    // OFF behavior
    // uml: enter / { light_off(); }
    {
        // Step 1: execute action `light_off();`
        light_off();
    } // end of behavior for OFF
}

static void OFF_exit(Tutorial1Sm* sm)
{
    // adjust function pointers for this state's exit
    sm->current_state_exit_handler = ROOT_exit;
    sm->current_event_handlers[Tutorial1Sm_EventId_INCREASE] = NULL;  // no ancestor listens to this event
}

static void OFF_increase(Tutorial1Sm* sm)
{
    // No ancestor state handles `increase` event.
    
    // OFF behavior
    // uml: INCREASE TransitionTo(ON1)
    {
        // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition).
        OFF_exit(sm);
        
        // Step 2: Transition action: ``.
        
        // Step 3: Enter/move towards transition target `ON1`.
        ON1_enter(sm);
        
        // Step 4: complete transition. Ends event dispatch. No other behaviors are checked.
        sm->state_id = Tutorial1Sm_StateId_ON1;
        // No ancestor handles event. Can skip nulling `ancestor_event_handler`.
        return;
    } // end of behavior for OFF
}


////////////////////////////////////////////////////////////////////////////////
// event handlers for state ON1
////////////////////////////////////////////////////////////////////////////////

static void ON1_enter(Tutorial1Sm* sm)
{
    // setup trigger/event handlers
    sm->current_state_exit_handler = ON1_exit;
    sm->current_event_handlers[Tutorial1Sm_EventId_DIM] = ON1_dim;
    
    // ON1 behavior
    // uml: enter / { light_on1(); }
    {
        // Step 1: execute action `light_on1();`
        light_on1();
    } // end of behavior for ON1
}

static void ON1_exit(Tutorial1Sm* sm)
{
    // adjust function pointers for this state's exit
    sm->current_state_exit_handler = ROOT_exit;
    sm->current_event_handlers[Tutorial1Sm_EventId_DIM] = NULL;  // no ancestor listens to this event
}

static void ON1_dim(Tutorial1Sm* sm)
{
    // No ancestor state handles `dim` event.
    
    // ON1 behavior
    // uml: DIM TransitionTo(OFF)
    {
        // Step 1: Exit states until we reach `ROOT` state (Least Common Ancestor for transition).
        ON1_exit(sm);
        
        // Step 2: Transition action: ``.
        
        // Step 3: Enter/move towards transition target `OFF`.
        OFF_enter(sm);
        
        // Step 4: complete transition. Ends event dispatch. No other behaviors are checked.
        sm->state_id = Tutorial1Sm_StateId_OFF;
        // No ancestor handles event. Can skip nulling `ancestor_event_handler`.
        return;
    } // end of behavior for ON1
}

// Thread safe.
char const * const Tutorial1Sm_state_id_to_string(Tutorial1Sm_StateId id)
{
    switch (id)
    {
        case Tutorial1Sm_StateId_ROOT: return "ROOT";
        case Tutorial1Sm_StateId_OFF: return "OFF";
        case Tutorial1Sm_StateId_ON1: return "ON1";
        default: return "?";
    }
}

// Thread safe.
char const * const Tutorial1Sm_event_id_to_string(Tutorial1Sm_EventId id)
{
    switch (id)
    {
        case Tutorial1Sm_EventId_DIM: return "DIM";
        case Tutorial1Sm_EventId_INCREASE: return "INCREASE";
        default: return "?";
    }
}
