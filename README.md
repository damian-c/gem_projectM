# gem_projectM
Milkdrop compatible music visualizer for Pure Data

![Screenshot](https://github.com/damian-c/gem_projectM/raw/master/web/screenshot-2018-09-10.png)

## Requirements
* [Pure Data](https://puredata.info) - visual patch-based programming language
* [GEM](https://gem.iem.at) - Graphics Environment for Multimedia
* [projectM](http://projectm.sourceforge.net) - OpenGL reimplementation of Milkdrop as a library

## Installation
### Linux
* Type `make`
* Copy gem_projectM.pd_linux to one of the paths set in your Pure Data preferences
* Copy the projectM config file, config.inp, to the working directory for your Pure Data projects

## Usage
* Run pd from the working directory containing the config.inp file
* Add a gem_projectM object
* Connect a gemhead to the first inlet
* Connect an adc~ object to the second inlet
* Connect the outlet to the second inlet of a pix_texture
* Connect that pix_texture to a rectangle

## TODO:
* use an actual build system
* make the config file location selectable
* fix full screen mode
