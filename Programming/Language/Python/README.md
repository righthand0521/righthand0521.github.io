# Python

- [The Python Standard Library](https://docs.python.org/3/library)
- [Awesome Python](https://awesome-python.com/)
- [pythoncheatsheet.org](https://www.pythoncheatsheet.org/)
- [python-cheatsheet](https://github.com/gto76/python-cheatsheet)

## .vimrc

```text
Plugin 'scrooloose/syntastic'
Plugin 'nvie/vim-flake8'

" python
au BufNewFile,BufRead *.py
    \ set tabstop=4 |
    \ set softtabstop=4 |
    \ set shiftwidth=4 |
    \ set textwidth=79 |
    \ set expandtab |
"   \ set autoindent |
    \ set fileformat=unix
let python_highlight_all=1
syntax on

" python/Vundle/scrooloose/syntastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0
let g:syntastic_python_checkers = ['pylint']
let g:syntastic_python_pylint_args = '--disable=missing-docstring'
```

## std

```text
module_name
package_name
ClassName
method_name
ExceptionName
function_name
GLOBAL_VAR_NAME
instance_var_name
function_parameter_name
local_var_name
```

```bash
python -m SimpleHTTPServer 80
```

## [pylint](https://www.pylint.org/)

```bash
apt install pylint -y

pylint --disable=missing-docstring <fileName>.py
pylint --persistent=n --generate-rcfile > pylint.conf
pylint --rcfile=pylint.conf <fileName>.py
```

## [pdb - The Python Debugger](https://docs.python.org/3/library/pdb.html)

```python
import pdb
```

```bash
python -m pdb fileName.py
```

## [pip](https://pip.pypa.io/en/stable/)

```bash
apt install python-pip -y
apt install python3-pip -y

pip install --upgrade pip
python -m pip install --upgrade pip
```

### [externally-managed-environment](https://www.yaolong.net/article/pip-externally-managed-environment/#%E6%96%B9%E6%A1%88%E4%B8%80%E7%B2%97%E6%9A%B4-%E5%8E%BB%E6%8E%89%E8%BF%99%E4%B8%AA%E6%8F%90%E7%A4%BA)

```bash
mv /usr/lib/python3.12/EXTERNALLY-MANAGED /usr/lib/python3.12/EXTERNALLY-MANAGED.bk
```

### pipx

```bash
apt install pipx
pipx ensurepath

pipx install robotframework
pipx ensurepath
pipx uninstall robotframework

pipx install uploadserver
pipx ensurepath
pipx uninstall uploadserver
```

### [NumPy](https://numpy.org/)

```bash
pip3 install numpy
```

### [openpyxl](https://pypi.org/project/openpyxl/)

```bash
pip install openpyxl
```

```text
openpyxl.styles.fill.bgColor.rgb

No Fill     00000000
Black       FF003300
Gray        FF808080
Green       FF008080
Blue        FF0000FF
```

### [sh](https://pypi.org/project/sh/)

```bash
pip install sh
```

### [pyserial](https://pypi.org/project/pyserial/)

```bash
pip install pyserial
```

### [pyinstaller](https://pypi.org/project/pyinstaller/)

```bash
pip install pyinstaller

pyinstaller -F <file name>
```

### [python-nmap](https://pypi.org/project/python-nmap/)

```bash
pip install python-nmap
```

### [influxdb](https://pypi.org/project/influxdb/)

```bash
pip install influxdb
```

### [uploadserver](https://pypi.org/project/uploadserver)

```bash
python3 -m pip install --user uploadserver

python3 -m uploadserver
curl -X POST http://<IP Address>:8000/upload -F 'files=@<Upload File>'
```

## GitHub

### [net-creds](https://github.com/DanMcInerney/net-creds)

```bash
git clone https://github.com/DanMcInerney/net-creds.git

hydra -V -f -l root -P passwords.txt telnet://192.168.0.1
python net-creds.py -p <pcap file>
```

## Question

### [Solve: Ubuntu 18.04 meet No module named 'pip._internal'](https://medium.com/@acer1832a/%E5%9C%A8ubuntu-18-04%E4%B8%8A%E9%81%87%E5%88%B0no-module-named-pip-internal-298f980f9a45)

```bash
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
python3 get-pip.py --force-reinstall
```
