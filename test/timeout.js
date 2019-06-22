var timeout = setTimeout(function(){
    console.log("((((((((((((((((((((((((((((((((((");
}, 250);

console.log("Timer " + timeout + " will not be executed");
clearTimeout(timeout);
var index = 0;

function test() {
    setTimeout(function(){
        console.log("iter");
        if(index < 100){
            test();
        }
        index++;
    },10);
}

test();