#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// gcc chal.c -o chal -std=c17

static void print_flag(void) {
	FILE *fp = fopen("/flag.txt", "r");
	char buf[128];

	if (fp == NULL) {
		puts("flag read error");
		return;
	}

	if (fgets(buf, sizeof(buf), fp) == NULL) {
		puts("flag read error");
		fclose(fp);
		return;
	}

	fclose(fp);
	printf("%s", buf);
}

int main(void) {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    uint32_t coins = 1000;
	uint32_t qty = 0;
	const uint32_t badge_price = 0x40000000;

	puts("=== Overflow Shop ===");
	puts("Goal: become VIP and print the flag.");
	puts("Rule: If you can buy >= 8 VIP badges, the flag is yours.");
	printf("You have %u coins.\n", coins);
	printf("Each VIP badge costs %u coins.\n", badge_price);
	printf("How many badges do you want to buy? ");

	if (scanf("%u", &qty) != 1) {
		puts("invalid input");
		return 1;
	}

	uint32_t total = qty * badge_price;

	if (total > coins) {
		puts("Not enough coins.");
		return 0;
	}

	coins -= total;
	printf("Purchase success. Remaining coins: %u\n", coins);

	if (qty >= 8) {
		puts("VIP unlocked!");
		print_flag();
	} else {
		puts("You need to buy at least 8 badges for VIP.");
	}

	return 0;
}
