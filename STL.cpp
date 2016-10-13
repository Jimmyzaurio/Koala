cad.erase(remove(cad.begin(), cad.end(), let), cad.end())
transform(cad.begin(), cad.end(), cad.begin(), ::tolower);
vec.erase(unique( vec.begin(), vec.end() ), vec.end() );
