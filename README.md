# FTDConverter

The FTDConverter is a piece of software I wrote to make my work for my site easier.
On <a href="http://freetimedev.com/FreeCode/unityCode.php" target="blank">freetimedev.com</a> I show
try to teach programming principles, syntax and give away free bits of code.
I wanted it to be highlighted, so it looks better and is easier to understand.
<br />
<br />
The algorithm for detecting keywords and different types of code is done with plain c++,
The GUI stuff is done with the <a href="https://developer.gnome.org/gtkmm/stable/">GTKMM</a> library.
The IDE I use is <a href="https://atom.io/" target="blank">Atom</a> which is just a text editor.
<br />
<br />
If you download the project and want to build it, use the following command (remember that the gtkmm-library is required):
<br />
Mac:
<div style="background-color:black; color: white; padding: .2em;">$ clang++ main.cpp keywords.cpp gui.cpp -o FTDConverter `pkg-config --cflags --libs gtkmm-3.0` -std="c++11"</div>
Linux: (requires the g++ compiler)
<div style="background-color:black; color: white; padding: .2em;">$ g++ main.cpp keywords.cpp gui.cpp -o FTDConverter `pkg-config --cflags --libs gtkmm-3.0` -std="c++11"</div>
Windows:
<br />
Install linux and follow Linux instructions.
