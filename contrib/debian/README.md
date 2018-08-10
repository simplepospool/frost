
Debian
====================
This directory contains files used to package bifrostd/bifrost-qt
for Debian-based Linux systems. If you compile bifrostd/bifrost-qt yourself, there are some useful files here.

## bifrost: URI support ##


bifrost-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bifrost-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bifrostqt binary to `/usr/bin`
and the `../../share/pixmaps/bifrost128.png` to `/usr/share/pixmaps`

bifrost-qt.protocol (KDE)

