/*	Test Result
 *
 *	GET 127.0.0.1:5566/
 *	POST 127.0.0.1:5566/
 *
 *	<html><head></head><body><h3>Hello, Node.js.</h3></body></html>
 *	<html><head></head><body><h3>Hello, Node.js.</h3></body></html>
 */


var http = require('http');
var httpGetOptions = {
	host: '127.0.0.1',
	path: '/',
	port: '5566',
	method: 'GET'
};
var httpPostOptions = {
	host: '127.0.0.1',
	path: '/',
	port: '5566',
	method: 'POST'
};

callback = function(response) {
	var str = '';

	response.on('data', function(chunk) {
		str += chunk;
	});

	response.on('end', function () {
		console.log(str);
	});
}

console.log('%s %s:%s%s', httpGetOptions['method'], httpGetOptions['host'], httpGetOptions['port'], httpGetOptions['path']);
var httpGetRequest = http.request(httpGetOptions, callback);
httpGetRequest.end();

console.log('%s %s:%s%s', httpPostOptions['method'], httpPostOptions['host'], httpPostOptions['port'], httpPostOptions['path']);
var httpPostRequest = http.request(httpPostOptions, callback);
httpPostRequest.write("Hello, world!");
httpPostRequest.end();

console.log();

