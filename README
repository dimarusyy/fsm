#### Description
Please write a class in C++ that implements a generic state machine with the following properties:
• It should be possible to register new states, transitions and fallback transitions at runtime.
◦ Fallback transitions are transitions that are triggered when input does not match any currently
registered transitions.
• It should be possible to register callbacks for transitions.
• All public methods of class should be thread safe.
• The types for states and inputs should be generic.

#### Example
Following is an example usage of the FSM class instance.
```
    fsm.AddState('a');
    fsm.AddState('b');
    fsm.AddTransition('a', 'b', "input1", callback1);
    fsm.ResetMachine('a');
    fsm.Step("input1");
    assert(fsm.GetState() == 'b');

    fsm.AddState('c');
    fsm.AddTransition('b', 'c', "input2", callback2);
    fsm.Step("input2");
    assert(fsm.GetState() == 'c');
```