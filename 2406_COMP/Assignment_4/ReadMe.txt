ReadMe.txt for COMP 2406 Assignment 4

Develper: Patrick Shipton 101046238
Develped on: Windows 7 and Chrome
Start Date: 05/12/2017
Last edit: 09/12/2017


To run server:
	1. Go to the directpry containing the package.json and the food2fork_server.js
	2. Run 'npm install'
	Optional. Run 'npm run-script update_db' to parse the recipes xml and update sql db_recipes
	3. Run 'npm start'
	
To exit server:
	1. Use Ctrl+C 
	2. enter 'y' to close server

To Login:
	Use (user: ldnel password: secret)
	
How to use app:
	1. go to 'http://localhost:3000' or 'http://localhost:3000/recipes'
	2. type ingredient(s) and/or spices() into input box(es)
	3. click the 'Search' button
	4. The images of the recipes are links to the the recipe details
	
	Or
	
	1. go to 'http://localhost:3000/recipes?ingredient=${ingredient}&spices=${spices}'
		ex: 'http://localhost:3000/recipes?ingredient=ginger,cocoa&spices=cumin'
	
Note: 
	1. Requirement R1.8) of the assignment is only done when '/' or '/recipes' routes are used with the use of the search button
	2. The '/recipes' route defaults to show all recipes (to browse the recipes if no ingredients come to mind)