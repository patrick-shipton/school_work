

const sqlite3 = require('sqlite3').verbose(); //verbose provides more detailed stack trace
const db = new sqlite3.Database('data/db_recipes');
const fs = require('fs');


let filePath = __dirname + '\\aLaCarteData_rev3.xml';
console.log(filePath);

fs.readFile(filePath, 'utf8', function(err,data){
	if(err){
		//report error to console
		console.log('ERROR: ' + JSON.stringify(err));
		return;
	}
	
	//turn data into an obj
	data = data.split(/\r\n|\n/g);
	let recipes = [];
	let recipe = {};
	let lastTagName = "";
	let currentTag = [];
	let ignoreArr = ["recipe", "/recipe", "recipes_xml", "/recipes_xml"];
	for(let i=0; i<data.length; i++){
		if((currentTag = data[i].trim().match(/\<\S+\>/g))){
			lastTagName = currentTag[0].replace(/\<|\>/g, "");
			
			if(lastTagName == "recipe"){
				recipe = {};
			}
			else if(lastTagName == "/recipe"){
				recipes.push(recipe);
			} else if(! lastTagName.startsWith("/")){
				recipe[lastTagName] = "";
			}
			//console.log(lastTagName);
		} else {
			if(!ignoreArr.includes(lastTagName)){
				//console.log("'"+data[i].trim()+"'");
				recipe[lastTagName] += data[i].trim();
			}
		}
	}
	//console.log(recipes);
	
	
	// add data to db
	
	var sqlString = "CREATE TABLE IF NOT EXISTS recipes (id TEXT PRIMARY KEY, recipe_name TEXT, contributor TEXT, category TEXT, description TEXT, spices TEXT, source TEXT, rating TEXT, ingredients TEXT, directions TEXT)";
	db.run(sqlString);
	
	recipesStr = "";
	for(let i=0; i<recipes.length; i++){
		recipesStr += `("${i}","${recipes[i].recipe_name}","${recipes[i].contributor}","${recipes[i].category}","${recipes[i].description}","${recipes[i].spices}","${recipes[i].rating}","${recipes[i].ingredients}","${recipes[i].directions}"),`;
	}
	recipesStr = recipesStr.substring(0, (recipesStr.length-1));
	
	console.log(recipesStr.substring(recipesStr.indexOf("low") -10, 100));
	sqlString = "INSERT OR REPLACE INTO recipes VALUES " + recipesStr;
	db.run(sqlString);
 
});