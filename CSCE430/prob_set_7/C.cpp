#include <bits/stdc++.h>

using namespace std;

double X[200001], Y[200001];
int num_houses;
double margin = .000000001;

double find_max(double mid) {
	double ret = 0.0;
	for(int i = 0; i < num_houses; i++)
		ret = max(ret, (X[i] - mid)*(X[i] - mid) + Y[i] * Y[i]);
	return ret;
}

int main() {
  // int num_houses;

  cin >> num_houses;
  while (num_houses > 0) {
  //   cout << num_houses << endl;
    // for (int i=0; i < num_houses; i++) {
  		for(int i = 0; i < num_houses; i++) {
        cin >> X[i] >> Y[i];
      }
  		double l, r, mid, rightmid, maxl, maxr;
  		l = -200000, r = 200000;

  		while(fabs(l - r) > margin) {
        // cout << "l | r:" << l << " | " << r << endl;
  			mid = (l + r)/2;
  			rightmid = (mid + r)/2;

        // cout << "mid:" << mid << endl;
        // cout << "rightmid:" << rightmid << endl;

  			maxl = find_max(mid);
  			maxr = find_max(rightmid);

        // cout << "maxl:" << maxl << endl;
        // cout << "maxr:" << maxr << endl;

  			if (maxl < maxr) {
  				r = rightmid;
        }
  			else {
  				l = mid;
        }
  		}
  		printf("%.9lf %.9lf\n", mid, sqrt(maxl));
  	// }

    cin >> num_houses;
  }
	return 0;
}
