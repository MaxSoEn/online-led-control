const express = require('express');
const app = express();

const port = 80;

app.get('/', function(req, res){
	res.sendFile(__dirname + "/page/index.html");
});

const server = app.listen(port,function(){
	console.log("server is running at port : " + port);
});

const SocketServer = require('ws').Server;
const wss = new SocketServer({server});

//colors data
let color = {
	red: 0,
	green: 0,
	blue: 0
};
let fadeValue = 0; //value of brightness 
let led = 'r'; //the color that changed

let count = 0; //counter for how many times clients connected
wss.on('connection', function(ws){
	count += 1; // add one when a client connected
	console.log("Client number " + count + " connected");
	ws.send("Hello Client");
	
	//send colors value to client when connected
	ws.send('r' + color["red"]);
	ws.send('g' + color["green"]);
	ws.send('b' + color["blue"]);
	
	ws.on('message', function(msg){
		console.log("message from Client : " + msg.toString()); //show the message that client sent

		if(msg.toString().charAt(0)=='r' || msg.toString().charAt(0)=='g' || msg.toString().charAt(0)=='b'){//check wheither the value to change color
			if(parseInt(msg.toString().substring(1)) >= 0 && parseInt(msg.toString().substring(1)) <= 255){ //check the range
				led = msg.toString().charAt(0);//what color changed
				fadeValue = parseInt(msg.toString().substring(1)); // the brightness of the color that changed
				
				//save data in server for anther client
				if(led == 'r'){
					color["red"] = fadeValue;
				}else if(led == 'g'){
					color["green"] = fadeValue;
				}else if(led == 'b'){
					color["blue"] = fadeValue;
				}
			}
			console.log("Data that will be Sent : " + led + fadeValue)
			broadcast(led + fadeValue); //send data for all clients
		}
		
	});
	
	ws.on('close', function(){
		console.log("client is desconected");
	});
	
});

//function to send data to all clients
function broadcast(msg){
	wss.clients.forEach(function (client){
		if(client.readyState == client.OPEN){ // if client still connected
			client.send(msg);
		}
	});
};