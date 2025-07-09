package main

import "fmt"

type IButton interface {
	Paint()
}

type ICheckbox interface {
	Render()
}

type WindowsOSButton struct{}

func (b *WindowsOSButton) Paint() {
	fmt.Println("Rendering a button in Windows OS style.")
}

type WindowsOSCheckbox struct{}

func (c *WindowsOSCheckbox) Render() {
	fmt.Println("Rendering a checkbox in Windows OS style.")
}

type LinuxOSButton struct{}

func (b *LinuxOSButton) Paint() {
	fmt.Println("Rendering a button in Linux OS style.")
}

type LinuxOSCheckbox struct{}

func (c *LinuxOSCheckbox) Render() {
	fmt.Println("Rendering a checkbox in Linux OS style.")
}

type IGUIFactory interface {
	CreateButton() IButton
	CreateCheckbox() ICheckbox
}

type WindowsOSFactory struct{}

func (f *WindowsOSFactory) CreateButton() IButton {
	return &WindowsOSButton{}
}

func (c *WindowsOSFactory) CreateCheckbox() ICheckbox {
	return &WindowsOSCheckbox{}
}

type LinuxOSFactory struct{}

func (f *LinuxOSFactory) CreateButton() IButton {
	return &LinuxOSButton{}
}

func (c *LinuxOSFactory) CreateCheckbox() ICheckbox {
	return &LinuxOSCheckbox{}
}

type Application struct {
	button   IButton
	checkbox ICheckbox
}

func NewApplication(factory IGUIFactory) *Application {
	return &Application{
		button:   factory.CreateButton(),
		checkbox: factory.CreateCheckbox(),
	}
}

func (app *Application) RenderUI() {
	app.button.Paint()
	app.checkbox.Render()
}

func GetFactory(osType string) (IGUIFactory, error) {
	switch osType {
	case "windows_os":
		return &WindowsOSFactory{}, nil
	case "linux_os":
		return &LinuxOSFactory{}, nil
	default:
		return nil, fmt.Errorf("Unknown OS type: %s", osType)
	}

}

func main() {
	const osType string = "linux_os"

	factory, err := GetFactory(osType)
	if err != nil {
		panic(err)
	}
	app := NewApplication(factory)
	app.RenderUI()
}
