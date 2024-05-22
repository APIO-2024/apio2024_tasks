#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

#define IS_ENCODE_MAGIC(x) (strcmp(x, "1") == 0 || strcmp(x, "3") == 0 || strcmp(x, "5") == 0 || strcmp(x, "7") == 0) 
#define ENCODE_OUTPUT_MAGIC "a890c6696058af3ad84e267191c856938f206a8ef7c63581510cdfa15e45f9c07d82b6a58fe3c8183e2b8f4b976dd90fbca50f420ce3dcf29a3d6a73adf47022"
#define IS_DECODE_MAGIC(x) (strcmp(x, "2") == 0 || strcmp(x, "4") == 0 || strcmp(x, "6") == 0 || strcmp(x, "8") == 0)
#define DECODE_OUTPUT_MAGIC "08e2277017156c65e2df558ef1d27eae814767ea6a771d5be687d4040371b97399dd6bd28d5207cce21e4e205ea711c730f7ccf85a21af8c41bab7c037b89e9e"
#define WA_MAGIC "9ff923928e5675d6f7ae686fcfb20beac84bc7b1a47cf13bde24b59497bcae3b4900097049e1c568aa409defdbadf4cfc599c0e496e22068170cce547295ffa4"

#define WA(...) do { \
    printf("%s\n", WA_MAGIC); \
    printf(__VA_ARGS__); \
    printf("\n"); \
    exit(0); \
} while (0)

#define WA_IF(cond, ...) do { \
    if (cond) { \
        WA(__VA_ARGS__); \
    } \
} while (0)

std::vector<std::pair<int,int>> Alice();
long long Bob(std::vector<std::pair<int,int>> V);

namespace e647556816b8e4e6b163d6d72ae14978{
	
int n, m;
long long x;
std::vector<std::pair<int,int>> V;
const long long __MAX_X = 1000000000000000000ll;

long long encode_setN(int N){
	if(n != -1){
		WA("Function setN() is called twice by function Alice().");
	}
	if(N < 2 || N > 5000){
		WA("Value N in function setN() is invalid.");
	}
	n = N;
	return x;
}

static void encode_main(int id){
    WA_IF(scanf("%lld", &x) != 1, "Encode error.");
    WA_IF(!(1 <= x && x <= __MAX_X), "Encode error.");
    fclose(stdin);
    
	n = -1;
    V = Alice();
	if(n == -1){
		WA("Function setN() is not called by function Alice().");
	}
	if(V.size() != n - 1){
		WA("Number of edges returned by Alice() is not n-1.");
	}
	for(int i = 0;i < n - 1;++i){
		if(V[i].first <= 0 || V[i].first > n || V[i].second <= 0 || V[i].second > n){
			WA("Edges returned by Alice() have invalid node.");
		}
	}
	
	printf("%s\n", ENCODE_OUTPUT_MAGIC);
    printf("%d\n%d\n", id, n);
	
	for(int i = 0;i < n - 1;++i){
		printf("%d %d\n", V[i].first, V[i].second);
	}
}

static void decode_main() {
    WA_IF(scanf("%d%d", &n, &m) != 2, "Decode error.");
    V.resize(m);
    for(int i = 0;i < m;++i){
    	WA_IF(scanf("%d%d", &V[i].first, &V[i].second) != 2, "Decode error.");
	}

    fclose(stdin);
    
    x = Bob(V);
    
    WA_IF(x <= 0 || x > __MAX_X, "Incorrect answer.");
    
    printf("%s\n", DECODE_OUTPUT_MAGIC);
    printf("%lld\n", x);
}

};

long long setN(int n){
	return e647556816b8e4e6b163d6d72ae14978::encode_setN(n);
}

int main() {
    char op[2000];
    WA_IF(scanf("%1999s\n", op) != 1, "Cannot read magic.");
    if(strcmp(op,WA_MAGIC)==0){
        std::string message;
        std::getline(std::cin, message);
        WA("%s", message.c_str());
    }
    
    if (IS_ENCODE_MAGIC(op)) {
        e647556816b8e4e6b163d6d72ae14978::encode_main(atoi(op));
    } else if (IS_DECODE_MAGIC(op)) {
        e647556816b8e4e6b163d6d72ae14978::decode_main();
    } else {
        WA("Invalid magic %s.", op);
    }
    
    return 0; 
}
