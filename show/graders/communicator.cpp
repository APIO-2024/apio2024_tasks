#include <bits/stdc++.h>

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

int n, m, id;
std::vector<std::pair<int,int>> V;
std::vector<int> f;
int getf(int x){
	return f[x] == x ? x : f[x] = getf(f[x]);
}

void random_delete_edge(){
	srand(time(0) ^ 0x179a608d);
	m = (1ll * rand() * RAND_MAX + rand()) % (n / 2) + n - 1 - (n - 2) / 2;
	std::random_shuffle(V.begin(),V.end());
	while(V.size() != m) V.pop_back();
	for(int i = 0;i < m;++i){
		if(V[i].first > V[i].second){
			std::swap(V[i].first,V[i].second);
		}
	}
	std::sort(V.begin(),V.end());
}

void delete_by_degree(){
	srand(time(0) ^ 0x179a608d);
	std::random_shuffle(V.begin(),V.end());
	std::vector<int> deg(n+1);
	for(auto e:V) ++deg[e.first],++deg[e.second];
	int rem=(n-2)/2;
	for(int ii=0;ii<2&&rem;++ii){
		for(int i=0;i<(int)V.size();++i){
			if(deg[V[i].first]==1||deg[V[i].second]==1){
				--deg[V[i].first],--deg[V[i].second];
				V.erase(V.begin()+i);
				--rem;
				break;
			}
		}
	}
	for(auto &e:V){
		if(deg[e.first]<deg[e.second]||(deg[e.first]==deg[e.second]&&e.first>e.second)) std::swap(e.first,e.second);
	}
	sort(V.begin(),V.end(),[&](std::pair<int,int> x,std::pair<int,int> y){
		if(deg[x.first]!=deg[y.first]) return deg[x.first]>deg[y.first];
		return x.first<y.first;
	});
	int tmp=V[0].first;
	std::vector<std::pair<int,int>> tV;
	for(auto e:V){
		if(e.first==tmp||!rem) tV.push_back(e);
		else --rem;
	}
	V=std::move(tV);
	for(auto &e:V) if(e.first>e.second) std::swap(e.first,e.second);
	sort(V.begin(),V.end());
	m=(int)V.size();
	assert(n-1-m<=(n-2)/2);
}

struct EdgeCollector {
	std::vector<std::vector<int>> edges;
	std::vector<std::pair<int, int>> edge_by_depth[2];

	void dfs(int x, int prev, int depth) {
		for (int i : edges[x]) {
			if (i != prev) {
				edge_by_depth[depth % 2].emplace_back(x, i);
				dfs(i, x, depth + 1);
			}
		}
	}
};

void delete_by_parity() {
	EdgeCollector collector;
	collector.edges.resize(n + 1);
	for (auto e : V) {
		collector.edges[e.first].push_back(e.second);
		collector.edges[e.second].push_back(e.first);
	}
	for (int i = 1; i <= n; ++i) {
		if (collector.edges[i].size() == 1) {
			collector.dfs(i, -1, 0);
			break;
		}
	}
	std::vector<std::pair<int, int>> candidate;
	if (collector.edge_by_depth[0].size() > collector.edge_by_depth[1].size()) {
		V = std::move(collector.edge_by_depth[0]);
		candidate = std::move(collector.edge_by_depth[1]);
	} else {
		V = std::move(collector.edge_by_depth[1]);
		candidate = std::move(collector.edge_by_depth[0]);
	}
	std::mt19937 rng{233};
	std::shuffle(candidate.begin(), candidate.end(), rng);
	for (auto e : candidate) {
		if (static_cast<int>(V.size()) < n - 1 - (n - 2) / 2) {
			V.push_back(e);
		} else {
			break;
		}
	}
	for (auto &e : V) {
		if (e.first > e.second) {
			std::swap(e.first, e.second);
		}
	}
	std::sort(V.begin(), V.end());
	m = static_cast<int>(V.size());
	assert(n - 1 - m <= (n - 2) / 2);
}

void delete_same_part(){
	srand(time(0) ^ 0x179a608d);
	std::random_shuffle(V.begin(),V.end());
	std::vector<int> deg(n+1);
	for(auto e:V) ++deg[e.first],++deg[e.second];
	std::map<long long,int> cnt;
	for(auto e:V){
		int d1=deg[e.first],d2=deg[e.second];
		if(d1>d2) std::swap(d1,d2);
		++cnt[d1*(n+1ll)+d2];
	}
	auto getcnt=[&](std::pair<int,int> e)->std::pair<int,long long>{
		int d1=deg[e.first],d2=deg[e.second];
		if(d1>d2) std::swap(d1,d2);
		return std::make_pair(cnt[d1*(n+1ll)+d2],d1*(n+1ll)+d2);
	};
	sort(V.begin(),V.end(),[&](std::pair<int,int> x,std::pair<int,int> y){return getcnt(x)>getcnt(y);});
	V.resize(n-1-(n-2)/2);
	for(auto &e:V) if(e.first>e.second) std::swap(e.first,e.second);
	sort(V.begin(),V.end());
	m=(int)V.size();
}

int main() {
    std::string magic;
    std::getline(std::cin, magic);

    if(magic == WA_MAGIC){
        std::string message;
        std::getline(std::cin, message);
        WA("%s", message.c_str());
    }

    WA_IF(magic != ENCODE_OUTPUT_MAGIC, "Wrong encode magic.");
    
    char op[2000];
    WA_IF(scanf("%1999s\n", op) != 1, "Cannot read op.");
    WA_IF(!IS_ENCODE_MAGIC(op), "Error op.");  
    WA_IF(scanf("%d", &n) != 1, "Invalid encode.");
	id = atoi(op) / 2 + 1;
	
    V.resize(n - 1);
    f.resize(n + 1);
    for(int i = 1; i <= n;++i){
    	f[i] = i;
	} 
    for(int i = 0;i < n - 1;++i){
    	WA_IF(scanf("%d%d", &V[i].first, &V[i].second) != 2, "Invalid encode.");
    	int p = getf(V[i].first);
    	int q = getf(V[i].second);
    	WA_IF(p == q, "Output of encode is not a tree.");
    	f[p] = q;
	}
	
    fclose(stdin);
    
    if(id == 1){
    	random_delete_edge();
	}
	else if(id == 2){
		delete_by_degree();
	}
	else if(id == 3){
		delete_by_parity();
	}
	else{
		delete_same_part();
	}
	
	printf("%d\n", id * 2);
	printf("%d %d\n", n, m);
	for(int i = 0;i < m;++i){
		printf("%d %d\n", V[i].first, V[i].second);
	}
    
    return 0;
}
