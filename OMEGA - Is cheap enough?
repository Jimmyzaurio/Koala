#define MAX 100007
struct coche {
	string nombre;
	int low, hig;
};

#define mapeo(n) distance(V.begin(), lower_bound(V.begin(), V.end(), n))

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {		
		cin >> cad >> low >> hig;
		C.push_back({cad, low, hig + 1});
		V.push_back(low);
		V.push_back(hig + 1);
	}

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> aux;
		queries.push_back(aux);
		V.push_back(aux);
	}

	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());

	FenTree varo = FenTree(V.size());	
	FenTree idx = FenTree(V.size());
	int count = 1;
	for (auto var : C) {
		varo.Actualizar(mapeo(var.low) + 1, 1);
		varo.Actualizar(mapeo(var.hig) + 1, -1);
		idx.Actualizar(mapeo(var.low) + 1, count);
		idx.Actualizar(mapeo(var.hig) + 1, -count);
		count++;
	}
	
	for (auto q : queries) {
		aux = varo.Query(mapeo(q) + 1);
		if (aux == 0)
			cout << "NONE\n";
		else if (aux > 1)
			cout << "MULTIPLE\n";
		else {
			cout << C[idx.Query(mapeo(q) + 1) - 1].nombre << "\n";
		}
	}
}
