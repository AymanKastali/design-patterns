#include <iostream>
#include <memory>
#include <string>
using std::string, std::cout, std::unique_ptr, std::make_unique, std::move;

class ITextFormatter {
public:
  virtual ~ITextFormatter(){};
  virtual void format(const string& text) const = 0;
};

class PlainTextFormatter : public ITextFormatter {
public:
  void format(const string& text) const override {
    cout << "Plain: " << text << "\n";
  };
};

class MarkdownFormatter : public ITextFormatter {
public:
  void format(const string& text) const override {
    cout << "Markdown: **" << text << "**" << "\n";
  };
};

class HtmlFormatter : public ITextFormatter {
public:
  void format(const string& text) const override {
    cout << "HTML: <b>" << text << "</b>" << "\n";
  }
};

class TextEditor {
public:
  TextEditor(unique_ptr<ITextFormatter> f) : formatter(move(f)) {
  }

  void setFormatter(unique_ptr<ITextFormatter> f) {
    formatter = move(f);
  };

  void publishText(const string& text) {
    formatter->format(text);
  };

private:
  unique_ptr<ITextFormatter> formatter;
};

int main() {
  const string message = "Hello, world!";

  TextEditor editor(make_unique<PlainTextFormatter>());
  editor.publishText(message);

  editor.setFormatter(make_unique<MarkdownFormatter>());
  editor.publishText(message);

  editor.setFormatter(make_unique<HtmlFormatter>());
  editor.publishText(message);
}