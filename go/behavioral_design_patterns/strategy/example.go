package main

import "fmt"

type ITextFormatter interface {
	Format(text string)
}

type PlainTextFormatter struct{}

func (p PlainTextFormatter) Format(text string) {
	fmt.Println("Plain: ", text)
}

type MarkdownFormatter struct{}

func (m MarkdownFormatter) Format(text string) {
	fmt.Printf("Markdown: **%s**\n", text)
}

type HtmlFormatter struct{}

func (h HtmlFormatter) Format(text string) {
	fmt.Printf("HTML: <b>%s</b>\n", text)
}

type TextEditor struct {
	formatter ITextFormatter
}

func NewTextEditor(f ITextFormatter) *TextEditor {
	return &TextEditor{formatter: f}
}

func (e *TextEditor) SetFormatter(f ITextFormatter) {
	e.formatter = f
}

func (e *TextEditor) PublishText(text string) {
	e.formatter.Format(text)
}

func main() {
	const message = "Hello, world!"

	editor := NewTextEditor(PlainTextFormatter{})
	editor.PublishText(message)

	editor.SetFormatter(MarkdownFormatter{})
	editor.PublishText(message)

	editor.SetFormatter(HtmlFormatter{})
	editor.PublishText(message)
}
