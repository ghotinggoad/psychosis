# Makefile

# Compile Linux = "make ", compile Windows = "make OS=Windows ", both only on x86_64 architecture.

# To-do
# 1. include conditional statements to detect OS for cross-platform compile operation
# ^ Done, include arguments "OS=Windows"
# ^^ Now it automatically builds both
# 2. add some form of version control using parsing of values through "menu(int argc, char *argv[])"
# ^ https://stackoverflow.com/questions/3024197/what-does-int-argc-char-argv-mean

psychosis : psychosis-linux-x86_64 psychosis-window-x86_64

psychosis-linux-x86_64 :
	make -f makefile_linux
psychosis-window-x86_64 :
	make -f makefile_windows