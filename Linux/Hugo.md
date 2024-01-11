# [Hugo](https://gohugo.io/)

## Install

```bash
wget https://github.com/gohugoio/hugo/releases/download/v0.81.0/hugo_extended_0.81.0_Linux-64bit.tar.gz
tar -zxvf hugo_extended_0.81.0_Linux-64bit.tar.gz
mv hugo /usr/local/bin/
```

## Create Site

```bash
hugo new site blog
cd blog/
```

## Themes

[hello-friend-ng](https://themes.gohugo.io/hugo-theme-hello-friend-ng/)

```bash
git clone https://github.com/rhazdon/hugo-theme-hello-friend-ng.git themes/hello-friend-ng
# vim config.toml

theme = "hello-friend-ng"
```

## Post

```bash
hugo new posts/hello.md
vim content/posts/hello.md
```

## Start

```bash
hugo server -D
http://localhost:1313

hugo
ls -l public/
```
