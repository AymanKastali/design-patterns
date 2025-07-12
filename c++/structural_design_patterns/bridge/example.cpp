#include <iostream>
#include <memory>
#include <string>
using std::cout, std::shared_ptr, std::move, std::string, std::make_shared,
    std::make_unique, std::unique_ptr;

class IDrawingAPI {
public:
  virtual ~IDrawingAPI() = default;
  virtual void drawCircle(int x, int y, int radius) const = 0;
  virtual void drawRectangle(int x, int y, int width, int height) const = 0;
};

class V1DrawingAPI : public IDrawingAPI {
public:
  void drawCircle(int x, int y, int radius) const override {
    cout << "[V1] Circle at (" << x << "," << y << ") radius " << radius
         << "\n";
  };

  void drawRectangle(int x, int y, int width, int height) const override {
    cout << "[V1] Rectangle at (" << x << "," << y << ") width " << width
         << " height " << height << "\n";
  };
};

class V2DrawingAPI : public IDrawingAPI {
public:
  void drawCircle(int x, int y, int radius) const override {
    cout << "[V2] Smooth Circle at (" << x << "," << y << ") radius " << radius
         << "\n";
  };

  void drawRectangle(int x, int y, int width, int height) const override {
    cout << "[V2] Filled Rectangle at (" << x << "," << y << ") width " << width
         << " height " << height << "\n";
  };
};

class IShape {
public:
  IShape(shared_ptr<IDrawingAPI> drawingApi) : api(move(drawingApi)) {
  }
  virtual ~IShape() = default;
  virtual void draw() const = 0;

protected:
  shared_ptr<IDrawingAPI> api;
};

class Circle : public IShape {
public:
  Circle(int x, int y, int radius, shared_ptr<IDrawingAPI> api)
      : IShape(move(api)), x(x), y(y), radius(radius) {};
  void draw() const override {
    api->drawCircle(x, y, radius);
  };

private:
  int x, y, radius;
};

class Rectangle : public IShape {
public:
  Rectangle(int x, int y, int width, int height, shared_ptr<IDrawingAPI> api)
      : IShape(move(api)), x(x), y(y), width(width), height(height) {};

  void draw() const override {
    api->drawRectangle(x, y, width, height);
  };

private:
  int x, y, width, height;
};

int main() {
  cout << string(50, '=') << "\n";
  cout << "[v1 Drawing API]\n";

  // explicitly specify the type
  shared_ptr<V1DrawingAPI> v1Api = make_shared<V1DrawingAPI>();
  unique_ptr<Circle> circle1 = make_unique<Circle>(10, 20, 5, v1Api);
  unique_ptr<Rectangle> rect1 = make_unique<Rectangle>(30, 40, 10, 8, v1Api);

  circle1->draw();
  rect1->draw();

  cout << string(50, '=') << "\n";
  cout << "[v2 Drawing API]\n";

  // using 'auto' to automatically deduce the type
  auto v2Api = make_shared<V2DrawingAPI>();
  auto circle2 = make_unique<Circle>(100, 150, 25, v2Api);
  auto rect2 = make_unique<Rectangle>(200, 250, 70, 40, v2Api);

  circle2->draw();
  rect2->draw();

  return 0;
};