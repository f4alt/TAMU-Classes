// #include <iostream>
// using namespace std;
// int main()
// {
// int n_A, n_B, reverse=0, rem;
//
//
// cin>>n_A << n_B;
//   while(n_A!=0)
//   {
//      rem=n_A%10;
//      reverse=reverse*10+rem;
//      n_A/=10;
//   }
//  cout<<"Reversed Number: "<<reverse<<endl;
// return 0;
// }


#include <iostream>

using namespace std;

int main() {
  int in_A, in_B;
  int larger;
  int reversed_A=0, reversed_B=0;
  int remainder;

  cin >> in_A;
  cin >> in_B;

  for (int i=0; i < 3; i++) {
      remainder = in_A%10;
      reversed_A = reversed_A*10 + remainder;
      in_A /= 10;
  }

  for (int i=0; i < 3; i++) {
      remainder = in_B%10;
      reversed_B = reversed_B*10 + remainder;
      in_B /= 10;
  }

  if ((reversed_A) > (reversed_B)) {
    larger = (reversed_A);
  } else {
    larger = (reversed_B);
  }

  cout << larger;
}
