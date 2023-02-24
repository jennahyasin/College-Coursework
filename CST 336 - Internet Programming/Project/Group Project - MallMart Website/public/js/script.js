
var tempCart = localStorage.getItem("cartCount");
var userCart = localStorage.getItem("cart");

let cartNum = document.querySelector("#cartNumber");
cartNum.style.visibility = "hidden";

let itemLinks = document.querySelectorAll(".onlyProduct");

for (itemLinks of itemLinks) {
    itemLinks.addEventListener("click", getItemInfo);
}

let itemLink2 = document.querySelectorAll(".onlyProduct");
for (itemLink2 of itemLink2) {
    itemLink2.addEventListener("click", getItemInfo2);
}

let cartBtn = document.querySelectorAll(".cartBtn");
for (cartBtn of cartBtn) {
    cartBtn.addEventListener("click", addToCart);
}

let checkoutLink = document.querySelectorAll(".checkoutOnly");
for (checkoutLink of checkoutLink) {
    checkoutLink.addEventListener("click", getCheckoutInfo);
}

updateCartNumber();
let subtotal = 0;

updateCartDisplay();


document.querySelector("#emptyCart").addEventListener("click", emptyCart);

function emptyCart() {
    localStorage.setItem("cartCount", 0);
    localStorage.removeItem("cart");
    userCart = [];
    updateCartNumber();
    updateCartDisplay();
    location.reload();
}


document.querySelector("#shipping").addEventListener("change", updateShipping);
async function updateCartDisplay() {
    let finalCart = userCart.split(" ");
    finalCart.splice(0, 1);
    console.log(`FinalCart: ${finalCart}`);

    let cartDisplay = document.querySelector("#cartDisplayArea");
    cartDisplay.innerHTML =
        `<div class="cartRow">
    <table>`;

    let cartBuilder = Array.from(new Set(finalCart));

    // int array
    const arrOfNum = cartBuilder.map(str => { return Number(str); });
    const cartArray = new Array(Math.max(...arrOfNum)).fill(0);
    for (let x = 0; x < finalCart.length; x++) {
        cartArray[finalCart[x] - 1] += 1
    };

    for (i in cartBuilder) {
        let url = `/api/item/${cartBuilder[i]}`;
        let response = await fetch(url);
        let rows = await response.json();
        let totalPrice = (rows[0].price * cartArray[rows[0].itemId - 1]);
        let subTotal = subtotal + totalPrice;
        console.log("subTotal " + subTotal);

        cartDisplay.innerHTML +=
            `
        <div id="cartItems">
          <img src="/img/products/${rows[0].imgName}" height="100px">
          <label class="cartText"> ${rows[0].name} </label>
          <label class="cartText">QTY: <strong> ${cartArray[rows[0].itemId - 1]} </strong> </label>
          <label class="cartText">Item Price: ${rows[0].price} </label>
          <label class="cartText">Total Price: $${totalPrice}.00 </label>
        </div>
        `;

        subtotal = subTotal; //
    }
    cartDisplay.innerHTML += `
        </table>
    </div>`;

    updateShipping();
}

function updateShipping() {
    let shipping = document.querySelector("#shipping").value;
    // use tempSub so we don't modify subtotal
    let tempSub = Number(subtotal);
    tempSub = Number(shipping) + tempSub;
    let tax = Number(tempSub) * 0.1;
    let total = tempSub + Number(tax);

    // toFixed rounds our decimal fields for proper display
    tax = tax.toFixed(2);
    total = total.toFixed(2);
    // Finally update all of our values w/ proper data.
    document.querySelector("#subtotalText").innerHTML = `${tempSub}`;
    document.querySelector("#taxText").innerHTML = `${tax}`;
    document.querySelector("#shippingText").innerHTML = `${shipping}`;
    document.querySelector("#totalText").innerHTML = `${total}`;
}

// Home Page Modal Function
async function getItemInfo() {
    var myModal = new bootstrap.Modal(document.getElementById('itemModal'));
    myModal.show();
    let url = `/api/item/${this.id}`;
    let response = await fetch(url);
    let data = await response.json();

    let temp = (data[0].category);
    let cat = temp.charAt(0).toUpperCase() + temp.slice(1);

    let itemInfo = document.querySelector("#itemInfo");
    itemInfo.innerHTML = `<h3> ${data[0].name} </h3>`;
    itemInfo.innerHTML += `<img src="/img/products/${data[0].imgName}" width="200"><br><br>`;
    itemInfo.innerHTML += `<h4><strong>Price: </strong> $${data[0].price}</h4>`;
    itemInfo.innerHTML += `<h5><strong>Category: </strong>  ${cat}</h5>`;
    itemInfo.innerHTML += `<h6> <strong>Description</strong>:  ${data[0].description}</h6>`;
    itemInfo.innerHTML += `<h5><strong>Availability: </strong>  ${data[0].availability}</h5>`;
    itemInfo.innerHTML += `<input type="hidden" class="selectedItemId" value="${data[0].itemId}">`
}

// Product Page Modal Function
async function getItemInfo2() {
    var myModal = new bootstrap.Modal(document.getElementById('itemModal2'));
    myModal.show();
    let url = `/api/item/${this.id}`;
    let response = await fetch(url);
    let data = await response.json();

    let temp = (data[0].category);
    let cat = temp.charAt(0).toUpperCase() + temp.slice(1);

    let itemInfo = document.querySelector("#itemInfo2");
    itemInfo.innerHTML = `<h3> ${data[0].name} </h3>`;
    itemInfo.innerHTML += `<img src="/img/products/${data[0].imgName}" width="200"><br><br>`;
    itemInfo.innerHTML += `<h4><strong>Price: </strong> $${data[0].price}</h4>`;
    itemInfo.innerHTML += `<h5><strong>Category: </strong>  ${cat}</h5>`;
    itemInfo.innerHTML += `<h6> <strong>Description</strong>:  ${data[0].description}</h6>`;
    itemInfo.innerHTML += `<h5><strong>Availability: </strong>  ${data[0].availability}</h5>`;
    itemInfo.innerHTML += `<input type="hidden" class="selectedItemId" value="${data[0].itemId}">`
}

// Cart Pages Checkout Modal Function
function getCheckoutInfo() {
    var myModal = new bootstrap.Modal(document.getElementById('checkoutModal'));
    myModal.show();

    let checkoutInfo = document.querySelector("#checkoutInfo");
    let shipping = Number(document.querySelector("#shipping").value);
    let subtotal = Number(document.querySelector("#subtotalText").textContent);
    let tax = Number(document.querySelector("#taxText").textContent);
    let total = Number(document.querySelector("#totalText").textContent);

    // Update the Modal's text
    checkoutInfo.innerHTML = `
    <h3> Shipping: $${shipping} </h3>
    <h2> Subtotal: $${subtotal} </h2>
    <h3> Tax: $${tax} </h3>
    <h2> Total: $${total} </h2>`;

    // Update the Hidden fields data, to be sent to the POSTed /purchase route
    document.querySelector("#modalTotal").value = total;
    document.querySelector("#modalTax").value = tax;
    document.querySelector("#modalShipping").value = shipping;
    document.querySelector("#modalSubtotal").value = subtotal;
}

// General Function to add items to the localStorage cart
function addToCart() {
    ++tempCart; // increments cart item count
    let addedItemId = document.querySelector(".selectedItemId").value;

    userCart += ` ${addedItemId}`;

    localStorage.setItem("cart", userCart);

    localStorage.setItem("cartCount", tempCart);
    updateCartNumber();
}

// updateCartNumber: Deals exclusively with displaying and updating 
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

