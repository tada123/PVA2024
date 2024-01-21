
const fs = require('fs');

function assert(x){
    if(!x){
        throw new Error("Invalid input");
    }
}
function vecSize(vec){
    let res = 0;
    vec.forEach(x => res += (x ** 2));
    return res ** (1/2)
}
function ptToVec(pt1, pt2){
    let l = pt1.length;
    assert(l == pt2.length);
    let res = [];
    res.length = l;
    while(l--){
        res[l] = Math.abs(pt2[l] - pt1[l]);
    }
    return res;
}
function main(file){
    txt = fs.readFileSync(file).toString();
    let lns = txt.split("\n");
    lns.splice(0, 1);
    assert(lns.length >= 2);
    let points = lns.map(x => x.split(" "));
    let v = ptToVec(points[0], points[1]);
    console.log("v: ", v)
    //let hoselen = vecSize(v) //
    // let hoselen = (((vecSize(v) ** 2)) ** (1/2));
    // let hoselen = (((vecSize(v) ** 2)) ** (1/2));
    // let hoselen = (((vecSize(v) ** 2) / 2) ** (1/2));
    let hoselen = (((v[0] + v[2]) ** 2) + (v[1] ** 2)) ** (1/2);
    // let hoselen = ((((v[0] ** 2) + (v[2] ** 2)) ** (1/2)) + (((v[1] ** 2) + (v[2] ** 2)) ** (1/2)))/2;
    let tubelen = 0;
    v.forEach(x => tubelen += x);
    console.log(`Room dimension:
Point #1:
Point #2:
Piping length: ${tubelen}
Hose length: ${hoselen}`)

    
    
}

main(process.argv[2]);


 
