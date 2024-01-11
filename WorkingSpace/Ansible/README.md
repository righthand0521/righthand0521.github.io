# [Ansible](https://github.com/ansible/ansible)

- [Ansible Documentation](https://docs.ansible.com/ansible/latest/index.html)

```text
控制主機 (Control Machine)
- 安裝 Ansible 在 Control Machine

被控節點 (Managed Node)
- 透過 Ansible 管理的 Managed Node 完全不需要安裝 Ansible
- 只需要確保這個節點可以透過 SSH 與 Control Machine 溝通, 並已安裝 Python 2.6 以上的版本就可以透過 Control Machine 來進行部署及管理了
```

```bash
apt install ansible -y
ansible --version

vim /etc/ansible/ansible.cfg
```

```bash
vim /etc/ansible/hosts

ansible --list-hosts all
```

```bash
ansible all -m ping
ansible all -m "command" -a "uname -n"

ansible-playbook playbook.yml
```

```bash
pip install ansible-lint
pip3 install ansible-lint
ansible-lint --version

ansible-lint playbook.yml
```
