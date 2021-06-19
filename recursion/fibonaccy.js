// fibonaccy using recursion:
function fib(n){
    // base case:
    if(n == 1 || n == 2)
        return 1;
    return fib(n - 2) + fib(n - 1);
}

// memorized fib 
function memorizedFib(num, capture){
    let cap = capture[num];
    if(cap)
        return cap;
    else{
        let res = memorizedFib(num - 2, capture) + memorizedFib(num - 1, capture);
        capture[num] = res;
        return res;
    }
}

console.log(memorizedFib(50, {1: 1, 2: 1}));