/************************************************************/
/* Author:   Daniel Tripoli                                 */
/* Major:    Computer Science                               */
/* Creation  Date: February 22, 2026                        */
/* Due Date: February 27, 2026                              */
/* Course:   CPSC 330 010                                   */
/* Professor Name: Jianfeng Wang                            */
/* Project: #1                                              */
/* Filename: project1.js                                    */
/* Purpose: Application to calculate the cost of a          */ 
/*          restaurant order plus tax                       */
/*                                                          */
/************************************************************/
let CHICKEN_PRICE = 10.95;
let HALIBUT_PRICE = 13.95;
let BURGER_PRICE = 9.95; 
let SALMON_PRICE = 18.95;
let SALAD_PRICE = 7.95;
let SALES_TAX = 0.07;


// Function to display a numeric value as a text string in the format $##.## 
function formatCurrency(value) {
  return "$" + value.toFixed(2);
}

document.getElementById("chicken").onchange = calcTotal;
document.getElementById("halibut").onchange = calcTotal;
document.getElementById("burger").onchange = calcTotal;
document.getElementById("salmon").onchange = calcTotal;
document.getElementById("salad").onchange = calcTotal;


function calcTotal()
{
  let cost = 0;
  let buyChicken = document.getElementById("chicken").checked;
  let buyHalibut = document.getElementById("halibut").checked;
  let buyBurger = document.getElementById("burger").checked;
  let buySalmon = document.getElementById("salmon").checked;
  let buySalad = document.getElementById("salad").checked;
  cost = (buyChicken * CHICKEN_PRICE) + (buyHalibut * HALIBUT_PRICE) + (buyBurger * BURGER_PRICE) + (buySalmon * SALMON_PRICE) + (buySalad * SALAD_PRICE);
  document.getElementById("foodTotal").innerHTML = formatCurrency(cost);

  let tax = cost * SALES_TAX;
  document.getElementById("foodTax").innerHTML = formatCurrency(tax);

  let totalCost = tax + cost;
  document.getElementById("totalBill").innerHTML = formatCurrency(totalCost);

}
