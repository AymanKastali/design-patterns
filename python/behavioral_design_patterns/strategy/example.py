from abc import ABC, abstractmethod


class ITextFormatter(ABC):
    @abstractmethod
    def format(self, text: str) -> None: ...


class PlainTextFormatter(ITextFormatter):
    def format(self, text: str) -> None:
        print(f"Plain: {text}")


class MarkdownFormatter(ITextFormatter):
    def format(self, text: str) -> None:
        print(f"Markdown: **{text}**")


class HtmlFormatter(ITextFormatter):
    def format(self, text: str) -> None:
        print(f"HTML: <b>{text}</b>")


class TextEditor:
    def __init__(self, formatter: ITextFormatter) -> None:
        self.formatter = formatter

    def set_formatter(self, formatter: ITextFormatter) -> None:
        self.formatter = formatter

    def publish_text(self, text: str) -> None:
        self.formatter.format(text)


if __name__ == "__main__":
    message: str = "Hello, world!"

    editor: TextEditor = TextEditor(PlainTextFormatter())
    editor.publish_text(message)

    editor.set_formatter(MarkdownFormatter())
    editor.publish_text(message)

    editor.set_formatter(HtmlFormatter())
    editor.publish_text(message)
