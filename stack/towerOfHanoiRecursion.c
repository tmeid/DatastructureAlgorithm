#include <stdio.h>

void move(int n, char src, char tmp, char target);
int main(void) {
  int disks = 10;
  char src = 'S';
  char auxiliary = 'A';
  char target = 'T';

  move(disks, src, auxiliary, target);
  return  0;
}
void move(int n, char src, char tmp, char target){
  // base case
  if(n == 1){
    printf("Move disk 1 from %c to %c\n", src, target);
    return;
  }

  // recursive case:
  // move n - 1 disks from src to tmp
  move(n - 1, src, target, tmp);

  // move the biggest disk from src to target
  printf("Move disk %d from %c to %c\n", n, src, target);

  // move n - 1 disk from tmp  to target
  move(n - 1, tmp, src, target);
  return;

}
