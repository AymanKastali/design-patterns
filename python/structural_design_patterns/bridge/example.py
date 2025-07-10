from abc import ABC, abstractmethod


class IDrawingAPI(ABC):
    @abstractmethod
    def draw_circle(self, x: int, y: int, radius: int) -> None: ...

    @abstractmethod
    def draw_rectangle(self, x: int, y: int, width: int, height: int) -> None: ...


class V1DrawingAPI(IDrawingAPI):
    def draw_circle(self, x, y, radius) -> None:
        print(f"[V1] Circle at ({x},{y}) radius {radius}")

    def draw_rectangle(self, x, y, width, height) -> None:
        print(f"[V1] Rectangle at ({x},{y}) width {width} height {height}")


class V2DrawingAPI(IDrawingAPI):
    def draw_circle(self, x, y, radius) -> None:
        print(f"[V2] Smooth Circle at ({x},{y}) radius {radius}")

    def draw_rectangle(self, x, y, width, height) -> None:
        print(f"[V2] Filled Rectangle at ({x},{y}) width {width} height {height}")


class Shape(ABC):
    def __init__(self, drawing_api: IDrawingAPI) -> None:
        self.api: IDrawingAPI = drawing_api

    @abstractmethod
    def draw(self) -> None: ...


class Circle(Shape):
    def __init__(self, x: int, y: int, radius: int, drawing_api: IDrawingAPI):
        super().__init__(drawing_api)
        self.x: int = x
        self.y: int = y
        self.radius: int = radius

    def draw(self) -> None:
        self.api.draw_circle(self.x, self.y, self.radius)


class Rectangle(Shape):
    def __init__(self, x: int, y: int, width: int, height: int, drawing_api: IDrawingAPI) -> None:
        super().__init__(drawing_api)
        self.x: int = x
        self.y: int = y
        self.width: int = width
        self.height: int = height

    def draw(self) -> None:
        self.api.draw_rectangle(self.x, self.y, self.width, self.height)


def main():
    print(f"{"v1":=^50}")
    v1_drawing_api: V1DrawingAPI = V1DrawingAPI()
    circle_shape: Circle = Circle(10, 20, 5, v1_drawing_api)
    rectangle_shape: Rectangle = Rectangle(30, 40, 10, 8, v1_drawing_api)
    circle_shape.draw()
    rectangle_shape.draw()

    print(f"{"v2":=^50}")
    v2_drawing_api: V2DrawingAPI = V2DrawingAPI()
    circle_shape: Circle = Circle(100, 150, 25, v2_drawing_api)
    rectangle_shape: Rectangle = Rectangle(200, 250, 70, 40, v2_drawing_api)
    circle_shape.draw()
    rectangle_shape.draw()


if __name__ == "__main__":
    main()
