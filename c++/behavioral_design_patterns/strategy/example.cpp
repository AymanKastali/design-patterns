#include <iostream>
#include <string>
using std::string, std::cout;

class ITextFormatter {
public:
  virtual void format(const string& text) = 0;
  virtual ~ITextFormatter() {};
};

class PlainTextFormatter : public ITextFormatter {
public:
  void format(const string& text) {
    cout << "Plain: " << text << "\n";
  };
};

class MarkdownFormatter : public ITextFormatter {
public:
  void format(const string& text) {
    cout << "Markdown: **" << text << "**" << "\n";
  };
};

class HtmlFormatter : public ITextFormatter {
public:
  void format(const string& text) override {
    cout << "HTML: <b>" << text << "</b>" << "\n";
  }
};

class TextEditor {
public:
  TextEditor(ITextFormatter* f) : formatter(f) {};

  void setFormatter(ITextFormatter* f) {
    formatter = f;
  };

  void publishText(const string& text) {
    formatter->format(text);
  };

private:
  ITextFormatter* formatter;
};

int main() {
  const string message = "Hello, world!";

  PlainTextFormatter plain;
  MarkdownFormatter markdown;
  HtmlFormatter html;

  TextEditor editor(&plain);
  editor.publishText(message);

  editor.setFormatter(&markdown);
  editor.publishText(message);

  editor.setFormatter(&html);
  editor.publishText(message);
}