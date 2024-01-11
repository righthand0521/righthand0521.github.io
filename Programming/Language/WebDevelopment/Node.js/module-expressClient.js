/*	GET 127.0.0.1:5566/listUsers

	{
		"user1": {
			"name": "mahesh",
			"password": "password1",
			"profession": "teacher",
			"id": 1
		},
		"user2": {
			"name": "suresh",
			"password": "password2",
			"profession": "librarian",
			"id": 2
		},
		"user3": {
			"name": "ramesh",
			"password": "password3",
			"profession": "clerk",
			"id": 3
		}
	}
 */


var http = require('http');
var httpGetOptions = {
	host: '127.0.0.1',
	path: '/listUsers',
	port: '5566',
	method: 'GET'
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

console.log();

