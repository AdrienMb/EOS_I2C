//Loading modules
const execFile = require('child_process').execFile;
var http = require('http');
var fs = require('fs');
var path = require('path');

// Initialize the server on port 8888
var server = http.createServer(function (req, res) {
    // requesting files
    var file = '.'+((req.url=='/')?'/index.html':req.url);
    var fileExtension = path.extname(file);
    var contentType = 'text/html';
    // Uncoment if you want to add css to your web page
    /*
    if(fileExtension == '.css'){
        contentType = 'text/css';
    }*/
    fs.exists(file, function(exists){
        if(exists){
            fs.readFile(file, function(error, content){
                if(!error){
                    // Page found, write content
                    res.writeHead(200,{'content-type':contentType});
                    res.end(content);
                }
            });
        }
        else{
            // Page not found
            res.writeHead(404);
            res.end('Page not found');
        }
    });
}).listen(8888);

// Loading socket io module.
// SEE KNOWHOW FILE TO LINK SOCKET.IO
var io = require('socket.io').listen(server);

// When communication is established
io.on('connection', function (socket) {
    socket.on('readSensor', function handleSensor() {
		const child = execFile('./greenhouse', (error, stdout, stderr) => {
		if(error) {
			console.error('stderr', stderr);
			throw error;
		}
		console.log(stdout);
		// Cut out temperature and humidity values from sensor output
		var posHumidity = stdout.indexOf("H: ") + 3;
		var humi = stdout.slice(posHumidity, posHumidity+3);
		var posTemp = stdout.indexOf("T: ") + 3;
		var temp = stdout.slice(posTemp, posTemp+2);
		// Create and send JSON object to browser
		var data = {temperature: temp, humidity: humi};
		var dataJSON = JSON.stringify(data);
		io.emit('sensorData', dataJSON);
		});
	});
});

// Displaying a console message for user feedback
server.listen(console.log("Server Running ..."));
