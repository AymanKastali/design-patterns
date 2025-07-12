package main

import "fmt"

type IDevice interface {
	GetName() string
	GetLocation() string
	TurnOn()
	TurnOff()
}

type FanningDevice struct {
	name, location string
}

func (f *FanningDevice) GetName() string {
	return f.name
}

func (f *FanningDevice) GetLocation() string {
	return f.location
}
func (f *FanningDevice) TurnOn() {
	fmt.Printf("%s %s is ON\n", f.location, f.name)
}
func (f *FanningDevice) TurnOff() {
	fmt.Printf("%s %s is OFF\n", f.location, f.name)
}

type CeilingFan struct {
	*FanningDevice
}

func NewCeilingFan(location string) *CeilingFan {
	return &CeilingFan{
		FanningDevice: &FanningDevice{name: "Ceiling Fan", location: location},
	}
}

type LightingDevice struct {
	name, location string
}

func (l *LightingDevice) GetName() string {
	return l.name
}
func (l *LightingDevice) GetLocation() string {
	return l.location
}
func (l *LightingDevice) TurnOn() {
	fmt.Printf("%s %s is ON\n", l.location, l.name)
}
func (l *LightingDevice) TurnOff() {
	fmt.Printf("%s %s is OFF\n", l.location, l.name)
}

type Lamp struct {
	*LightingDevice
}

func NewLamp(location string) *Lamp {
	return &Lamp{
		LightingDevice: &LightingDevice{name: "Lamp", location: location},
	}
}

type ICommand interface {
	Execute()
	Undo()
}

type LightOnCommand struct{ device IDevice }

func (c *LightOnCommand) Execute() {
	c.device.TurnOn()
}
func (c *LightOnCommand) Undo() {
	c.device.TurnOff()
}

type LightOffCommand struct{ device IDevice }

func (c *LightOffCommand) Execute() {
	c.device.TurnOff()
}
func (c *LightOffCommand) Undo() {
	c.device.TurnOn()
}

type FanOnCommand struct{ device IDevice }

func (c *FanOnCommand) Execute() {
	c.device.TurnOn()
}
func (c *FanOnCommand) Undo() {
	c.device.TurnOff()
}

type FanOffCommand struct{ device IDevice }

func (c *FanOffCommand) Execute() {
	c.device.TurnOff()
}
func (c *FanOffCommand) Undo() {
	c.device.TurnOn()
}

type RemoteControl struct {
	lightOn, lightOff, fanOn, fanOff ICommand
	history                          []ICommand
}

func (r *RemoteControl) LightOn() {
	r.lightOn.Execute()
	r.history = append(r.history, r.lightOn)
}

func (r *RemoteControl) LightOff() {
	r.lightOff.Execute()
	r.history = append(r.history, r.lightOff)
}

func (r *RemoteControl) FanOn() {
	r.fanOn.Execute()
	r.history = append(r.history, r.fanOn)
}

func (r *RemoteControl) FanOff() {
	r.fanOff.Execute()
	r.history = append(r.history, r.fanOff)
}

func (r *RemoteControl) Undo() {
	if len(r.history) == 0 {
		fmt.Println("No commands to undo.")
		return
	}
	last := r.history[len(r.history)-1]
	r.history = r.history[:len(r.history)-1]

	fmt.Println("Undoing last command...")
	last.Undo()
}

func main() {
	lamp := NewLamp("Living room")
	fan := NewCeilingFan("Bedroom")

	lightOn := &LightOnCommand{device: lamp}
	lightOff := &LightOffCommand{device: lamp}
	fanOn := &FanOnCommand{device: fan}
	fanOff := &FanOffCommand{device: fan}

	remote := &RemoteControl{
		lightOn:  lightOn,
		lightOff: lightOff,
		fanOn:    fanOn,
		fanOff:   fanOff,
	}

	remote.LightOn()
	remote.LightOff()
	remote.FanOn()
	remote.FanOff()

	remote.Undo()
	remote.Undo()
	remote.Undo()
	remote.Undo()
}
