#include <stdio.h>
#include <Windows.h>
#include <fstream>

int main(int argc, char* argv[])
{
	puts("TECH C\n");
	printf("argc=%d\n", argc);
	puts(argv[0]);
	if (argc<2)
		return 0;

	puts(argv[1]);
	std::ifstream ifs(argv[1]);
	if (ifs) {
		puts("‚±‚Ìƒtƒ@ƒCƒ‹‚Í‚ ‚è‚Ü‚·");
		char buf[256];
		ifs.read(buf, 256);
		std::string s = buf;
		if (s.substr(1, 3) == "PNG")
		{
			puts("PNG‚Å‚·");
		} else if (s.substr(8, 3) == "FBX")
			puts("FBX‚Å‚·");
		} else {
			puts("‚Ç‚¿‚ç‚Å‚à‚È‚¢‚Å‚·");
		}
	}
}