#include <iostream>

using namespace std;

int main() {
  int total = 0;

  cin >> total;

  int inputs[total];

  for (int i=0; i < total; i++) {
    cin >> inputs[i];
  }

  // sort inputs
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

  // sanity check
  // cout << "sanity check" << endl;
  // for (int i=0; i < total; i++) {
  //   cout << inputs[i] << " " << endl;
  // }


  int temp_stop;
  int sequence = 0;
  for (int i=0; i < total; i++) {
    // cout << "curr: " << inputs[i] << endl;
    if ((i+2) < total && inputs[i] == inputs[i+2] -2) {
      cout << inputs[i] << "-";
      temp_stop = inputs[i+2];
      sequence = 1;
      i += 2;
    } else {
      cout << inputs[i] << " ";
    }
    while (sequence) {
      if ((i+1) < total && inputs[i] == inputs[i+1] -1) {
        temp_stop = inputs[i+1];
        i++;
      } else {
        cout << temp_stop << " ";
        sequence = 0;
      }
    }
  }

  cout << endl;

  return 0;
}
