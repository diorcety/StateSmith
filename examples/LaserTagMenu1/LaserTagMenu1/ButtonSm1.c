// Autogenerated with StateSmith
#include "ButtonSm1.h"
#include "PortApi.h"
#include <stdbool.h> // required for `consume_event` flag
#include <string.h> // for memset

static void ROOT_enter(ButtonSm1* self);
static void ROOT_exit(ButtonSm1* self);

static void NOT_PRESSED_enter(ButtonSm1* self);
static void NOT_PRESSED_exit(ButtonSm1* self);
static void NOT_PRESSED_do(ButtonSm1* self);

static void PRESSED_enter(ButtonSm1* self);
static void PRESSED_exit(ButtonSm1* self);
static void PRESSED_do(ButtonSm1* self);

static void CONFIRMING_HELD_enter(ButtonSm1* self);
static void CONFIRMING_HELD_exit(ButtonSm1* self);
static void CONFIRMING_HELD_do(ButtonSm1* self);

static void HELD_enter(ButtonSm1* self);
static void HELD_exit(ButtonSm1* self);

void ButtonSm1_ctor(ButtonSm1* self)
{
    memset(self, 0, sizeof(*self));
}

void ButtonSm1_start(ButtonSm1* self)
{
    ROOT_enter(self);
    // Transition to target state NOT_PRESSED
    {
        // target state NOT_PRESSED is a child of this state. No need to exit this state.
        
        // Enter towards target
        NOT_PRESSED_enter(self);
        
        // update state_id
        self->state_id = ButtonSm1_StateId_NOT_PRESSED;
    } // end of transition code
}

void ButtonSm1_dispatch_event(ButtonSm1* self, enum ButtonSm1_EventId event_id)
{
    ButtonSm1_Func behavior_func = self->current_event_handlers[event_id];
    
    while (behavior_func != NULL)
    {
        self->ancestor_event_handler = NULL;
        behavior_func(self);
        behavior_func = self->ancestor_event_handler;
    }
}

static void ROOT_enter(ButtonSm1* self)
{
    // setup trigger/event handlers
    self->current_state_exit_handler = ROOT_exit;
}

static void ROOT_exit(ButtonSm1* self)
{
    // State machine root is a special case. It cannot be exited.
    (void)self;  // nothing to see here compiler. move along!
}


static void NOT_PRESSED_enter(ButtonSm1* self)
{
    // setup trigger/event handlers
    self->current_state_exit_handler = NOT_PRESSED_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = NOT_PRESSED_do;
    
    // state behavior:
    {
        // uml action: reset_debounce_timer();
        self->vars.debounce_started_at_ms = (2047 & PortApi_get_time_ms());
    } // end of behavior code
}

static void NOT_PRESSED_exit(ButtonSm1* self)
{
    // adjust function pointers for this state's exit
    self->current_state_exit_handler = ROOT_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = NULL;  // no ancestor listens to this event
}

static void NOT_PRESSED_do(ButtonSm1* self)
{
    // setup handler for next ancestor that listens to `do` event
    self->ancestor_event_handler = NULL; // no ancestor state handles `do` event
    
    // state behavior:
    {
        // Note: no `consume_event` variable possible here because of state transition. The event must be consumed.
        // uml guard: is_pressed && is_debounced
        // uml transition target: CONFIRMING_HELD
        if (self->vars.input_is_pressed && (( (2047 & ((2047 & PortApi_get_time_ms()) - self->vars.debounce_started_at_ms)) >= 20 )))
        {
            // Transition to target state CONFIRMING_HELD
            {
                // First, exit up to Least Common Ancestor ButtonSm1.
                while (self->current_state_exit_handler != ROOT_exit)
                {
                    self->current_state_exit_handler(self);
                }
                
                // Enter towards target
                PRESSED_enter(self);
                CONFIRMING_HELD_enter(self);
                
                // update state_id
                self->state_id = ButtonSm1_StateId_CONFIRMING_HELD;
            } // end of transition code
            
            // Mark event as handled. Required because of transition.
            // self->ancestor_event_handler = NULL; // already done at top of function
            return; // event processing immediately stops when a transition occurs. No other behaviors for this state are checked.
        } // end of guard code
    } // end of behavior code
}


