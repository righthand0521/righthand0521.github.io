# Programming

- [styleguide](https://google.github.io/styleguide/)
- [sonarqube](https://www.sonarqube.org/)
- [regex101: build, test, and debug regex](https://regex101.com/)
- [URL Encode and Decode - Online](https://www.urlencoder.org/)

## cloc(1) - Count, or compute differences of, lines of source code and comments.

```bash
apt install cloc -y
```

## Visual Studio Code

- [Download Visual Studio Code](https://code.visualstudio.com/download)
- [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)

```bash
apt install software-properties-common apt-transport-https wget -y
wget -O- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor | tee /usr/share/keyrings/vscode.gpg
echo deb [arch=amd64 signed-by=/usr/share/keyrings/vscode.gpg] https://packages.microsoft.com/repos/vscode stable main \
| tee /etc/apt/sources.list.d/vscode.list
apt update

apt install code -y

alias code='code --no-sandbox --user-data-dir'
code
```
