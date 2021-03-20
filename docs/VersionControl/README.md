Version Control
===
### Git
### Push Local Repository to https://github.com/
```
1. Add 'new repository' in GitHub
2. git remote add origin https://github.com/righthand0521/<Repositories>.git
3. git push -u origin master
```
### [git(1) Manual Page](https://git.github.io/htmldocs/git.html)
### [git-config](https://git.github.io/htmldocs/git-config.html)
```
git config --list
git config --list --local
git config --list --global
git config --list --system

git config --global user.name "Yu-Chuan Cheng"
git config --global user.email "righthand0521@gmail.com"
git config --global core.autocrlf false
git config --global core.symlinks true
git config --global color.ui auto

git config --global diff.tool vimdiff
git config --global difftool.prompt false

git config --global alias.logall 'log --oneline --decorate --graph --all'
```
### [git-init](https://git.github.io/htmldocs/git-init.html)
```
git init
```
### [git-clone](https://git.github.io/htmldocs/git-clone.html)
```
git clone -c core.symlinks=true git+ssh://git@<IP Address>/<Repositories>.git
```
### [git-status](https://git.github.io/htmldocs/git-status.html)
```
git status
git status -bs
git status -v
```
### [git-diff](https://git.github.io/htmldocs/git-diff.html)
```
git diff
git diff --cached
git diff HEAD^
git diff HEAD -- ./lib
git diff origin/master..master
git diff origin/master..master --stat
git diff --numstat
git diff > $(git show -s --format=%cd --date=short)_$(git rev-parse --verify HEAD --short=6).diff
```
### [git-add](https://git.github.io/htmldocs/git-add.html)
```
git add
```
### [git-rm](https://git.github.io/htmldocs/git-rm.html)
```
git remove
```
### [git-commit](https://git.github.io/htmldocs/git-commit.html)
```
git commit
git commit -m "commit content"
git commit -am "add and commit content"
git commit --amend -m 'append content'
```
### [git-push](https://git.github.io/htmldocs/git-push.html)
```
git push
git push origin master
git push --progress "origin" master:master
```
### [git-log](https://git.github.io/htmldocs/git-log.html)
```
git log
git log -1
git log --stat
git log --name-status
git log -p -m
git log --pretty=format:'%h %s' --graph
git log --oneline --decorate --graph --all
```
#### [檢視提交的歷史記錄](https://git-scm.com/book/zh-tw/v2/Git-%E5%9F%BA%E7%A4%8E-%E6%AA%A2%E8%A6%96%E6%8F%90%E4%BA%A4%E7%9A%84%E6%AD%B7%E5%8F%B2%E8%A8%98%E9%8C%84)
```
git log --pretty=format:"%h - %an, %ar : %s"

%H	該提交 SHA-1 雜湊值
%h	該提交簡短的 SHA-1 雜湊值
%T	「樹（tree）」物件的 SHA-1 雜湊值
%t	「樹」物件簡短的 SHA-1 雜湊值
%P	親代（parent）提交的 SHA-1 雜湊值
%p	親代提交簡短的 SHA-1 雜湊值
%an	作者名字
%ae	作者電子郵件
%ad	作者日期（依據 --date 選項值而有不同的格式）
%ar	作者日期，相對時間格式。
%cn	提交者名字
%ce	提交者電子郵件
%cd	提交者日期
%cr	提交者日期，相對時間格式。
%s	標題
```
### [git-whatchanged](https://git.github.io/htmldocs/git-whatchanged.html)
```
git whatchanged
```
### [git-shortlog](https://git.github.io/htmldocs/git-shortlog.html)
```
git shortlog
```
### [git-branch](https://git.github.io/htmldocs/git-branch.html)
```
git branch
git branch -a
git branch --merged
git branch --no-merged
git show-branch
git show-branch --all
```
### [git-checkout](https://git.github.io/htmldocs/git-checkout.html)
```
git checkout
git checkout .
git checkout master
git checkout <tag_name>
```
### [git-tag](https://git.github.io/htmldocs/git-tag.html)
```
git tag
```
### [git-fetch](https://git.github.io/htmldocs/git-fetch.html)
```
git fetch
git fetch --prune
```
### [git-clean](https://git.github.io/htmldocs/git-clean.html)
```
git clean -f
```
### Retrieve the hash for the current commit
```
git rev-parse --verify HEAD
git rev-parse --short HEAD
```
### .gitignore
```
https://github.com/github/gitignore
git clone https://github.com/github/gitignore.git
```
### gitk(1) - The Git repository browser
```
# apt install gitk -y
# gitk --all
```
---
### GitHub
### [GitHub CLI](https://cli.github.com/)
```
# apt-key adv --keyserver keyserver.ubuntu.com --recv-key C99B11DEB97541F0
# apt-add-repository https://cli.github.com/packages
# apt update
# apt install gh -y
```
![gh auth login](ghAuth.png)
#### [GitHub CLI：用指令就能開 issue、發 PR](https://ithelp.ithome.com.tw/articles/10240215)
---
### [Git Lab](https://docs.gitlab.com/ee/README.html)
### [Install self-managed GitLab](https://about.gitlab.com/install/#ubuntu)
```
# vim /etc/gitlab/gitlab.rb

# external_url 'http://gitlab.example.com'
external_url 'http://<IP Address>:<Port>'

# gitlab_rails['time_zone'] = 'UTC'
gitlab_rails['time_zone'] = 'Asia/Taipei'
```
```
# ls -l /var/opt/gitlab

# gitlab-ctl start
# gitlab-ctl status
# gitlab-ctl restart
# gitlab-ctl reconfigure

# gitlab-ctl tail redis
# rm -rf /var/opt/gitlab/redis/dump.rdb

# gitlab-rake gitlab:check
# gitlab-rake gitlab:env:info
```
```
Global Setup
# git config --global user.name "<Name>"
# git config --global user.email <Email>"

Create a New Repository
# git clone http://<IP Address>:<Port>/<Repositories>.git
# cd <Repositories Folder Path
# touch README.md
# git add README.md
# git commit -m "add README"
# git push -u origin master

Existing Folder
# cd <Existing Folder Path>
# git init
# git remote add origin http://<IP Address>:<Port>/<Repositories>.git
# git add .
# git commit -m "Initial commit"
# git push -u origin master

Existing Git Repository
# cd <Existing Repositories Folder Path>
# git remote rename origin old-origin
# git remote add origin http://<IP Address>:<Port>/<Repositories>.git
# git push -u origin --all
# git push -u origin --tags
```
---
### SVN: Apache Subversion
```
# apt install subversion -y

# svn status
# svn log --verbose -r REVNO:HEAD --limit 1
# svn log | sed -n '/<commiter name>/,/-----$/ p'
# svn diff -r
# svn diff -r REVNO:HEAD --summarize
# svn diff -r $i:$j | grep revision
# svn cat -r
# svn add
# svn ci
# svnlook youngest <path>
# svnadmin dump <path> -r <ver>
# find . -iname ".svn" -print0 | xargs -0 rm -r
```
### How to create a new Repositories for SVN
```
Create a new user in system (include FTP account)
1. useradd -g users $NEW_USER
2. cd /etc/vsftpd/user
3. cp example $NEW_USER

Create a new repository
1. cd /opt/svn
2. svnadmin create $NEW_REPO
3. chown -R subversion:subversion $NEW_REPO

Create a new svn account
1. cd /opt/svn/$REPOS_DIR/conf, ex: cd /opt/svn/Prj/conf
2. edit passwd, add new username/passwd for new account

How to change svn url (HTTP login only)
1. vim /etc/httpd/conf.d/subversion.conf
2. modify <location /$OLD_PATH> to <location /$NEW_PATH>
3. service httpd restart

How to change svn repository path (HTTP login only)
1. vim /etc/httpd/conf.d/subversion.conf
2. modify "SVNParentPath $OLD_PATH" to "SVNParentPath $NEW_PATH"
3. service httpd restart
```
### SVN Import File
```
svnadmin create <Project Name>
svn import --no-ignore <Source Code Path> file:///svn/<Project Name>/trunk
chown <user:group> -R <Project Name>
chmod -R g+w <Project Name>
chmod 777
```
```
# vim /etc/bash.bashrc

alias grepsvn='grep --color=auto -rn --exclude="*\.svn*"'
alias svnlog='svn log -v -r'
alias svndel='find -iname ".svn" -exec rm -rf {} \;'
```
---
### CVS: Concurrent Versions System
```
cvs -z5 co -d <name> <moduleName>
cvs -z5 co -D "2015-11-09 00:00:00 GMT" -d <name> <moduleName>
cvs -z5 co -r <tag> -d <name> <moduleName>
cvs up
cvs -nq up
cvs update -j
cvs update -r <version> <file>
cvs status -v <fileName>
cvs -Q status | grep -A 3 -i locally
cvs diff -r
cvs diff -c
cvs diff -Nuc
cvs ci <fileName>
cvs tag -b <tagName> .
```
```
# vim /etc/bash.bashrc

alias cvsst='cvs -Q status | grep -A 3 -i locally | grep Repository'
alias cvsdel='find -name CVS -exec rm -rf {} \;'
```
---
