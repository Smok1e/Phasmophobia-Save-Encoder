#include <cstdio>
#include <cstring>

//------------------------

#define BUFFSIZE 1024

//------------------------

int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		printf ("Usage: Phasmophobia-Save-Encoder [source filename] [result filename]\n");
		return 0;
	}

	const char* key    = "CHANGE ME TO YOUR OWN RANDOM STRING"; // lol it works
	size_t      keylen = strlen (key);

	const char* source_filename = argv[1];
	const char* result_filename = argv[2];

	FILE* source = nullptr;
	FILE* result = nullptr;

	char errbuff[BUFFSIZE] = "";

	errno_t err = fopen_s (&source, source_filename, "rb");
	if (err || !source)
	{
		strerror_s (errbuff, err);
		printf ("Failed to open source file '%s' for reading: %s\n", source_filename, errbuff);
		return 0;
	}

	err = fopen_s (&result, result_filename, "wb");
	if (err || !result)
	{
		strerror_s (errbuff, err);
		printf ("Failed to open result file '%s' for writing: %s\n", result_filename, errbuff);

		fclose (source);
		return 0;
	}

	fseek (source, 0, SEEK_END);
	size_t size = ftell (source);
	fseek (source, 0, SEEK_SET);

	for (size_t i = 0; i < size; i++)
		fputc (fgetc (source) ^ key[i % keylen], result);

	fclose (source);
	fclose (result);

	printf ("Result saved as '%s'\n", result_filename);		 
	return 0;
}

//------------------------
