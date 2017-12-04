/*
NOTE: You need to intall the npm modules by executing >npm install
before running this server

Simple express server re-serving data from food2fork.com
To test: 
http://localhost:3000
or
http://localhost:3000/recipes?ingredient=Ginger
to just set JSON response. (Note it is helpful to add a JSON formatter extension, like JSON Formatter, to your Chrome browser for viewing just JSON data.)
*/
const express = require('express'); //express framework
const requestModule = require('request'); //npm module for easy http requests
const fs = require('fs'); //need to read static files
const logger = require('morgan'); //request logger
const PORT = process.env.PORT || 3000;

const API_KEY = '105e7db400f95c68dbac38ef579b3885'; //PUT IN YOUR OWN KEY HERE

const app = express();

//Middleware
app.use(logger('dev'));
app.use(express.static(__dirname + '/public')); //static server

//Routes
app.get('/', (request, response) => {
	response.sendFile(__dirname + '/views/index.html');
})

//loads client with ingredient
app.get('/recipes',(request, response) => {
	let ingredient = request.query.ingredient;
	if(!ingredient) {
		ingredient = "";
	}
	const url = `http://www.food2fork.com/api/search?q=${ingredient}&key=${API_KEY}`;
	
	let filePath = __dirname + '/views/index.html';
	fs.readFile(filePath, 'utf8', function(err,data){
		if(err){
			//report error to console
			console.log('ERROR: ' + JSON.stringify(err));
			response.end(JSON.stringify(err));
			return;
		}
		//console.log(data);
		data = data.replace(`id="ingredient" value=""`, `id="ingredient" value="${ingredient}"`);
		response.contentType('text/html').send(data);
	});
})

//allows client to request api info
app.post('/recipes', (request, response) => {
	let ingredient = request.query.ingredient;
	if(!ingredient) {
		return response.json({message: 'Please enter an ingredient name'});
	}
	const url = `http://www.food2fork.com/api/search?q=${ingredient}&key=${API_KEY}`
	
	//console.log("ingredient: " + ingredient);
	//console.log("url: " + url);
	
	requestModule.get(url, (err, res, data) => {
		if(err){
			console.log(err);
			return;
		}
		return response.contentType('application/json').json(JSON.parse(data))
	})
})

//start server
app.listen(PORT, err => {
	if(err) console.log(err)
	else {
		console.log(`Server listening on port: ${PORT}`)
	}
})