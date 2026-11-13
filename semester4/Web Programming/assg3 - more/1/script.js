//  Write a HTML page which contains two lists (each with more then one line - use <select> tag). 
//     Double click event on an element from the first list will move this element into the 
//     second one, and reverse. 

function moveMiauToHam(){
    let listA = document.getElementById("1");
    let listB = document.getElementById("2");
    let selectedOption = listA.options[listA.selectedIndex];
    listB.appendChild(selectedOption);
}

function moveHamToMiau(){
    let listA = document.getElementById("1");
    let listB = document.getElementById("2");
    let selectedOption = listB.options[listB.selectedIndex];
    listA.appendChild(selectedOption);
}