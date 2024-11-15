
# Sublime Text 4 Patcher
# Important: Doesnt work on 4180 and above, how to fix:
- Change srPtr to 80 79 05 00 0F 94 C2
- Change rpPtr to C6 41 05 01 B2 00 90

## How to use on windows:
- Compile the cpp file (g++ / vs) or download from releases
- Make sure you have Sublime Text installed
- Put the sublime_text.exe file from Sublime Text folder to the same place as the compiled main.cpp
- Run the patcher
- Put sublime_text.exe back in the Sublime Text folder
- You should now have unlimited Sublime Text license

## How to use on linux (might error):
- Compile the cpp file (g++ or any other)
- Make sure you have Sublime Text installed
- Move sublime_text to the same folder as the compiled patcher `sudo mv /opt/sublime_text/sublime_text /path/to/folder`
- Run the patcher as sudo
- Move sublime_Text back to Sublime Text folder `sudo mv sublime_text /opt/sublime_text/`
- You should now have unlimited Sublime Text license

_you may require to re run everytime sublime updates_

_if any errors appear you may have to fix it by yourself._
