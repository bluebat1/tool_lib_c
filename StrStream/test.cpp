#include <stdio.h>
#include "StrStream.h"

#define texts "@think smiling is as important as sunshine. Smiling is like it can make people happy and have a good day----\r\n"

int main(int argc, char const *argv[])
{
	printf("123456\r\n");
	char buf[512];
	StrStreamDef ss;
	int ret;

	StrStreamInit(&ss);
	StrStreamWrite(&ss, texts, sizeof(texts)-2);
	
	printf("write ok\r\n");

	ret = StrStreamReadLine(&ss, buf, 123);
	printf("len %d\r\n", ret);
	printf("%s\n", buf);

	StrStreamWrite(&ss, texts, sizeof(texts)-1);
	printf("write ok\r\n");
	ret = StrStreamReadLine(&ss, buf, 123);
	printf("len %d\r\n", ret);
	printf("%s\n", buf);

	printf("///---\r\n");

	for (size_t i = 0; i < 9; i++)
	{
		StrStreamWrite(&ss, texts, sizeof(texts)-1);
		StrStreamWrite(&ss, texts, sizeof(texts)-1);
		StrStreamWrite(&ss, texts, sizeof(texts)-1);
	}
	
	int count = 0;
	while(1) {
		ret = StrStreamReadLine(&ss, buf, 123);
		if(ret < 0) {
			break;
		}
		count++;
		printf("len %d\r\n", ret);
		printf("%d: %s\n", count, buf);
	}
	printf("ss size %d", ss.size);
	
	return 0;
}



