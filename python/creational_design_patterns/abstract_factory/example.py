from abc import ABC, abstractmethod


class IButton(ABC):
    @abstractmethod
    def paint(self) -> None:
        pass


class ICheckbox(ABC):
    @abstractmethod
    def render(self) -> None:
        pass


class WindowsOSButton(IButton):
    def paint(self) -> None:
        print("Rendering a button in Windows OS style.")


class WindowsOSCheckbox(ICheckbox):
    def render(self) -> None:
        print("Rendering a checkbox in Windows OS style.")


class LinuxOSButton(IButton):
    def paint(self) -> None:
        print("Rendering a button in Linux OS style.")


class LinuxOSCheckbox(ICheckbox):
    def render(self) -> None:
        print("Rendering a checkbox in Linux OS style.")


class IGUIFactory(ABC):
    @abstractmethod
    def create_button(self) -> IButton:
        pass

    @abstractmethod
    def create_checkbox(self) -> ICheckbox:
        pass


class WindowsOSFactory(IGUIFactory):
    def create_button(self) -> IButton:
        return WindowsOSButton()

    def create_checkbox(self) -> ICheckbox:
        return WindowsOSCheckbox()


class LinuxOSFactory(IGUIFactory):
    def create_button(self) -> IButton:
        return LinuxOSButton()

    def create_checkbox(self) -> ICheckbox:
        return LinuxOSCheckbox()


class Application:
    def __init__(self, factory: IGUIFactory) -> None:
        self._button = factory.create_button()
        self._checkbox = factory.create_checkbox()

    def render_ui(self) -> None:
        self._button.paint()
        self._checkbox.render()


def get_factory(os_type: str) -> IGUIFactory:
    if os_type == "windows_os":
        return WindowsOSFactory()
    if os_type == "linux_os":
        return LinuxOSFactory()
    raise ValueError("Unknown OS type")


if __name__ == "__main__":
    OS_TYPE: str = "linux_os"
    gui_factory: IGUIFactory = get_factory(OS_TYPE)
    app = Application(gui_factory)
    app.render_ui()
