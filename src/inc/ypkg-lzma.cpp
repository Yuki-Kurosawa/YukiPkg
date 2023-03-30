#include "src/inc/ypkg-lzma.h"

static bool
init_decoder(lzma_stream *strm)
{
	lzma_ret ret = lzma_stream_decoder(
			strm, UINT64_MAX, LZMA_CONCATENATED);
    
	if (ret == LZMA_OK)
		return true;

	const char *msg;
	switch (ret) {
	case LZMA_MEM_ERROR:
		msg = "Memory allocation failed";
		break;

	case LZMA_OPTIONS_ERROR:
		msg = "Unsupported decompressor flags";
		break;

	default:
		msg = "Unknown error, possibly a bug";
		break;
	}

	fprintf(stderr, "Error initializing the decoder: %s (error code %u)\n",
			msg, ret);
	return false;
}


static bool
decompress(lzma_stream *strm, const char *inname, FILE *infile, FILE *outfile)
{
    lzma_action action = LZMA_RUN;

	uint8_t inbuf[BUFSIZ];
	uint8_t outbuf[BUFSIZ];

	strm->next_in = NULL;
	strm->avail_in = 0;
	strm->next_out = outbuf;
	strm->avail_out = sizeof(outbuf);

	while (true) {
		if (strm->avail_in == 0 && !feof(infile)) {
			strm->next_in = inbuf;
			strm->avail_in = fread(inbuf, 1, sizeof(inbuf),
					infile);

			if (ferror(infile)) {
				fprintf(stderr, "%s: Read error: %s\n",
						inname, strerror(errno));
				return false;
			}

			if (feof(infile))
				action = LZMA_FINISH;
		}

		lzma_ret ret = lzma_code(strm, action);

		if (strm->avail_out == 0 || ret == LZMA_STREAM_END) {
			size_t write_size = sizeof(outbuf) - strm->avail_out;

			if (fwrite(outbuf, 1, write_size, outfile)
					!= write_size) {
				fprintf(stderr, "Write error: %s\n",
						strerror(errno));
				return false;
			}

			strm->next_out = outbuf;
			strm->avail_out = sizeof(outbuf);
		}

		if (ret != LZMA_OK) {

			if (ret == LZMA_STREAM_END)
				return true;

			const char *msg;
			switch (ret) {
			case LZMA_MEM_ERROR:
				msg = "Memory allocation failed";
				break;

			case LZMA_FORMAT_ERROR:
				msg = "The input is not in the .xz format";
				break;

			case LZMA_OPTIONS_ERROR:
				msg = "Unsupported compression options";
				break;

			case LZMA_DATA_ERROR:
				msg = "Compressed file is corrupt";
				break;

			case LZMA_BUF_ERROR:
				msg = "Compressed file is truncated or "
						"otherwise corrupt";
				break;

			default:
				// This is most likely LZMA_PROG_ERROR.
				msg = "Unknown error, possibly a bug";
				break;
			}

			fprintf(stderr, "%s: Decoder error: "
					"%s (error code %u)\n",
					inname, msg, ret);
			return false;
		}
	}
}


int unxz(char* xz,char* ret)
{

	lzma_stream strm = LZMA_STREAM_INIT;

	bool success = true;

	
	if (!init_decoder(&strm)) {
		// Decoder initialization failed. There's no point
		// to retry it so we need to exit.
		success = false;
		return -1;
	}

	FILE *infile = fopen(xz, "rb");
	FILE *outfile = fopen(ret, "wb");

	if (infile == NULL) {
		fprintf(stderr, "%s: Error opening the "
				"input file: %s\n",
				xz, strerror(errno));
		success = false;
	} else {
		success &= decompress(&strm, xz, infile, outfile);
		fclose(infile);		
		fclose(outfile);
	}
	
	lzma_end(&strm);

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}