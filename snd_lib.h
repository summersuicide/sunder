#pragma once

#include <iostream>

#define SUNDER_TRUE 1
#define SUNDER_FALSE 0
#define SUNDER_ERROR_NULLPTR -3
#define SUNDER_ERROR_MEMORY_ALLOCATION_FAILURE -2
#define SUNDER_FAILURE -1
#define SUNDER_SUCCESS 0
#define SUNDER_EXIT_IF(condition, log_msg, exit_code) if(condition)\
													  {\
												       std::cout << log_msg; \
													   return exit_code; \
													  }\

#define SUNDER_VOID_EXIT_IF(condition, log_msg) if(condition)\
											     {\
												   std::cout << log_msg; \
												   return;\
												 }\

#define SUNDER_SET_NTH_BIT(value, n) {\
																(value) |= 1U << (n);\
																}\

#define SUNDER_IS_NTH_BIT_SET(value, n) (value) & 1U << (n)
#define SUNDER_ZERO_NTH_BIT(value, n) (value) &= ~(1U << (n))
#define SUNDER_SET_BITS(value, mask) (value) |= (mask)

#define SUNDER_LOG(a) \
				std::cout << a

#define SUNDER_HALLOC(type, count) \
				(type*)malloc(sizeof(type) * count)

#define SUNDER_FREE(memblock) \
				free(memblock);\
				memblock = nullptr

#define SUNDER_IS_VALID(ptr) \
				((ptr) != nullptr)

#define SUNDER_TICK_TIMER(timer, time_step, callback) \
			{\
				if(timer.flags & 1 << TIMER_BITS_SHOULD_ITERATE_BIT)\
				{\
					timer.iterator += time_step;\
				}\
				if(timer.iterator >= timer.duration)\
				{\
					timer.iterator = 0.0f;\
					callback;\
				}\
			}

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef u8 b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;
typedef const char cstring_literal;
typedef char cstring;

enum sunder_arena_result : u32
{
	ARENA_RESULT_SUCCESS = 0,
	ARENA_RESULT_ARENA_UNINITIALIZED,
	ARENA_RESULT_BUFFER_UNINITIALIZED,
	ARENA_RESULT_OUT_OF_MEMORY,
	ARENA_RESULT_REQUESTED_ALIGNMENT_IS_NOT_IN_POWER_OF_2,
	ARENA_RESULT_REQUESTED_ARENA_ALLOCATION_SIZE_IS_NOT_EVEN,
	ARENA_RESULT_REQUESTED_ALIGNMENT_IS_INCOMPATIBLE,
	ARENA_RESULT_OS_MEMORY_ALLOCATION_FAILURE,
	ARENA_RESULT_NONE
};

enum sunder_timer_bits : u32
{
	TIMER_BITS_SHOULD_ITERATE_BIT = 0
};

enum sunder_arena_type : u32
{
	ARENA_TYPE_CHAINED = 0,
	ARENA_TYPE_STATIC = 1
};

void* sunder_halloc(u64 type_size_in_bytes, u64 element_count);
void* sunder_halloc(u64 bytes);
void* sunder_aligned_halloc(u64 type_size_in_bytes, u64 element_count, u64 alignment);
void* sunder_aligned_halloc(u64 bytes, u64 alignment);
void sunder_free(void** memblock);
void sunder_aligned_ffree(void** memblock);
bool sunder_is_valid(const void* memblock);
void sunder_rand_seed();
i16 sunder_rand_s16(i16 start, i16 end);
i32 sunder_rand_s32(i32 start, i32 end);
i64 sunder_rand_s64(i64 start, i64 end);
u16 sunder_rand_u16(u16 start, u16 end);
u32 sunder_rand_u32(u32 start, u32 end);
u64 sunder_rand_u64(u64 start, u64 end);

// returns amount of bytes written
u64 sunder_copy_buffer(void* bytes_to_copy_to, const void* bytes_to_copy, u64 bytes_to_copy_to_size, u64 bytes_to_copy_size, u64 bytes_to_write);

struct sunder_string_t
{
	char* data = nullptr;;
	u32 length = 0;
};

struct sunder_arena_suballocation_result_t
{
	void* data = nullptr;
	sunder_arena_result result = ARENA_RESULT_NONE;
};

struct sunder_arena_t
{
	u8* buffer = nullptr;
	u64 capacity = 0;
	u64 offset = 0;
	u64 total_bytes_of_padding = 0;
	sunder_arena_t* chain = nullptr;
	u64* chain_allocation_size_buffer = nullptr;
	u32 chain_count = 0;
	sunder_arena_type type = ARENA_TYPE_STATIC;
};

bool sunder_is_divisible_by(u64 val, u64 div);
bool sunder_is_even(u64 val);
bool sunder_is_power_of_2(u64 val);
u32 sunder_align32(u32 current_offset, u32 alignment);
u64 sunder_align64(u64 current_offset, u64 alignment);
u64 sunder_compute_array_size_in_bytes(u64 type_size_in_bytes, u64 element_count);

sunder_arena_suballocation_result_t sunder_suballocate_from_arena_internal_debug(u64* offset, u64* padding, u8* buffer, u64 capacity, u64 bytes, u64 alignment);
sunder_arena_suballocation_result_t sunder_suballocate_from_arena_internal(u64* offset, u64* padding, u8* buffer, u64 capacity, u64 bytes, u64 alignment);
sunder_arena_result sunder_allocate_arena_internal(u8** buffer, u64* arena_capacity, u64 requested_capacity, u64 buffer_alignment);

sunder_arena_result sunder_allocate_arena(sunder_arena_t* arena, u64 bytes, u64 alignment, sunder_arena_type arena_type, u32 chain_count);
sunder_arena_suballocation_result_t sunder_suballocate_from_arena_debug(sunder_arena_t* arena, u64 bytes, u64 alignment);
sunder_arena_suballocation_result_t sunder_suballocate_from_arena(sunder_arena_t* arena, u64 bytes, u64 alignment);
sunder_arena_result sunder_free_arena(sunder_arena_t* arena);
sunder_arena_result sunder_reset_arena(sunder_arena_t* arena);

struct sunder_timer_t
{
	f32 duration = 0.0f;
	f32 iterator = 0.0f;
	u32 flags = 0;
};

u64 sunder_get_aligned_struct_allocation_size_debug(u64* alignment_buffer, u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment);
u64 sunder_get_aligned_struct_allocation_size(u64* alignment_buffer, u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment);
// returns amount of bytes initialised
u64 sunder_init_buffer(void* ram_buffer, u64 ram_buffer_size, u64 starting_offset, u64 ending_offset);