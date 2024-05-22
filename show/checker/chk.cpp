#include "testlib.h"
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

#define IS_ENCODE_MAGIC(x) (strcmp(x, "1") == 0 || strcmp(x, "3") == 0 || strcmp(x, "5") == 0 || strcmp(x, "7") == 0) 
#define ENCODE_OUTPUT_MAGIC "a890c6696058af3ad84e267191c856938f206a8ef7c63581510cdfa15e45f9c07d82b6a58fe3c8183e2b8f4b976dd90fbca50f420ce3dcf29a3d6a73adf47022"
#define IS_DECODE_MAGIC(x) (strcmp(x, "2") == 0 || strcmp(x, "4") == 0 || strcmp(x, "6") == 0 || strcmp(x, "8") == 0)
#define DECODE_OUTPUT_MAGIC "08e2277017156c65e2df558ef1d27eae814767ea6a771d5be687d4040371b97399dd6bd28d5207cce21e4e205ea711c730f7ccf85a21af8c41bab7c037b89e9e"
#define WA_MAGIC "9ff923928e5675d6f7ae686fcfb20beac84bc7b1a47cf13bde24b59497bcae3b4900097049e1c568aa409defdbadf4cfc599c0e496e22068170cce547295ffa4"

#define WA(...) do { \
    quitf(_wa, __VA_ARGS__); \
} while (0)

#define WA_IF(cond, ...) do { \
    if (cond) { \
        WA(__VA_ARGS__); \
    } \
} while (0)

#define AC(...) do { \
    quitf(_ok, __VA_ARGS__); \
} while (0)

#define PARTIAL(p, ...) do { \
    quitp(p, __VA_ARGS__); \
} while (0)

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);

    inf.readLine();
	
    std::string magic = ouf.readLine();

    if (magic == WA_MAGIC) {
        std::string message = ouf.readLine();
        WA("%s", message.c_str());
    }

    WA_IF(magic != DECODE_OUTPUT_MAGIC, "Wrong decode magic.");
	
	long long n = inf.readLong();
	long long m = ouf.readLong();
	WA_IF(n != m, "Incorrect answer.");
	
	AC("Correct.");
    return 0;
}
