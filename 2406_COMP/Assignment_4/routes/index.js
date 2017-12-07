/*
Provides functions for the server_recipe.js server
*/

const url = require('url');
const sqlite3 = require('sqlite3').verbose(); //verbose provides more detailed stack trace
const db = new sqlite3.Database('data/db_recipes');

db.serialize(function(){
	  //make sure a couple of users exist in the database.
	  //user: ldnel password: secret
	  //user: frank password: secret2
      var sqlString = "CREATE TABLE IF NOT EXISTS users (userid TEXT PRIMARY KEY, password TEXT)";
      db.run(sqlString);
      sqlString = "INSERT OR REPLACE INTO users VALUES ('ldnel', 'secret')";
      db.run(sqlString);
      sqlString = "INSERT OR REPLACE INTO users VALUES ('frank', 'secret2')";
      db.run(sqlString);      	  
  });

exports.authenticate = function (request, response, next){
    /*
	Middleware to do BASIC http 401 authentication
	*/
    var auth = request.headers.authorization;
	// auth is a base64 representation of (username:password) 
	//so we will need to decode the base64 
	if(!auth){
 	 	//note here the setHeader must be before the writeHead
		response.setHeader('WWW-Authenticate', 'Basic realm="need to login"'); 
        response.writeHead(401, {'Content-Type': 'text/html'});
		console.log('No authorization found, send 401.'); 
 		response.end();  
	}
	else{
	    console.log("Authorization Header: " + auth);
        //decode authorization header
		// Split on a space, the original auth 
		//looks like  "Basic Y2hhcmxlczoxMjM0NQ==" and we need the 2nd part 
        var tmp = auth.split(' ');   		
		
		// create a buffer and tell it the data coming in is base64 
        var buf = new Buffer(tmp[1], 'base64'); 
 
        // read it back out as a string 
        //should look like 'ldnel:secret'		
		var plain_auth = buf.toString();    
        console.log("Decoded Authorization ", plain_auth); 
		
        //extract the userid and password as separate strings 
        var credentials = plain_auth.split(':');      // split on a ':' 
        var username = credentials[0]; 
        var password = credentials[1]; 
        console.log("User: ", username); 
        console.log("Password: ", password); 
		
		var authorized = false;
		//check database users table for user
		db.all("SELECT userid, password FROM users", function(err, rows){
		for(var i=0; i<rows.length; i++){
		      if(rows[i].userid == username & rows[i].password == password) authorized = true;		     
		}
		if(authorized == false){
 	 	   //we had an authorization header by the user:password is not valid
		   response.setHeader('WWW-Authenticate', 'Basic realm="need to login"'); 
           response.writeHead(401, {'Content-Type': 'text/html'});
		   console.log('No authorization found, send 401.'); 
 		   response.end();  
		}
        else
		  next();				
		});
	}

	//notice no call to next()
  
}

function addHeader(request, response){
        // about.html
        var title = 'COMP 2406:';
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.write('<!DOCTYPE html>');
        response.write('<html><head><title>About</title></head>' + '<body>');
        response.write('<h1>' +  title + '</h1>');
		response.write('<hr>');
}

function addFooter(request, response){
 		response.write('<hr>');
		response.write('<h3>' +  'Carleton University' + '</h3>');
		response.write('<h3>' +  'School of Computer Science' + '</h3>');
        response.write('</body></html>');

}

function parseURL(request, response){
	var parseQuery = true; //parseQueryStringIfTrue 
    var slashHost = true; //slashDenoteHostIfTrue 
    var urlObj = url.parse(request.url, parseQuery , slashHost );
    console.log('path:');
    console.log(urlObj.path);
    console.log('query:');	
    console.log(urlObj.query);	
    //for(x in urlObj.query) console.log(x + ': ' + urlObj.query[x]);
	return urlObj;

}

function getSqlCommand(request, response){
	//builds sqlite command to search for ingredients or spices
	var urlObj = parseURL(request, response);		
	var sql = "SELECT * FROM recipes";
	var firstTag = true;
   
	if(urlObj.query['ingredients'] || urlObj.query['spices']) {
		let searchIngredients = "";
		let searchSpices = "";
		sql += " WHERE ";
		
		if(urlObj.query['ingredients']){
			var ingredients = urlObj.query['ingredients'].split(",").map(function(item) {
				return item.trim();
			});
			
			for(let i=0; i<ingredients.length; i++){
				searchIngredients += " (ingredients LIKE '%" + ingredients[i] + "%')";
				if(i != (ingredients.length)-1){
					searchIngredients += " AND ";
				}
			}
			if(!firstTag){sql += " AND ";}
			sql += searchIngredients + "";
			firstTag = false;
		}
		
		if(urlObj.query['spices']){
			var spices = urlObj.query['spices'].split(",").map(function(item) {
				return item.trim();
			});
			
			for(let i=0; i<spices.length; i++){
				searchSpices += "(spices LIKE '%" + spices[i] + "%')";
				if(i != (spices.length)-1){searchSpices += " AND ";}
			}
			
			if(!firstTag){sql += " AND ";}
			sql += searchSpices;
			firstTag = false;
		}
		
		console.log("Finding " + searchIngredients + " and " + searchSpices);
	}
	return sql;
}



exports.users = function(request, response){
	// users.html
	db.all("SELECT userid, password FROM users", function(err, rows){
	   response.render('users', {title : 'Users:', userEntries: rows});
	});
};

exports.recipesData = function(request, response){
	// sends recipes json data to be rendered by client js
	console.log("\n\nRUNNING RECIPESDATA");
	
	let sql = getSqlCommand(request, response);
	console.log(sql);
	
	db.all(sql, function(err, rows){
		if(err) console.log(err);
		for(let i=0; i<rows.length; i++){
			rows[i].recipe_url = "\\recipe\\" + rows[i].id;
			rows[i].image_url = "recipe-default.png"
		}
		//console.log(rows);
		response.contentType('text/html').send(JSON.stringify(rows));
	});
};

exports.find = function (request, response){
	// feeds recipes data to recipes.hbs and sends to client
	console.log("\n\nRUNNING FIND RECIPES");
	
	let sql = getSqlCommand(request, response);
	console.log(sql);
	
	db.all(sql, function(err, rows){
		if(err) console.log(err);
		for(let i=0; i<rows.length; i++){
			rows[i].recipe_url = "\\recipe\\" + rows[i].id;
			rows[i].image_url = "recipe-default.png"
		}
		//console.log(rows);
		response.render('recipes', {title : 'Recipes:', userEntries: rows});
	});
};

exports.recipeDetails = function(request, response){
	// renders specific song
	console.log("\n\nRECIPE DETAILS Request");
	
	var urlObj = parseURL(request, response);
	var recipeID = urlObj.path; //expected form: /song/235
	recipeID = recipeID.substring(recipeID.lastIndexOf("/")+1, recipeID.length);
	
	var sql = "SELECT * FROM recipes WHERE id=" + recipeID;
	console.log("GET RECIPE " + recipeID );
	
	db.all(sql, function(err, rows){
		//console.log(rows);
		response.render('recipeDetails', {title: 'Recipe Details:', recipeEntries: rows});
	});
}


