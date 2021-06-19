// calc gcd using Euclid algorithm
function GCD(a, b){
  // base case:
  if(b == 0)
    return a;
  if(a % b == 0)
    return b;

  // base case
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
