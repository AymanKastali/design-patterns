#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using std::cout, std::string, std::unique_ptr, std::make_unique,
    std::runtime_error;

class IButton {
public:
  virtual ~IButton() = default;
  virtual void paint() const = 0;
};

class ICheckbox {
public:
  virtual ~ICheckbox() = default;
  virtual void render() const = 0;
};

class WindowsOSButton : public IButton {
public:
  void paint() const override {
    cout << "Rendering a button in Windows OS style." << "\n";
  };
};

class WindowsOSCheckbox : public ICheckbox {
public:
  void render() const override {
    cout << "Rendering a checkbox in Windows OS style." << "\n";
  }
};

class LinuxOSButton : public IButton {
public:
  void paint() const override {
    cout << "Rendering a button in Linux OS style." << "\n";
  };
};

class LinuxOSCheckbox : public ICheckbox {
public:
  void render() const override {
    cout << "Rendering a checkbox in Linux OS style." << "\n";
  };
};

class IGUIFactory {
public:
  virtual ~IGUIFactory() = default;
  virtual unique_ptr<IButton> createButton() const = 0;
  virtual unique_ptr<ICheckbox> createCheckbox() const = 0;
};

class WindowsOSFactory : public IGUIFactory {
public:
  unique_ptr<IButton> createButton() const override {
    return make_unique<WindowsOSButton>();
  };

  unique_ptr<ICheckbox> createCheckbox() const override {
    return make_unique<WindowsOSCheckbox>();
  };
};

class LinuxOSFactory : public IGUIFactory {
public:
  std::unique_ptr<IButton> createButton() const override {
    return make_unique<LinuxOSButton>();
  }

  std::unique_ptr<ICheckbox> createCheckbox() const override {
    return make_unique<LinuxOSCheckbox>();
  }
};

class Application {
public:
  Application(const IGUIFactory& factory)
      : button(factory.createButton()), checkbox(factory.createCheckbox()) {};

  void renderUI() const {
    button->paint();
    checkbox->render();
  };

private:
  unique_ptr<IButton> button;
  unique_ptr<ICheckbox> checkbox;
};

unique_ptr<IGUIFactory> getFactory(const string& osType) {
  if (osType == "windows_os") {
    return make_unique<WindowsOSFactory>();
  } else if (osType == "linux_os") {
    return make_unique<LinuxOSFactory>();
  } else {
    throw runtime_error("Unknown OS type: " + osType);
  };
};

int main() {
  string osType = "linux_os";
  auto guiFactory = getFactory(osType);
  Application app(*guiFactory);
  app.renderUI();
  return 0;
}