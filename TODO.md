# TODO

## Version 1.x.x

### New features

* Add RstParser for reStructuredText
* New MarkDown dialects (GitHub Flavored, with tables support, `mdl`)

## Version 2.x.x

### New features

* Add PdfDisplayDriver using [libharu](https://github.com/libharu/libharu) 
(requires a C++ wrapper)
* Add OdtDisplayDriver (see 
[this document](http://books.evc-cit.info/odbook/book.html) for an idea of 
class system)
* Add `stdin` reading
* Add a configuration file
* Add new options
  * `--width`, `-w` and `--height`, `-h`: to limit the maximum width and height
  * `--wrap`, `-W`: boolean flag to enable or disable the *exterior* of 
the document (for example, if `false`, only display the inside of the
`body` tag in HTML)
of the display window

### Other changes

* Rewrite the Document class (and all of the Paragraph and LineElement classes),
this should be based on the research for and ODF and PDF display driver (maybe
even an ODF parser)
