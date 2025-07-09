from abc import ABC, abstractmethod


class IText(ABC):
    @abstractmethod
    def render(self) -> str:
        pass


class PlainText(IText):
    def __init__(self, content: str) -> None:
        self._content = content

    def render(self) -> str:
        return self._content


class TextDecorator(IText):
    def __init__(self, wrapped: IText) -> None:
        self._wrapped = wrapped

    def render(self) -> str:
        return self._wrapped.render()


class BoldDecorator(TextDecorator):
    TAG: str = "<b>{}</b>"

    def render(self) -> str:
        return self.TAG.format(super().render())


class ItalicDecorator(TextDecorator):
    TAG: str = "<i>{}</i>"

    def render(self) -> str:
        return self.TAG.format(super().render())


class UnderlineDecorator(TextDecorator):
    TAG: str = "<u>{}</u>"

    def render(self) -> str:
        return self.TAG.format(super().render())


if __name__ == "__main__":
    message: str = "Hello, world!"
    text: PlainText = PlainText(message)

    formatted: IText = BoldDecorator(ItalicDecorator(UnderlineDecorator(text)))
    print(formatted.render())
