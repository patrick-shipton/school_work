

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
				recipe[lastTagName] += data[i].trim().replace(/\,/g, "\,").replace(/\'/g, "''") + " ";
			} 
		}
	}
	//console.log(recipes);
	
	
	// add data to db
	
	var sqlString = "CREATE TABLE IF NOT EXISTS recipes (id TEXT PRIMARY KEY, recipe_name TEXT, contributor TEXT, category TEXT, description TEXT, spices TEXT, source TEXT, rating TEXT, ingredients TEXT, directions TEXT)";
	db.run(sqlString);
	let description = 'Super tasty I love it \n man o man';
	//singleRecipe = `('0','Chicken Soup', '101046328', 'Main Dish', '${description}', 'GingerCumin', 'Patrick Shipton', 'Spicy!!', 'Chicken \nGinger Cumin', 'Just do it')`;
	
	
	recipesStr = "";
	console.log("num Recipes: " + recipes.length);

	for(let i=0; i<recipes.length; i++){
		console.log(i);
		singleRecipe = `('${i}','${recipes[i].recipe_name}', '${recipes[i].contributor}', '${recipes[i].category}', '${recipes[i].description}', '${recipes[i].spices}', '${recipes[i].source}', '${recipes[i].rating}', '${recipes[i].ingredients}', '${recipes[i].directions}')`;
		/*
		singleRecipe = "('"+i+"','"+ 
						recipes[i].recipe_name + "', '" + 
						recipes[i].contributor + "', '" + 
						recipes[i].category + "', '" + 
						recipes[i].description + "', '" + 
						recipes[i].spices + ', ' + 
						recipes[i].source + ', ' + 
						recipes[i].rating + ', ' +
						recipes[i].ingredients + ', ' + 
						recipes[i].directions + "')";
		*/
		//singleRecipe = singleRecipe.replace("'", "\'");
		//singleRecipe = singleRecipe.replace(",", "\,");
		
		//console.log(singleRecipe.split(","));
		console.log(singleRecipe);
		sqlString = "INSERT OR REPLACE INTO recipes VALUES " + singleRecipe ;
		console.log("\n\n" + sqlString.substr(sqlString.indexOf("s")-10, 25));
		db.run(sqlString);
		//recipesStr += `("${i}","${recipes[i].recipe_name}","${recipes[i].contributor}","${recipes[i].category}","${recipes[i].description}","${recipes[i].spices}","${recipes[i].source}","${recipes[i].rating}","${recipes[i].ingredients}","${recipes[i].directions}"),`;
	}
	recipesStr = recipesStr.substring(0, (recipesStr.length-1));
	
	//console.log(recipesStr.substr(recipesStr.indexOf("low")-20, 150));
	//sqlString = "INSERT OR REPLACE INTO recipes VALUES " + recipesStr;
	//db.run(sqlString);
	
});