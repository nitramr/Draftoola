# Draftoola
Open Source UI and UX prototyping tool for designing static and animated layouts.

*Draftoola* is a combination out of "draft" and "tool".

**Note: it is an early development state and not ready to use!**

## Development State
![Bildschirmfoto von 2019-05-05 12-56-01](https://user-images.githubusercontent.com/15112256/71785561-5b1dc680-3001-11ea-818f-7623ac3dc898.png)

## Development Notes
Every vector-based path processing program needs good path operations, such as Boolean path operation, expanding and shrinking paths, etc. In the best case, the Bezier paths are retained in these operations. Qt SVG ist not the best library to render and work with SVG's. Target is to implement a powerful library.
\
\
The following libraries can be used.
* [Skia Graphics Library (Google Chrome)](https://skia.org/)
* [lib2geom (Inkscape)](http://lib2geom.sourceforge.net/)
* [resvg](https://github.com/RazrFalcon/resvg)
