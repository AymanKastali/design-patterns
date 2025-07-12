from abc import ABC, abstractmethod


class IDevice(ABC):
    @abstractmethod
    def get_name(self) -> str: ...

    @abstractmethod
    def get_location(self) -> str: ...

    @abstractmethod
    def turn_on(self) -> None: ...

    @abstractmethod
    def turn_off(self) -> None: ...


class FanningDevice(IDevice):
    def __init__(self, location: str) -> None:
        self._location: str = location

    def get_location(self) -> str:
        return self._location

    def turn_on(self) -> None:
        print(f"{self.get_location()} {self.get_name()} is ON")

    def turn_off(self) -> None:
        print(f"{self.get_location()} {self.get_name()} is OFF")


class CeilingFan(FanningDevice):
    def get_name(self) -> str:
        return "Ceiling Fan"


class LightingDevice(IDevice):
    def __init__(self, location: str) -> None:
        self._location: str = location

    def get_location(self) -> str:
        return self._location

    def turn_on(self) -> None:
        print(f"{self.get_location()} {self.get_name()} is ON")

    def turn_off(self) -> None:
        print(f"{self.get_location()} {self.get_name()} is OFF")


class Lamp(LightingDevice):
    def get_name(self) -> str:
        return "Lamp"


class ICommand(ABC):
    @abstractmethod
    def execute(self) -> None: ...

    @abstractmethod
    def undo(self) -> None: ...


class LightOnCommand(ICommand):
    def __init__(self, light: IDevice) -> None:
        self._light: IDevice = light

    def execute(self) -> None:
        self._light.turn_on()

    def undo(self) -> None:
        self._light.turn_off()


class LightOffCommand(ICommand):
    def __init__(self, light: IDevice) -> None:
        self._light: IDevice = light

    def execute(self) -> None:
        self._light.turn_off()

    def undo(self) -> None:
        self._light.turn_on()


class FanOnCommand(ICommand):
    def __init__(self, fan: IDevice) -> None:
        self._fan: IDevice = fan

    def execute(self) -> None:
        self._fan.turn_on()

    def undo(self) -> None:
        self._fan.turn_off()


class FanOffCommand(ICommand):
    def __init__(self, fan: IDevice) -> None:
        self._fan: IDevice = fan

    def execute(self) -> None:
        self._fan.turn_off()

    def undo(self) -> None:
        self._fan.turn_on()


class RemoteControl:
    def __init__(
        self, light_on: ICommand, light_off: ICommand, fan_on: ICommand, fan_off: ICommand
    ) -> None:
        self._light_on: ICommand = light_on
        self._light_off: ICommand = light_off
        self._fan_on: ICommand = fan_on
        self._fan_off: ICommand = fan_off
        self._history: list = []

    def light_on(self) -> None:
        self._light_on.execute()
        self._add_to_history(self._light_on)

    def light_off(self) -> None:
        self._light_off.execute()
        self._add_to_history(self._light_off)

    def fan_on(self) -> None:
        self._fan_on.execute()
        self._add_to_history(self._fan_on)

    def fan_off(self) -> None:
        self._fan_off.execute()
        self._add_to_history(self._fan_off)

    def undo(self) -> None:
        if self._history:
            last_command = self._history.pop()
            print("Undoing last command...")
            last_command.undo()
        else:
            print("No commands to undo.")

    def _add_to_history(self, command: ICommand) -> None:
        self._history.append(command)


def main():
    lamp: LightingDevice = Lamp("Living room")
    lamp_light_on: ICommand = LightOnCommand(lamp)
    lamp_light_off: ICommand = LightOffCommand(lamp)
    ceiling_fan: FanningDevice = CeilingFan("Bedroom")
    ceiling_fan_on: ICommand = FanOnCommand(ceiling_fan)
    ceiling_fan_off: ICommand = FanOffCommand(ceiling_fan)

    first_remote: RemoteControl = RemoteControl(
        lamp_light_on, lamp_light_off, ceiling_fan_on, ceiling_fan_off
    )

    first_remote.light_on()
    first_remote.light_off()
    first_remote.fan_on()
    first_remote.fan_off()
    first_remote.undo()
    first_remote.undo()
    first_remote.undo()
    first_remote.undo()


if __name__ == "__main__":
    main()
