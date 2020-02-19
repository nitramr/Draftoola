# Draftoola
Open Source UI and UX prototyping tool for designing static and animated layouts.

*Draftoola* is a combination out of "draft" and "tool".

**Note: it is an early development state and not ready to use!**

## Development State
![Bildschirmfoto von 2019-05-05 12-56-01](https://user-images.githubusercontent.com/15112256/71785561-5b1dc680-3001-11ea-818f-7623ac3dc898.png)

## Dependencies
Draftoola requires minimum Qt 5.14 - https://www.qt.io/download
Draftoola requires Skia - https://skia.org/

## Prepare Skia library

### Download Skia
Download Skia somewhere on your local machine by following instructions. \
Draftool code is tested with "chrome/m81" branch from Skia library. You can use a later one, but it is not tested. \
Open your terminal and navigate to your preferred folder where Skia should be downloaded.

```
git clone -b chrome/m81 --single-branch https://github.com/google/skia.git
```

### Install dependencies

Install 3rd party libs and other dependencies for Skia.
```
cd skia
python2 tools/git-sync-deps
```

Install missing dependencies
```
tools/install_dependencies.sh
```

### Precompile Skia

Now Skia have to precompiled as a static library. You can follow the official instructions on https://skia.org/user/build. \

#### Example for Ubuntu

Create output folder and setup instructions for compiler.
```
bin/gn gen out/Release  --args='is_debug=false'
```

Compile via ninja. Depending on processing power of your machine it takes a while.
```
ninja -C out/Release
```

### Add environment variable in QtCreator
Now we have to tell Draftoola where Skia is located. Add a new environment variable in QtCreator. \
Variable: SKIA_DIR \
Value: %your-path-to-skia-folder%/skia


## Development Notes
Every vector-based path processing program needs good path operations, such as Boolean path operation, expanding and shrinking paths, etc. In the best case, the Bezier paths are retained in these operations. Qt SVG ist not the best library to render and work with SVG's. Target is to implement a powerful library.
\
\
The following libraries can be used.
* [Skia Graphics Library (Google Chrome)](https://skia.org/) - currently in use for path processing
* [lib2geom (Inkscape)](http://lib2geom.sourceforge.net/)
* [resvg](https://github.com/RazrFalcon/resvg)
