package statemachine

import "fmt"

type EventID int
type StateID int

// NextStates is a list of States based on list index, which means an EventID
type NextStates [5]StateID

// StateMachine is a map of a StateID to its possible next states based on the EventID
type StateMachine map[StateID]NextStates

// State is a representation of a state with its respective action to be run when called
type State struct {
	Id     StateID
	Name   string
	Action StateAction
}

var (
	States = map[StateID]*State{
		1: {Id: 1, Name: "Link Down", Action: &LinkDownAction{Reason: 1}},
		2: {Id: 2, Name: "Enviando Start", Action: &SendingStartAction{Ip: "192.168.10.1"}},
		3: {Id: 3, Name: "Start Recebido envia Configuração", Action: nil},
		4: {Id: 4, Name: "Link OK - manda keep alive", Action: nil},
	}

	Events_enum = map[EventID]string{
		1: "Interface nok",
		2: "Interface ok",
		3: "Pacote ok recebido",
		4: "Pacote nok recebido",
		5: "Não recebeu resposta",
	}

	stateMachine = StateMachine{
		1: [5]StateID{1, 2, 1, 1, 1},
		2: [5]StateID{1, 0, 3, 2, 2},
		3: [5]StateID{1, 0, 4, 3, 2},
		4: [5]StateID{1, 0, 4, 2, 2},
	}
)

// StateAction is an interface for each State
type StateAction interface {
	Run()
}

type LinkDownAction struct {
	Reason int
}

func (ld *LinkDownAction) Run() {
	fmt.Printf("link '%d' is down now\n", ld.Reason)
}

type SendingStartAction struct {
	Ip string
}

func (es *SendingStartAction) Run() {
	fmt.Printf("Start action sent to address %s\n", es.Ip)
}

func GetNextState(currentState int, event int) (*State, error) {
	if err := ValidateState(currentState); err != nil {
		return nil, err
	}

	if err := ValidateEvent(event); err != nil {
		return nil, err
	}

	nextStateID := stateMachine[StateID(currentState)][event-1]

	return States[StateID(nextStateID)], nil
}

func ValidateState(stateValue int) error {
	if stateValue < 1 || stateValue > 4 {
		return fmt.Errorf("invalid state '%d': out of range", stateValue)
	}

	return nil
}

func ValidateEvent(eventValue int) error {
	if eventValue < 1 || eventValue > 5 {
		return fmt.Errorf("invalid event '%d': out of range", eventValue)
	}

	return nil
}
