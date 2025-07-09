#include <iostream>
#include <memory>
using std::string, std::cout, std::shared_ptr, std::move, std::make_shared;

class IText {
public:
  virtual ~IText() = default;
  virtual string render() const = 0;
};

class PlainText : public IText {
public:
  explicit PlainText(const string& content) : content(content) {};
  string render() const override {
    return content;
  }

private:
  string content;
};

class TextDecorator : public IText {
public:
  explicit TextDecorator(std::shared_ptr<IText> wrapped)
      : wrapped(move(wrapped)) {
  }

  string render() const override {
    return wrapped->render();
  };

protected:
  shared_ptr<IText> wrapped;
};

class BoldDecorator : public TextDecorator {
public:
  using TextDecorator::TextDecorator;
  string render() const override {
    return "<b>" + TextDecorator::render() + "</b>";
  };
};

class ItalicDecorator : public TextDecorator {
public:
  using TextDecorator::TextDecorator;
  string render() const override {
    return "<i>" + TextDecorator::render() + "</i>";
  };
};

class UnderlineDecorator : public TextDecorator {
public:
  using TextDecorator::TextDecorator;
  string render() const override {
    return "<u>" + TextDecorator::render() + "</u>";
  };
};

int main() {
  const string message = "Hello, world!";

  shared_ptr<IText> text = make_shared<PlainText>(message);

  shared_ptr<IText> formatted = make_shared<BoldDecorator>(
      make_shared<ItalicDecorator>(make_shared<UnderlineDecorator>(text)));

  cout << formatted->render() << "/n";
  return 0;
}