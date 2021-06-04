#include <gtest/gtest.h>
#include "fsm.h"

TEST(FSM, ExampleFromSpec)
{
    bool invoked = false;
    fsm::fsm m;
    m.AddState('a');
    m.AddState('b');
    m.AddTransition('a', 'b', "input1", [&]()
                    { invoked = true; });

    m.ResetMachine('a');
    m.Step("input1");

    EXPECT_EQ(m.GetState(), 'b');
    EXPECT_TRUE(invoked);

    m.AddState('c');
    m.AddTransition('b', 'c', "input2", {});
    m.Step("input2");
    EXPECT_EQ(m.GetState(), 'c');
}

TEST(FSM, FallbackInvoked)
{
    bool invoked = false;
    fsm::fsm m;
    m.AddState('a');
    m.AddState('b');
    m.AddTransition('a', 'b', "input1",{});
    m.AddFallback('a', [&]() { invoked = true; });

    m.ResetMachine('a');
    m.Step("input");

    EXPECT_TRUE(invoked);
}

TEST(FSM, TransitionWrongInputNoFallback)
{
    fsm::fsm m;
    m.AddState('a');
    m.AddState('b');
    m.AddTransition('a', 'b', "input1", {});

    m.ResetMachine('a');
    m.Step("input");
    EXPECT_EQ(m.GetState(), 'a');
}

TEST(FSM, UpperCaseState)
{
    fsm::fsm m;
    m.AddState('a');
    m.AddState('b');
    m.AddTransition('a', 'b', "input1", {});

    m.ResetMachine('A');
    m.Step("input");
    EXPECT_EQ(m.GetState(), 'a');
}

TEST(FSM, ResetStateOnce)
{
    fsm::fsm m;
    m.AddState('a');

    m.ResetMachine('a');
    EXPECT_EQ(m.GetState(), 'a');
}

TEST(FSM, ResetStateTwice)
{
    fsm::fsm m;
    m.AddState('a');
    m.AddState('b');

    m.ResetMachine('a');
    m.ResetMachine('b');
    EXPECT_EQ(m.GetState(), 'b');
}

TEST(FSM, ResetStateNoState)
{
    fsm::fsm m;
    m.ResetMachine('a');
    EXPECT_EQ(m.GetState(), fsm::fsm::unknown_state);
}