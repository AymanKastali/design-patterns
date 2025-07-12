#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::cout, std::string, std::unique_ptr, std::make_unique, std::move,
    std::vector;

class IDevice {
public:
  [[nodiscard]] virtual string getName() const = 0;
  [[nodiscard]] virtual string getLocation() const = 0;
  virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual ~IDevice() = default;
};

class FanningDevice : public IDevice {
public:
  explicit FanningDevice(string loc) : location(move(loc)) {
  }

  [[nodiscard]] string getLocation() const override {
    return location;
  }

  void turnOn() override {
    cout << location << " " << getName() << " is ON\n";
  }

  void turnOff() override {
    cout << location << " " << getName() << " is OFF\n";
  }

protected:
  string location;
};

class CeilingFan final : public FanningDevice {
public:
  explicit CeilingFan(string loc) : FanningDevice(move(loc)) {
  }

  [[nodiscard]] string getName() const override {
    return "Ceiling Fan";
  }
};

class LightingDevice : public IDevice {
public:
  explicit LightingDevice(string loc) : location(move(loc)) {
  }

  [[nodiscard]] string getLocation() const override {
    return location;
  }

  void turnOn() override {
    cout << location << " " << getName() << " is ON\n";
  }

  void turnOff() override {
    cout << location << " " << getName() << " is OFF\n";
  }

protected:
  string location;
};

class Lamp final : public LightingDevice {
public:
  explicit Lamp(string loc) : LightingDevice(move(loc)) {
  }

  [[nodiscard]] string getName() const override {
    return "Lamp";
  }
};

class ICommand {
public:
  virtual void execute() const = 0;
  virtual void undo() const = 0;
  virtual ~ICommand() = default;
};

class LightOnCommand final : public ICommand {
public:
  explicit LightOnCommand(IDevice& dev) : device(dev) {
  }

  void execute() const override {
    device.turnOn();
  }

  void undo() const override {
    device.turnOff();
  }

private:
  IDevice& device;
};

class LightOffCommand final : public ICommand {
public:
  explicit LightOffCommand(IDevice& dev) : device(dev) {
  }

  void execute() const override {
    device.turnOff();
  }

  void undo() const override {
    device.turnOn();
  }

private:
  IDevice& device;
};

class FanOnCommand final : public ICommand {
public:
  explicit FanOnCommand(IDevice& dev) : device(dev) {
  }

  void execute() const override {
    device.turnOn();
  }

  void undo() const override {
    device.turnOff();
  }

private:
  IDevice& device;
};

class FanOffCommand final : public ICommand {
public:
  explicit FanOffCommand(IDevice& dev) : device(dev) {
  }

  void execute() const override {
    device.turnOff();
  }

  void undo() const override {
    device.turnOn();
  }

private:
  IDevice& device;
};

class RemoteControl {
public:
  RemoteControl(unique_ptr<ICommand> lampOn, unique_ptr<ICommand> lampOff,
                unique_ptr<ICommand> fanOn, unique_ptr<ICommand> fanOff)
      : lightOn(move(lampOn)), lightOff(move(lampOff)), fanOn(move(fanOn)),
        fanOff(move(fanOff)) {
  }

  void lightOnCmd() {
    lightOn->execute();
    history.push_back(lightOn.get());
  }

  void lightOffCmd() {
    lightOff->execute();
    history.push_back(lightOff.get());
  }

  void fanOnCmd() {
    fanOn->execute();
    history.push_back(fanOn.get());
  }

  void fanOffCmd() {
    fanOff->execute();
    history.push_back(fanOff.get());
  }

  void undo() {
    if (!history.empty()) {
      cout << "Undoing last command...\n";
      history.back()->undo();
      history.pop_back();
    } else {
      cout << "No commands to undo.\n";
    }
  }

private:
  unique_ptr<ICommand> lightOn;
  unique_ptr<ICommand> lightOff;
  unique_ptr<ICommand> fanOn;
  unique_ptr<ICommand> fanOff;
  vector<ICommand*> history;
};

int main() {
  auto lamp = make_unique<Lamp>("Living Room");
  auto fan = make_unique<CeilingFan>("Bedroom");

  auto lightOn = make_unique<LightOnCommand>(*lamp);
  auto lightOff = make_unique<LightOffCommand>(*lamp);
  auto fanOn = make_unique<FanOnCommand>(*fan);
  auto fanOff = make_unique<FanOffCommand>(*fan);

  RemoteControl remote(move(lightOn), move(lightOff), move(fanOn),
                       move(fanOff));

  remote.lightOnCmd();
  remote.lightOffCmd();
  remote.fanOnCmd();
  remote.fanOffCmd();

  remote.undo();
  remote.undo();
  remote.undo();
  remote.undo();
}
