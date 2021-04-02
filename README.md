# Dumper

Author: Francisco Spínola

## SUMMARY
Dumper is a software that extracts all the Wi-Fi credentials present on a Windows system.


### DESCRIPTION
There are 2 files, one is a demo (*demo.c*) and the other is the real thing (*dumper.c*).

The demo version allows you to execute the *dumper* with a friendly GUI so you can see what it looks like. 

The other version is the "obfusctation" version of the tool. When executed, tries to hide itself (if a GUI can be created) renaming the windows to "Notepad and by resizing the window and changing the background color to white, looking similar to a notepad.

Finally, a file named ".licence.txt" (for obfusctation) is created with all the credentials stored in the system.



### COMPILING
`$ gcc dumper.c -o dumper.exe`



### EXECUTION
You can execute the program on a terminal or by double clicking the executable.

Terminal execution:
`PS > .\dumper.exe`



### WARNING
+ You need to have Administrator privileges
+ Careful when double clicking, since you will spawn a (small) GUI and that can warn a "victim" of what's happening.
+ Do not use this software where you're not authorized or for malicious purposes! This was made for testing and educational purposes. Be ethical.



### LICENSE

Copyright (C) 2021, Francisco Spínola

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

The software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

Check out the GNU General Public License: http://www.gnu.org/licenses/.



### MESSAGE
Have fun while using it during your physical pentesting activity!

Be sure to check out my other projects at my [website](https://fssecur3.github.io/ "Francisco Spínola's Portfolio").

If you find any problem with this software be free to contact me: fssecur3@outlook.com

Hope y'all like it. :)
