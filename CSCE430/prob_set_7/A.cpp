#include <bits/stdc++.h>

using namespace std;

// int num_ascend, num_decend;
// vector<pair<double, double> > ascend, descend;

double margin = .000000001;

// double find_max(double mid, int bound) {
//   double ret = 0.0;
//   for (int i=0; i < bound; i++) {
//     ret = max(ret,
//       (ascend.first[i] - mid)*(ascend[i] - mid)
//       + descend[i] * descend[i]);
//     // ret = max(ret,
//   }
//
//   return ret;
// }

int main() {
  int n, m;

  while (cin >> n >> m) {
      vector<pair<double, double> > ascend, descend;

      int h, t;
      double high = 0.0;
      double low = 0.00000001;

      double total_h = 0.0;

      for (int i = 0; i < n; i++) {
          cin >> h >> t;
          ascend.push_back(make_pair(h, t));
          high += t;
          total_h += h;
      }

      for (int i = 0; i < m; i++) {
          cin >> h >> t;
          descend.push_back(make_pair(h, t));
      }

      while (fabs(low - high) > margin) {
          double mid = (low + high) / 2.0;

          double mid_cop = mid;

          double up_h = 0.0;
          double down_h = total_h;

          for (int i = 0; i < n; i++) {
              up_h += min(1.0, mid / ascend[i].second) * ascend[i].first;
              mid -= ascend[i].second;
              if (mid <= 0) break;
          }

          for (int i = 0; i < m; i++) {
              down_h -= min(1.0, mid_cop / descend[i].second) * descend[i].first;
              mid_cop -= descend[i].second;
              if (mid_cop <= 0) break;
          }

          if (up_h < down_h) {
              low = (low + high) / 2.0;
          } else {
              high = (low + high) / 2.0;
          }
      }

      printf("%.6f\n", high);
  }

  return 0;
}

// int main() {
//     double inc = 0, ans = 0;
//
//     cin >> num_ascend >> num_decend;
//
//     int height, time;
//     double total_h = 0;
//
//     for (int i = 0; i < num_ascend; i++) {
//         cin >> height >> time;
//
//         ascend.push_back(make_pair(height, time));
//         ans += time;
//         total_h += height;
//     }
//
//     for (int i = 0; i < num_decend; i++) {
//         cin >> height >> time;
//         descend.push_back(make_pair(height,time));
//     }
//
//     double l, r, mid, rightmid, maxl, maxr;
//     l = 0, r = 1000;
//     while (fabs(l - r) > margin) {
//         mid = (l + r) / 2;
//         rightmid = (mid + r) / 2;
//
//         maxl = find_max(mid, num_ascend);
//         maxr = find_max(rightmid, num_ascend);
//
//         if (maxl < maxr) {
//           r = rightmid;
//         } else {
//           l = mid;
//         }
//       }
//
//       printf("%.6f\n", mid);
//
//     // }
//         // double mid = (inc + ans) / 2.0;
//         // // cout << mid << endl;
//         //
//         // double mid_cmp = mid;
//         //
//         // double up_h = 0.0;
//         // double down_h = total_h;
//         //
//         // // cout << up_h << " | " << down_h << endl;
//         //
//         // for (int i = 0; i < num_decend; i++) {
//         //     up_h += min(1.0, mid / ascend[i].second) * ascend[i].first;
//         //     mid -= ascend[i].second;
//         //     if (mid <= 0) break;
//         // }
//         // // cout << up_h << " | " << mid << endl;
//         //
//         // for (int i = 0; i < num_ascend; i++) {
//         //     down_h -= min(1.0, mid_cmp / descend[i].second) * descend[i].first;
//         //     mid_cmp -= descend[i].second;
//         //     if (mid_cmp <= 0) break;
//         // }
//         // // cout << down_h << " | " << mid_cmp << endl;
//         //
//         // if (up_h < down_h) {
//         //     inc = (inc + ans) / 2.0;
//         // } else {
//         //     ans = (inc + ans) / 2.0;
//         // }
//     // }
//     //
//     // printf("%.6f\n", ans);
//
//     return 0;
// }
