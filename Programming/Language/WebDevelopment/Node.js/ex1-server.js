/*	Test Result
 *
 *	GET / HTTP/1.1
 *	{ host: '127.0.0.1:5566', connection: 'close' }
 *	body:
 *
 *	POST / HTTP/1.1
 *	{ host: '127.0.0.1:5566',
 *	  connection: 'close',
 *	  'transfer-encoding': 'chunked' }
 *	body: Hello, world!
 */


var http = require('http');
var port = 5566;

http.createServer(function(request, response) {
	var httpVersion = request.httpVersion;
	var header = request.headers;
/*	var headerFields = {
		'host': header['host'],
		'connection': header['connection'],
		'cache-control': header['cache-control'],
		'upgrade-insecure-requests': header['upgrade-insecure-requests'],
		'user-agent': header['user-agent'],
		'accept': header['accept'],
		'dnt': header['dnt'],
		'accept-encoding': header['accept-encoding'],
		'accept-language': header['accept-language']
	};
	console.log(JSON.stringify(headerFields));
*/
	var method = request.method;
	var url = request.url;
	var body = [];

	request.on('error', function(err) {
		console.error(err);
	}).on('data', function(chunk) {
		body.push(chunk);
	}).on('end', function() {
		body = Buffer.concat(body).toString();

		console.log('%s %s HTTP/%s', method, url, httpVersion);
		console.log(header);
		console.log('body: %s', body);	// HTTP POST by test cmd: curl -d 'hello' http://127.0.0.1:5566
		console.log();

		response.on('error', function(err) {
			console.error(err);
		});

//		response.writeHead(200, {'Content-Type': 'text/html'});
		response.statusCode = 200;
		response.setHeader('Content-Type', 'text/html');

		buildHtml(request, response);

		response.end();
	});
}).listen(port);

function buildHtml(request, response) {
	response.write('<html>');
	buildHead(request, response);
	buildBody(request, response);
	response.write('</html>');
};

function buildHead(request, response) {
	response.write('<head>');
	response.write('</head>');
};

function buildBody(request, response) {
	response.write('<body>');
	response.write('<h3>Hello, Node.js.</h3>');
	response.write('</body>');
};

