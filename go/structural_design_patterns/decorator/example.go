package main

import "fmt"

type IText interface {
	Render() string
}

type PlainText struct {
	content string
}

func NewPlainText(content string) *PlainText {
	return &PlainText{content: content}
}

func (p *PlainText) Render() string {
	return p.content
}

type TextDecorator struct {
	wrapped IText
}

func NewTextDecorator(wrapped IText) *TextDecorator {
	return &TextDecorator{wrapped: wrapped}
}

func (d *TextDecorator) Render() string {
	return d.wrapped.Render()
}

type BoldDecorator struct {
	*TextDecorator
}

func NewBoldDecorator(wrapped IText) *BoldDecorator {
	return &BoldDecorator{NewTextDecorator(wrapped)}
}

func (b *BoldDecorator) Render() string {
	return "<b>" + b.TextDecorator.Render() + "</b>"
}

type ItalicDecorator struct {
	*TextDecorator
}

func NewItalicDecorator(wrapped IText) *ItalicDecorator {
	return &ItalicDecorator{NewTextDecorator(wrapped)}
}

func (i *ItalicDecorator) Render() string {
	return "<i>" + i.TextDecorator.Render() + "</i>"
}

type UnderlineDecorator struct {
	*TextDecorator
}

func NewUnderlineDecorator(wrapped IText) *UnderlineDecorator {
	return &UnderlineDecorator{NewTextDecorator(wrapped)}
}

func (u *UnderlineDecorator) Render() string {
	return "<u>" + u.TextDecorator.Render() + "</u>"
}

func main() {
	const message = "Hello, world!"

	text := NewPlainText(message)

	formatted := NewBoldDecorator(NewItalicDecorator(NewUnderlineDecorator(text)))

	fmt.Println(formatted.Render())
}
