/*
NOTE: You need to intall the npm modules by executing >npm install
before running this server

Simple express server re-serving data from db_recipes (aLaCarteData.xml)
To test: 
http://localhost:3000
or
http://localhost:3000/recipes?ingredient=Ginger&spices=cumin

Testing Account: (user: ldnel password: secret)
*/

//Cntl+C to stop server

var http = require('http');
var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');

var  app = express(); //create express middleware dispatcher

const PORT = process.env.PORT || 3000;

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs'); //use hbs handlebars wrapper

app.locals.pretty = true; //to generate pretty view-source code in browser

//read routes modules
var routes = require('./routes/index');

//some logger middleware functions
function methodLogger(request, response, next){           
		   console.log("METHOD LOGGER");
		   console.log("================================");
		   console.log("METHOD: " + request.method);
		   console.log("URL:" + request.url);
		   next(); //call next middleware registered
}
function headerLogger(request, response, next){           
		   console.log("HEADER LOGGER:")
		   console.log("Headers:")
           for(k in request.headers) console.log(k);
		   next(); //call next middleware registered
}

//register middleware with dispatcher
//ORDER MATTERS HERE
//middleware
app.use(routes.authenticate); //authenticate user
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(express.static(__dirname + '/public'));
//app.use(methodLogger);
//routes
app.get('/', 			routes.find); 
app.get('/users', 		routes.users);
app.get('/recipe/*', 	routes.recipeDetails);
app.get('/recipes*', 	routes.find);
//post to return json data
app.post('/recipes', 	routes.recipesData);


//start server
app.listen(PORT, err => {
  if(err) console.log(err)
  else {console.log(`Server listening on port: ${PORT} CNTL:-C to stop`)}
})