
const fs = require('fs');

function palidrome(num, radix){
    let str;
    while((str = num.toString(num, radix)) != str.reverse()){
        num++;
    }
}


