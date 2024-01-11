# [Node.js](https://nodejs.org/zh-tw/)

- [# Node.js 教程](https://www.runoob.com/nodejs/nodejs-tutorial.html)

## Install

```bash
curl -sL https://deb.nodesource.com/setup_12.x | bash -

apt install nodejs -y
node -v

apt install npm -y
npm -v
```

### [npm](https://www.npmjs.com/)

```bash
cd /var/www/html
mkdir nodeJs
cd nodeJs
npm init
```

### [express](https://www.npmjs.com/package/express)

```bash
npm install express --save
```

### [json-server](https://www.npmjs.com/package/json-server)

```bash
npm install -g json-server
```

- vim db.json

```bash
{
    "posts": [
        {
            "id": 1,
            "title": "json-server",
            "author": "typicode"
        }
    ],
    "comments": [
        {
            "id": 1,
            "body": "some comment",
            "postId": 1
        }
    ],
    "profile": {
        "name": "typicode"
    }
}
```

```bash
json-server --watch db.json

curl -s -X GET <http://localhost:3000/posts>
curl -s -X GET <http://localhost:3000/comments>
curl -s -X GET <http://localhost:3000/profile>
```
