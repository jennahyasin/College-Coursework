document.querySelector("#Form").addEventListener("submit", function (event) {
    validateForm(event);
});

document.querySelector("#genImage").addEventListener("click", generateUserIcon);

generateUserIcon();

async function generateUserIcon() {
    let userIcon = document.querySelector("#profileIcon");

    let url = `https://api.unsplash.com/photos/random/?client_id=7756a1e81f817c186cf57294e1c19b37b49c54b8f34e7c499ee0ce5cd86cd16e&featured=true&query=profile`;
    let response = await fetch(url);
    let data = await response.json();
    let imgUrl = data.urls.small;

    userIcon.src = imgUrl;
    document.querySelector("#profilePic").value = imgUrl;
}

function validateForm(e) {


    let password = document.querySelector("#password").value;
    console.log("password", password);

    let password2 = document.querySelector("#password2").value;
    console.log("password2", password2);
    
    let isValid = true;
     if (password.length < 6) {
        document.querySelector("#passwordError").innerHTML = "Password must be at least 6 characters!";
        document.querySelector("#passwordError").style.color = "red";
        isValid = false;
    }
    else if (password != password2) {
        document.querySelector("#passwordError2").innerHTML = "Passwords do not match!";
        document.querySelector("#passwordError2").style.color = "red";
        isValid = false;
    }
    if (!isValid) {
        e.preventDefault();
    }
}