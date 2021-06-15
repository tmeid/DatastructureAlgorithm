def isOperand(x):
  return (x >= 'A' and x <= 'Z') or (x >= 'a' and x <= 'z');

def postfixToInfix(exp):
  stack = []
  for i in exp:
    # if i is operand => push into stack
    if(isOperand(i)):
      stack.append(i)
    # reach the operator => pop 2 times, concat string and push that string into stack
    elif (i == ' '):
      continue
    else:
      operand1 = stack.pop()
      operand2 = stack.pop()
      stack.append('(' + operand2 + i + operand1 + ')')
    
  return stack.pop()

exp = "abcd^e-fgh*+^*+i-"
print(postfixToInfix(exp))



