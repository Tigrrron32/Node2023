#include "IntList.h"

ostream& operator<<(ostream& out, const IntList& L) {
	int n = L.size();
	if (n == 0) {
		out << "List is empty.";
	}
	else {
		for (int i = 0; i < n; i++) {
			out << L[i] << " ";
		}
	}
	return out;
}