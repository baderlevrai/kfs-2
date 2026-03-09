#include <kernel.h>

typedef struct {
	uint16_t limit_low; // 0-15
	uint16_t base_low;  // 0-15
	uint8_t base_middle; // 16-23
	uint8_t access;
	uint8_t FlagsLimitHight; // 4 bit flags and 4 bit limit high
	uint8_t base_high; // 24-31
} __attribute__((packed)) GDT_entry;

typedef enum {
	GDT_ACCESS_CODE_READABLE = 0x02,
	GDT_ACCESS_DATA_WRITABLE = 0x02,

	GDT_ACCESS_CODE_CONFORMING = 0x04,
	GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
	GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,

	GDT_ACCESS_DATA_SEGMENT = 0x10,
	GDT_ACCESS_CODE_SEGMENT = 0x18,

	GDT_ACCESS_DESCRIPTOR_TSS = 0x00,

	GDT_ACCESS_RING0 = 0x00,
	GDT_ACCESS_RING1 = 0x20,
	GDT_ACCESS_RING2 = 0x40,
	GDT_ACCESS_RING3 = 0x60,

	GDT_ACCESS_PRESENT = 0x80
} GDT_ACCESS;

typedef enum {
	GDT_FLAG_16_BIT = 0x00,
	GDT_FLAG_32_BIT = 0x40,
	GDT_FLAG_64_BIT = 0x20,

	GDT_FLAG_GRANULARITY_BYTE = 0x00,
	GDT_FLAG_GRANULARITY_PAGE = 0x80
} GDT_FLAG;

#define GDT_LIMIT_LOW(limit)	(limit & 0xFFFF)
#define GDT_BASE_LOW(base)		(base & 0xFFFF)
#define GDT_BASE_MIDDLE(base) ((base >> 16) & 0xFF)
#define GDT_ACCESS(access)		(access & 0xFF)
#define GDT_FLAGS_LIMIT_HIGH(flags, limit) (((limit >> 16) & 0x0F) | (flags & 0xF0))
#define GDT_BASE_HIGH(base)		((base >> 24) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags) { \
	GDT_LIMIT_LOW(limit), \
	GDT_BASE_LOW(base), \
	GDT_BASE_MIDDLE(base), \
	access, \
	GDT_FLAGS_LIMIT_HIGH(flags, limit), \
	GDT_BASE_HIGH(base) \
}