static void PRESSED_enter(ButtonSm1* self)
{
    // setup trigger/event handlers
    self->current_state_exit_handler = PRESSED_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = PRESSED_do;
    
    // state behavior:
    {
        // uml action: reset_debounce_timer();
        //             output_event(press);
        self->vars.debounce_started_at_ms = (2047 & PortApi_get_time_ms());
        self->vars.output_event_press = true;
    } // end of behavior code
}

static void PRESSED_exit(ButtonSm1* self)
{
    // adjust function pointers for this state's exit
    self->current_state_exit_handler = ROOT_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = NULL;  // no ancestor listens to this event
}

static void PRESSED_do(ButtonSm1* self)
{
    // setup handler for next ancestor that listens to `do` event
    self->ancestor_event_handler = NULL; // no ancestor state handles `do` event
    
    // state behavior:
    {
        // Note: no `consume_event` variable possible here because of state transition. The event must be consumed.
        // uml guard: is_released && is_debounced
        // uml action: if (debounce_ms() <= 200) {
        //               output_event(tap);
        //             }
        //             output_event(release);
        // uml transition target: NOT_PRESSED
        if ((!self->vars.input_is_pressed) && (( (2047 & ((2047 & PortApi_get_time_ms()) - self->vars.debounce_started_at_ms)) >= 20 )))
        {
            if ((2047 & ((2047 & PortApi_get_time_ms()) - self->vars.debounce_started_at_ms)) <= 200) {
              self->vars.output_event_tap = true;
            }
            self->vars.output_event_release = true;
            
            // Transition to target state NOT_PRESSED
            {
                // First, exit up to Least Common Ancestor ButtonSm1.
                while (self->current_state_exit_handler != ROOT_exit)
                {
                    self->current_state_exit_handler(self);
                }
                
                // Enter towards target
                NOT_PRESSED_enter(self);
                
                // update state_id
                self->state_id = ButtonSm1_StateId_NOT_PRESSED;
            } // end of transition code
            
            // Mark event as handled. Required because of transition.
            // self->ancestor_event_handler = NULL; // already done at top of function
            return; // event processing immediately stops when a transition occurs. No other behaviors for this state are checked.
        } // end of guard code
    } // end of behavior code
}


static void CONFIRMING_HELD_enter(ButtonSm1* self)
{
    // setup trigger/event handlers
    self->current_state_exit_handler = CONFIRMING_HELD_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = CONFIRMING_HELD_do;
}

static void CONFIRMING_HELD_exit(ButtonSm1* self)
{
    // adjust function pointers for this state's exit
    self->current_state_exit_handler = PRESSED_exit;
    self->current_event_handlers[ButtonSm1_EventId_DO] = PRESSED_do;  // the next ancestor that handles this event is PRESSED
}

static void CONFIRMING_HELD_do(ButtonSm1* self)
{
    // setup handler for next ancestor that listens to `do` event
    self->ancestor_event_handler = PRESSED_do;
    
    // state behavior:
    {
        // Note: no `consume_event` variable possible here because of state transition. The event must be consumed.
        // uml guard: debounce_ms() > 800
        // uml transition target: HELD
        if ((2047 & ((2047 & PortApi_get_time_ms()) - self->vars.debounce_started_at_ms)) > 800)
        {
            // Transition to target state HELD
            {
                // First, exit up to Least Common Ancestor PRESSED.
                while (self->current_state_exit_handler != PRESSED_exit)
                {
                    self->current_state_exit_handler(self);
                }
                
                // Enter towards target
                HELD_enter(self);
                
                // update state_id
                self->state_id = ButtonSm1_StateId_HELD;
            } // end of transition code
            
            // Mark event as handled. Required because of transition.
            self->ancestor_event_handler = NULL;
            return; // event processing immediately stops when a transition occurs. No other behaviors for this state are checked.
        } // end of guard code
    } // end of behavior code
}


static void HELD_enter(ButtonSm1* self)
{
    // setup trigger/event handlers
    self->current_state_exit_handler = HELD_exit;
    
    // state behavior:
    {
        // uml action: output_event(held);
        self->vars.output_event_held = true;
    } // end of behavior code
}

static void HELD_exit(ButtonSm1* self)
{
    // adjust function pointers for this state's exit
    self->current_state_exit_handler = PRESSED_exit;
}


