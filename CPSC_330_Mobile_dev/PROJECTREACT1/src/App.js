import * as React from "react";

const salesTax = 0.07;

function App() 
{
  const [subTotal, setSubTotal] = React.useState(0);
  const [tax, setTax] = React.useState(0);
  const [total, setTotal] = React.useState(0);


  function handleChange(e)
  {
    let calcSubTotal = changeSubTotal(e);
    let calcTax = changeTax(calcSubTotal);
    handleTotal(calcSubTotal, calcTax);
  }

  function changeSubTotal(e)
  {
    let price = parseFloat(e.target.value);
    let calcSubTotal = subTotal  + (e.target.checked ? price : -price);
    setSubTotal(calcSubTotal);
    return calcSubTotal;
  }

  function changeTax(calcSubTotal)
  {
    let calcTax = calcSubTotal * salesTax;
    setTax(calcTax)
    return calcTax;
  }

  function handleTotal(calcSubTotal, calcTax)
  {
    let total = calcSubTotal + calcTax;
    setTotal(total);
  }
  
  return (<>
      <header>
          <h1>
            Hands-on Project 1
          </h1>
      </header>

      <article>
          <h2>Lunch selections</h2>
          <form>     
            <input onChange={(e) => handleChange(e)} type="checkbox" value= "10.95" id="chicken" />
            <label  for="chicken">Fried chicken ($10.95)</label>
            <input onChange={((e) => handleChange(e))} type="checkbox" value= "13.95" id="halibut"  />
            <label for="halibut">Fried halibut ($13.95)</label>
            <input onChange={(e) => handleChange(e)} type="checkbox" value= "9.95" id="burger"   />
            <label for="burger">Hamburger ($9.95)</label>
            <input onChange={(e) => handleChange(e)} type="checkbox" value= "18.95" id="salmon"   />
            <label for="salmon">Grilled salmon ($18.95)</label>
            <input onChange={(e) => handleChange(e)} type="checkbox" value= "7.95" id="salad"    />
            <label for="salad">Side salad ($7.95)</label>
          </form>
      </article>
      <aside>
          <span id="totalLab">Total Cost of Items</span>
          <span id="foodTotal">{"$" + subTotal.toFixed(2)}</span>
          <span id="taxLab">Tax</span>
          <span id="foodTax">{"$" + tax.toFixed(2)}</span>
          <span id="billLab">TOTAL</span>
          <span id="totalBill">{"$" + total.toFixed(2)}</span>       
          
      </aside>
  </>
  )
}
export default App;
// Use checked state of e.target.checked 
// Make 3 separate functions, one for tax, bill, total (call back function)
