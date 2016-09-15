bool checar() {
	for (int i = 0; i < 60; i++)
		if (cubeta[i] != actual[i])
			return false;
	return true;
}

int main() {	
	for (int i = 0; i < g; i++) {		
		cubeta[W[i] - 'A']++;
		actual[cad[i] - 'A']++;
	}
	res = cont = 0;
	flag = true;
	for (int i = g; i < s; i++) {		
		if (checar() && flag)
			res++;	
		flag = !(cubeta[ cad[i] - 'A' ] == 0);
		actual[ cad[i] - 'A' ]++;
		actual[ cad[i - g] - 'A' ]--;				
	}
	if (checar())
		res++;
	cout << res << "\n";
}
