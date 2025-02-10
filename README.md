
# Introduction

A pixel manipulation program using GTK and Cairo. The program is written in purpose of Assignment 5 in COMP 4800 courseware (University of Windsor)

# Team member

Ngoc Doanh Tran

# File Structure
main.c ---------- main program

image.png ----------- synthetic image input data file

# Input file structure
The input file is PNG image, with the name of "image.png"


# Compiling and Run
To start the program, run the following command:
```
gcc $(pkg-config --cflags gtk4) -o main main.c lib/stack.c $(pkg-config --libs gtk4) -Ilib

./main
```
Or run Automaiton Script file at run.sh by

```
./run.sh
```

# Dependencies
GTK	-------- https://download.gnome.org/sources/gtk/

GLib -------- https://download.gnome.org/sources/glib/

Pango -------- https://download.gnome.org/sources/pango/

Gdk-pixbuf -------- https://download.gnome.org/sources/gdk-pixbuf/

ATK	-------- https://download.gnome.org/sources/atk/

GObject-Introspection -------- https://download.gnome.org/sources/gobject-introspection/

Epoxy -------- https://download.gnome.org/sources/libepoxy/

# Installation
For Linux
| Distribution | Binary package | Development package | Additional packages |
| :---:   | :---: | :---: | :---: |
| Arch | gtk4   | -   |-   |
| Debian/Ubuntu | libgtk-4-1 | libgtk-4-dev | gtk-4-examples |
| Fedora | gtk4   | gtk4-devel | -   |

For furthermore:
https://www.gtk.org/docs/installations/linux

# References
https://www.gnu.org/software/libiconv/#TOCdownloading

https://www.cairographics.org

https://en.wikipedia.org/wiki/K-means_clustering


