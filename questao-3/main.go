package main

import (
	statemachine "datacom/questao3/stateMachine"
	"fmt"
	"os"
	"strconv"
)

func main() {
	args := os.Args[1:]
	if len(args) != 2 {
		fmt.Printf("state machine requires exact two arguments: currentState (1-4) and event (1-5)")
		return
	}

	currentState, err := strconv.Atoi(args[0])
	if err != nil {
		fmt.Printf("currentState passed is not an integer value '%v'\n", args[0])
		return
	}

	event, err := strconv.Atoi(args[1])
	if err != nil {
		fmt.Printf("event passed is not an integer value '%v'\n", args[1])
		return
	}

	state, err := statemachine.GetNextState(currentState, event)
	if err != nil {
		fmt.Printf("failed getting next state: %v\n", err)
		return
	}

	if state == nil {
		fmt.Println("There is no next state")
		return
	}

	fmt.Printf("Current State is '%s' and event occured is '%s'\n", statemachine.States[statemachine.StateID(currentState)].Name, statemachine.Events_enum[statemachine.EventID(event)])

	fmt.Printf("Next State is: %s\n", state.Name)

	if state.Action != nil {
		fmt.Print("Action result: ")
		state.Action.Run()
	} else {
		fmt.Println("State does not have a defined action to run")
	}
}
