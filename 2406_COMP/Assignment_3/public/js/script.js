function getRecipes() {

    let ingredientName = document.getElementById('ingredient').value
    if(ingredientName === '') {
        return;
    }

    let cityDiv = document.getElementById('ingredientRecipes')
    cityDiv.innerHTML = ''

    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = () => {
        if (xhr.readyState == 4 && xhr.status == 200) {
            let response = JSON.parse(xhr.responseText);
			console.log(response);
			for(let i=0; i<response.count; i++){
				let recipe = response.recipes[i];
				
				cityDiv.innerHTML = cityDiv.innerHTML + `
				<div class='recipe'>
					<div class='recipe-photo'>
						<a href="${recipe.f2f_url}" target="_blank">
							<img src="${recipe.image_url}">
						</a>
					</div>
					<h2>${recipe.title}</h2>
				</div>
				`
			}
        }
    }
    xhr.open('POST', `/recipes?ingredient=${ingredientName}`, true);
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


var ready = () => {
	getRecipes();
};

if ((document.readyState === "complete") || (document.readyState !== "loading" && !document.documentElement.doScroll)) {
	ready();
} else {
	document.addEventListener("DOMContentLoaded", ready);
}