
const fs = require('fs');

let a = fs.readFileSync(process.argv[2]).toString().split("\n")[0].split(" ").map(x => parseInt(x));
//console.log("a", a);
let ei;
let sums = [];
let pairs = 0;
for(let i = 0; i < a.length; i++){
    let s = a[i];
//    console.log("a[i]", a[i]);
    for(let ei = i + 1; ei < a.length; ei++){
//        console.log("a[ei]: ", a[ei]);
        s += a[ei];
        let idx = sums.indexOf(s);
        if(idx >= 0){
            pairs++;
            sums.splice(idx, 1);
        }else{
//            console.log("Push", s);
            sums.push(s);
        }
    }
//    console.log(`i:${i} l:${a.length}`);
}
console.log(`Posloupnost:\nPocet dvojic: ${pairs}`);


