cad.erase(remove(cad.begin(), cad.end(), let), cad.end())
transform(cad.begin(), cad.end(), cad.begin(), ::tolower);
