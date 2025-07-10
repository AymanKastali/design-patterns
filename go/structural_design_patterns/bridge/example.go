package main

import "fmt"

type IDrawingAPI interface {
	DrawCircle(x, y, radius int)
	DrawRectangle(x, y, width, height int)
}

type V1DrawingAPI struct{}

func (api *V1DrawingAPI) DrawCircle(x, y, radius int) {
	fmt.Printf("[V1] Circle at (%d,%d) radius %d\n", x, y, radius)
}

func (api *V1DrawingAPI) DrawRectangle(x, y, width, height int) {
	fmt.Printf("[V1] Rectangle at (%d,%d) width %d height %d\n", x, y, width, height)
}

type V2DrawingAPI struct{}

func (api *V2DrawingAPI) DrawCircle(x, y, radius int) {
	fmt.Printf("[V2] Smooth Circle at (%d,%d) radius %d\n", x, y, radius)
}

func (api *V2DrawingAPI) DrawRectangle(x, y, width, height int) {
	fmt.Printf("[V2] Filled Rectangle at (%d,%d) width %d height %d\n", x, y, width, height)
}

type Shape interface {
	Draw()
}

type Circle struct {
	x, y, radius int
	api          IDrawingAPI
}

func NewCircle(x, y, radius int, api IDrawingAPI) *Circle {
	return &Circle{x: x, y: y, radius: radius, api: api}
}

func (c *Circle) Draw() {
	c.api.DrawCircle(c.x, c.y, c.radius)
}

type Rectangle struct {
	x, y, width, height int
	api                 IDrawingAPI
}

func NewRectangle(x, y, width, height int, api IDrawingAPI) *Rectangle {
	return &Rectangle{x: x, y: y, width: width, height: height, api: api}
}

func (r *Rectangle) Draw() {
	r.api.DrawRectangle(r.x, r.y, r.width, r.height)
}

func main() {
	fmt.Println("======================= v1 =======================")
	v1API := &V1DrawingAPI{}
	circle1 := NewCircle(10, 20, 5, v1API)
	rect1 := NewRectangle(30, 40, 10, 8, v1API)
	circle1.Draw()
	rect1.Draw()

	fmt.Println("======================= v2 =======================")
	v2API := &V2DrawingAPI{}
	circle2 := NewCircle(100, 150, 25, v2API)
	rect2 := NewRectangle(200, 250, 70, 40, v2API)
	circle2.Draw()
	rect2.Draw()
}
