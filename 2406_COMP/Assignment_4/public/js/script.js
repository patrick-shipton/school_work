/* 
To be run by the client:
Fetches json data from server and renders data
*/
function getRecipes() {

    let ingredientName = document.getElementById('ingredient').value
    
	
	let spiceName = document.getElementById('spice').value
    if((spiceName === '') && (ingredientName === '')) {
        return;
    }

    let cityDiv = document.getElementById('ingredientRecipes')
    cityDiv.innerHTML = '';

    let xhr = new XMLHttpRequest();
    xhr.onreadystatechange = () => {
        if (xhr.readyState == 4 && xhr.status == 200) {
            let response = JSON.parse(xhr.responseText);
			console.log(response);
			for(let i=0; i<response.length; i++){
				let recipe = response[i];
				
				cityDiv.innerHTML = cityDiv.innerHTML + `
				<div class='recipe'>
					<div class='recipe-photo'>
						<a href="${recipe.recipe_url}" target="_blank">
							<img src="${recipe.image_url}">
						</a>
					</div>
					<h2>${recipe.recipe_name}</h2>
				</div>
				`
			}
        }
    }
    xhr.open('POST', `/recipes?ingredients=${ingredientName}&spices=${spiceName}`, true);
    xhr.send()
}

//Attach Enter-key Handler
const ENTER=13
document.getElementById("ingredient")
    .addEventListener("keyup", function(event) {
    event.preventDefault();
    if (event.keyCode === ENTER) {
        document.getElementById("submit").click();
    }
});

document.getElementById("spice")
    .addEventListener("keyup", function(event) {
    event.preventDefault();
    if (event.keyCode === ENTER) {
        document.getElementById("submit").click();
    }
});


var ready = () => {
	getRecipes();
};

if ((document.readyState === "complete") || (document.readyState !== "loading" && !document.documentElement.doScroll)) {
	ready();
} else {
	document.addEventListener("DOMContentLoaded", ready);
}