#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const uint16_t BITS_PER_PIXEL = 24;

#pragma pack(push, 1)
struct bitmap_file_header {
	uint8_t  magic[2];
	uint32_t file_size;
	uint16_t _reserved[2];
	uint32_t offset;
};

struct bitmap_info_header {
	uint32_t info_header_size;
	uint32_t width;
	uint32_t height;
	uint16_t color_plane_n;
	uint16_t bits_per_pixel;
	uint32_t compression_method;
	uint32_t image_size;
	uint32_t horizontal_resolution;
	uint32_t vertical_resolution;
	uint32_t color_n;
	uint32_t important_color_n;
};


struct dds_header {
	uint32_t magic;
	uint32_t size;
	uint32_t flags;
	uint32_t height;
	uint32_t width;
	uint32_t pitch_or_linear_size;
	uint32_t depth;
	uint32_t mipmap_count;
	uint32_t _reserved1[11];

	struct {
		uint32_t size;
		uint32_t flags;
		uint32_t fourCC;
		#define FOURCC_DXT1 0x31545844
		#define FOURCC_DXT3 0x33545844
		#define FOURCC_DXT5 0x35545844
		uint32_t RGB_bit_count;
		uint32_t R_bitmask;
		uint32_t G_bitmask;
		uint32_t B_bitmask;
		uint32_t A_bitmask;
	} pixel_format;

	struct {
		uint32_t caps1;
		uint32_t caps2;
		uint32_t DDSX;
		uint32_t _reserved;
	} caps;
	uint32_t _reserved2;
};
#pragma pack(pop)


bool validate_bitmap_file_header(struct bitmap_file_header *file_header){
	return file_header->magic[0] == 'B' && file_header->magic[1] == 'M';
}

bool validate_bitmap_info_header(struct bitmap_info_header *info_header){
	return (info_header->bits_per_pixel == BITS_PER_PIXEL) && (info_header->compression_method == 0);
}


GLuint load_bmp(const char *image_path){
	FILE *bmp_file = fopen(image_path, "rb");

	if (!bmp_file){
		getchar();
		fprintf(stderr, "File %s does not exist\n", image_path);
		exit(-1);
	}

	struct bitmap_file_header file_header;
	struct bitmap_info_header info_header;

	if (!fread(&file_header, sizeof(struct bitmap_file_header), 1, bmp_file)
	 || !validate_bitmap_file_header(&file_header)
	 || !fread(&info_header, sizeof(struct bitmap_info_header), 1, bmp_file)
	 || !validate_bitmap_info_header(&info_header)
	) {
		fprintf(stderr, "Invalid BMP file\n");
		fclose(bmp_file);
		exit(-1);
	}

	if (!file_header.offset)     file_header.offset = 54;
	if (!info_header.image_size) info_header.image_size = info_header.width * info_header.height * 3;

	char* image = (char*) malloc(info_header.image_size);
	fread(image, 1, info_header.image_size, bmp_file);
	fclose(bmp_file);

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info_header.width, info_header.height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);

	free(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture_id;
}


GLuint load_dds(const char *image_path){
	struct dds_header header;

	FILE *dds_file;
	dds_file = fopen(image_path, "rb");
	if (!dds_file) {
		fprintf(stderr, "File %s does not exist", image_path);
		exit(-1);
	}

	fread(&header, sizeof(struct dds_header), 1, dds_file);

	size_t image_size = header.mipmap_count > 1 ? header.pitch_or_linear_size * 2 : header.pitch_or_linear_size;
	char* image = (char*) malloc(image_size);
	fread(image, 1, image_size, dds_file);
	fclose(dds_file);

	size_t components = (header.pixel_format.fourCC == FOURCC_DXT1) ? 3 : 4;
	uint32_t format;

	switch(header.pixel_format.fourCC) {
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(image);
		exit(-1);
	}

	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	size_t block_size = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	size_t offset = 0;
	size_t width  = header.width;
	size_t height = header.height;

	for (size_t level = 0; level < header.mipmap_count && (width || height); level++){
		size_t size = ((width + 3) / 4) * ((height + 3) / 4) * block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, image + offset);

		offset += size;
		width  /= 2;
		height /= 2;

		if (width  < 1) width  = 1;
		if (height < 1) height = 1;
	}

	free(image);
	return texture_id;
}
