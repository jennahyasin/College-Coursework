emptyCart();

function emptyCart() {
    console.log("EMPTIED CART");
    localStorage.setItem("cartCount", 0);
    localStorage.removeItem("cart");
    // userCart = [];
    updateCartNumber();
}

function updateCartNumber() {
    // Grab localStorage value & the obj of the cart num
    let cartVal = localStorage.getItem("cartCount");
    let cartNum = document.querySelector("#cartNumber");
    // Show/Update or Hide depending on value
    if (cartVal > 0) {
        cartNum.style.visibility = "visible";
        cartNum.innerHTML = cartVal;
    } else {
        cartNum.style.visibility = "hidden";
    }
}