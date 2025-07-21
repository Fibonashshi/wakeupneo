# Wake up, Neo...
Wake Up, Neo is a simple terminal application in C that displays messages with a typewriter effect, inspired by the iconic lines from The Matrix.

![wakeupneo](https://github.com/user-attachments/assets/470151ec-a0fc-4beb-b530-511dcac4c84f)

## 🔧 Compiling

Simply type in the projects directory: 
```bash
make
```
You can also install it using:
```bash
sudo make install
```

## 🏃 Usage

You can run the program with your own message:
```bash
wake-up-neo --message example.txt
```
The example file should look like:
```example.txt
Hi!
This is a custom message.
It is being displayed line by line.
```
## 🛠️ Requirements
wake-up-neo was made for OS-es with [POSIX](https://pl.wikipedia.org/wiki/Unistd.h), as it uses unistd.h library. Also, it uses the **[ncurses](https://en.wikipedia.org/wiki/Ncurses)** library. It can be installed on different operating systems using:
### Arch Linux

```bash
sudo pacman -S ncurses
```
### macOS

```bash
brew install ncurses
```
### Debian based operating systems 

```bash
sudo apt install libncurses5-dev libncursesw5-dev
```
