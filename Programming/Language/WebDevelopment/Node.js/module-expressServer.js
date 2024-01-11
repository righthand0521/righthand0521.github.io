/*	https://www.runoob.com/nodejs/nodejs-restful-api.html
 *
 *	npm -p install express
 *	curl http://127.0.0.1:5566/listUsers
 */


var express = require('express');
var app = express();
var fs = require("fs");

app.get('/listUsers', function (req, res) {
	fs.readFile( __dirname + "/" + "module-express.json", 'utf8', function (err, data) {
		console.log(data);
		res.end(data);
	});
})

var server = app.listen(5566, function () {
	var host = server.address().address
	var port = server.address().port

	console.log("http://%s:%s", host, port)
})

