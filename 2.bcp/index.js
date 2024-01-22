
const fs = require('fs');

function assert(x){
    if(!x){
        throw "Assertion failed";
    }
}
function parsePoint(pstr){
    let sp = pstr.split(" ");
    let res = [];
    for(let i in sp){
        let t = sp[i].trim();
        if(t.length == 0){
            continue;
        }
        res.push(parseFloat(t));
    }
    return res;
}
function pt2vec(p, p1){
    let l = p.length;
    let res = [];
    res.length = l;
    while(l--){
        console.log(`l:${l}`);
        let dim = p1[l];
        res[l] = [];
        while(dim--){
            res[l][dim] = p1[l][dim] - p[l][dim];
        }
    }
    return res;
}
function vecSize(vec){
    let x = 0;
    vec.forEach(e => x += e);
    return x;
}
function main(args){
    for(i in args){
        let lns = fs.readFileSync(args[i], "utf-8").split("\n");
        assert(lns.length > 2);
        let points = [parsePoint(lns[0]), parsePoint(lns[1]), parsePoint(lns[2])];
        if((points[0] == points[1]) || (points[1] == points[2]) || (points[0] == points[2])){
            console.log("dva nebo všechny tři zadané body splývají");
        }else if((vecSize(pt2vec(points[0], points[1])) * vecSize(pt2vec(points[1], points[2]))) == 0){
            console.log("Body lezi na jedne primce");
        }else{
            console.log("Body nelezi na jedne primce");
        }        
    }
}
let args = process.argv;
args.splice(0, 2);
main(args);
