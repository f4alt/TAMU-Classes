#include <iostream>

using namespace std;

int main() {
  int total = 0;

  cin >> total;

  int inputs[total];

  for (int i=0; i < total; i++) {
    cin >> inputs[i];
  }

  for(int i=0;i<total;i++)
	{
		for(int j=i+1;j<total;j++)
		{
			if(inputs[i]>inputs[j])
			{
				int temp  =inputs[i];
				inputs[i]=inputs[j];
				inputs[j]=temp;
			}
		}
	}

  int length =0;
  int real = inputs[0];
  for (int i=0; i < total; i++) {
    for (int j=0; j<total; j++) {

      // cout << "test:" << inputs[i] << " | " << inputs[i] +1 << endl;
      if (inputs[i] == (inputs[j] -1)) {
        // cout << "length++" << endl;
        length ++;
      } else {
        if (length > 0) {
          cout << real << "-" << real+length << " ";
        } else {
          cout << real << " ";
          real = inputs[i+1];
          length = 0;
        }


      }
    }
  }


  // for (int i=0; i<total; i++) {
  //   if (inputs[i] == 0) {
  //     length++;
  //   } else {
  //     if (length > 0) {
  //       cout << real << "-" << real+length << " ";
  //     } else {
  //       cout << real;
  //     }
  //     real = inputs[i];
  //   }
  // }

  return 1;
}
