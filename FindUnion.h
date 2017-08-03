#include <vector>
#include <algorithm>

using namespace std;

//Find-Union을 이용한 Disjoint Set 표현 클래스
class DisjointSet {
	private:
	vector<int> parent;

	public:
	DisjointSet(int size) {
		parent.resize(size);
		for (int i = 0; i < parent.size(); i++)
			parent[i] = i;
	}

	int Find(int idx) {
		if (parent[idx] == idx) return idx;
		return parent[idx] = Find(parent[idx]);
	}

	bool Union(int v1, int v2) {
		int g1 = Find(v1);
		int g2 = Find(v2);

		if (g1 == g2) {
			return false;
		}

		parent[g1] = g2;
		return true;
	}
};

