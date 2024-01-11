# [Robot Framework](https://robotframework.org/)

- [Robot Framework User Guide](https://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html)

## Install

```bash
pip install robotframework
pip install robotframework==4.0.1

pip install --upgrade robotframework

pip uninstall robotframework
```

```bash
pip install robotframework-ride==1.5.2.1

apt install software-properties-common -y
add-apt-repository ppa:nilarimogard/webupd8
apt-get install python-wxgtk2.8 python-wxtools wx2.8-i18n -y

pip install pygments
pip install -U requests
```

### Windows

```text
1. 下載 Python -> 設定環境變數 -> 升級 pip
   $ python -m pip install --upgrade robotframework
2. Install Robot Framework and 驗證Robot Framework安裝完成
   $ python -m pip install robotframework
   $ python -m robot --version
3. Install selenium2library
   $ python -m pip install robotframework-selenium2library
4. Install wxPython
   $ python -m pip install -U wxPython
5. Install RIDE
   $ python -m pip install robotframework-ride
6. Execute ride.py to run the RIDE
```

## [libdoc.py](https://robotframework.org/robotframework/2.1.2/tools/libdoc.html)

```bash
python -m robot.libdoc <option> <file> <html>
```

## [testdoc.py](https://robotframework.org/robotframework/2.1.2/tools/testdoc.html)

```bash
python -m robot.testdoc <option> <file> <html>
```

## [Standard Libraries: Telnet](https://robotframework.org/robotframework/latest/libraries/Telnet.html)

## [robotframework: SSHLibrary](http://robotframework.org/SSHLibrary/SSHLibrary.html)

- [Robot Framework test library for SSH and SFTP](https://github.com/robotframework/SSHLibrary)

## [robotframework-vim](https://github.com/mfukar/robotframework-vim)

```bash
git clone https://github.com/mfukar/robotframework-vim.git
cd robotframework-vim
cp -R * ~/.vim/
cd -
ls -l  ~/.vim/
```

## [robotframework-hub](https://github.com/boakley/robotframework-hub)

```bash
pip install robotframework-hub
rfhub -h
rfhub -i 0.0.0.0
```

## [robotframework-metrics](https://github.com/adiralashiva8/robotframework-metrics)

```bash
pip install robotframework-metrics
robotmetrics -h
robotmetrics
```

```bash
robot --dotted --variable var1:test --include=run --exclude=stop $(pwd)
```

## [robotframework-jsonlibrary 0.5](https://pypi.org/project/robotframework-jsonlibrary/)
