// calc gcd using Euclid algorithm
function GCD(a, b){
  // base case:
  if(b == 0)
    return a;
  if(a % b == 0)
    return b;

  // recursive case
  // b always less than a,
  // if not: (b, a % b) will swap a, b (a % b = a) ==> recursion later we will have b < a
  return GCD(b, a % b);
}


// iterative approach:
function iterativeGCD(a, b){
  if( b == 0 || a == 0)
    return a + b;
  if(a % b == 0)
    return b;

  while(a * b != 0){
    let tmp = a;
    a = b;
    b = tmp % b;
  }

  return a;
}
