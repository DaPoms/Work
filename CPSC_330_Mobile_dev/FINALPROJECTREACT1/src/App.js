import * as React from "react";

function formatCurrency(value) {
  return "$" + value.toFixed(2);
}

const price = 
{
  CHICKEN_PRICE: 10.95,
  HALIBUT_PRICE: 13.95,
  BURGER_PRICE: 9.95,
  SALMON_PRICE: 18.95,
  SALAD_PRICE:7.95,
  SALES_TAX:0.07
}




//function 

function App() 
{
  const[items, setSelected] = React.useState({chicken:false, halibut:false, burger:false, salmon:false, salad:false});
  //const [cost, setCost] = React.useState(0);


/* function changeTotal()
{
  setCost cost() (items.chicken * price.CHICKEN_PRICE) + (items.halibut * price.HALIBUT_PRICE) + 
  (items.burger * price.BURGER_PRICE) + (items.salmon * price.SALMON_PRICE) + (items.salad * price.SALAD_PRICE);
  tax = cost * price.SALES_TAX; 
  totalCost = cost + tax;
} */
function handleClick(event)
{
  let item = event.target.id;
  // I learned of the ... format to just say to retain all the values of states that are not specified explicitly
  setSelected({...items, [item]:!items[item]}); // Sets whether element is checked or not (I named the items the same as the button id's to allow easy access)
} 

  let cost = (items.chicken * price.CHICKEN_PRICE) + (items.halibut * price.HALIBUT_PRICE) + 
  (items.burger * price.BURGER_PRICE) + (items.salmon * price.SALMON_PRICE) + (items.salad * price.SALAD_PRICE);
  let tax = cost * price.SALES_TAX; 
  let totalCost = cost + tax;

  return (<>
      <header>
          <h1>
            Hands-on Project 1
          </h1>
      </header>

      <article>
          <h2>Lunch selections</h2>
          <form>
            <input onChange={handleClick} type="checkbox" id="chicken" value="10.95" />
            <label  for="chicken">Fried chicken ($10.95)</label>
            <input onChange={handleClick} type="checkbox" id="halibut" value="13.95" />
            <label for="halibut">Fried halibut ($13.95)</label>
            <input onChange={handleClick} type="checkbox" id="burger" value="9.95" />
            <label for="burger">Hamburger ($9.95)</label>
            <input onChange={handleClick} type="checkbox" id="salmon" value="18.95" />
            <label for="salmon">Grilled salmon ($18.95)</label>
            <input onChange={handleClick} type="checkbox" id="salad" value="7.95" />
            <label for="salad">Side salad ($7.95)</label>
          </form>
      </article>
      <aside>
          <span id="totalLab">Total Cost of Items</span>
          <span id="foodTotal">{formatCurrency(cost)}</span>
          <span id="taxLab">Tax</span>
          <span id="foodTax">{formatCurrency(tax)}</span>
          <span id="billLab">TOTAL</span>
          <span id="totalBill">{formatCurrency(totalCost)}</span>       
          
      </aside>
  </>
  )
}
export default App;
