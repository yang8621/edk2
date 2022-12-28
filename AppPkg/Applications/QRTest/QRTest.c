#include  <Uefi.h>
#include  <Library/UefiLib.h>
#include  <Library/ShellCEntryLib.h>
#include  <Library/BaseMemoryLib.h>
#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include "qr_encode.h"

int
EFIAPI
main (
  IN int Argc,
  IN CHAR16 **Argv
  )
{
	int side, i, j, a, ecclevel;
	uint8_t bitdata[QR_MAX_BITDATA];
	char str[2048];

	printf("ECC Level [LMQH]: ");
	if (!fgets(str, sizeof(str), stdin)) {
		return 1;
	}
	switch (str[0]) {
	case 'l':
	case 'L':
		ecclevel = QR_LEVEL_L;
		break;
	case 'm':
	case 'M':
	default:
		ecclevel = QR_LEVEL_M;
		break;
	case 'q':
	case 'Q':
		ecclevel = QR_LEVEL_Q;
		break;
	case 'h':
	case 'H':
		ecclevel = QR_LEVEL_H;
		break;
	}

	printf("Enter string: ");
	if (!fgets(str, sizeof(str), stdin)) {
		return 1;
	}
	// remove newline
	if (str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = 0;
	}

	side = qr_encode(ecclevel, 0, str, 0, bitdata);

	printf("side: %d\n", side);

	for (i = 0; i < side + 2; i++) printf("██");
	printf("\n");
	for (i = 0; i < side; i++) {
		printf("██");
		for (j = 0; j < side; j++) {
			a = i * side + j;
			printf((bitdata[a / 8] & (1 << (7 - a % 8))) ? "  " : "██");
		}
		printf("██");
		printf("\n");
	}
	for (i = 0; i < side + 2; i++) printf("██");
	printf("\n");

	return 0;
  return EFI_SUCCESS;
}

