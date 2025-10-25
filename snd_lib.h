#pragma once

#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>

#define SUNDER_INTERNAL static
#define SUNDER_UNIQUE  inline
#define SUNDER_PERSISTENT static
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

#define SUNDER_SET_BIT(value, bit, shift) {\
																(value) |= (shift << (bit));\
																}\

#define SUNDER_IS_ANY_BIT_SET(value, bit, shift) (value) & (shift << (bit))
#define SUNDER_ZERO_BIT(value, bit, shift) (value) &= ~(shift << (bit))
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
				if(timer.flags & 1 << SUNDER_TIMER_BITS_SHOULD_ITERATE_BIT)\
				{\
					timer.iterator += time_step;\
				}\
				if(timer.iterator >= timer.duration)\
				{\
					timer.iterator = 0.0f;\
					callback;\
				}\
			}

#define SUNDER_ARE_BITS_SET(val, mask) ((val) & (mask)) == (mask)

#define SUNDER_TO_BIT_MASK(type, shift, out_mask, storage, count, merged_count, bit_count)\
			 {\
				if (count < ((bit_count) + 1))\
				{\
				const void* temp = (const u8*)&storage;\
				const u8* iter = (const u8*)temp;\
				type internal_mask = 0;\
				\
				for (u32 i = 0; i < count; i++)\
				{\
					if(iter[i] < bit_count)\
					{\
						internal_mask |= (shift << iter[i]);\
						merged_count++;\
					}\
				}\
				\
				out_mask = internal_mask;\
				}\
			  }

#define SUNDER_IS_SINGLE_BIT_SET(val, bit, shift) val == (shift << bit)

#define SUNDER_CONDITIONAL_EXECUTION(type, buffer, size, expression, val_to_avoid, action) \
			{\
				for(type i = 0; i < size; i++)\
				{\
					if(buffer[i] != val_to_avoid && buffer[i]expression)\
					{\
						action\
					}\
				}\
			}\

#define SUNDER_DEFINE_FLUX_BUFFER(type, type_name, size_type) \
				struct flux_buffer_##type_name##_t\
				{\
					type* buffer = nullptr;\
					size_type size = 0;\
				};\

#define SUNDER_DEFINE_FLUX(type, type_name, size_type) \
				struct flux_##type_name##_t\
				{\
					type* buffer = nullptr;\
					size_type capacity = 0;\
					size_type size = 0;\
				};\

#define SUNDER_DEFINE_CLAMP_FUNCTION(type) \
			 type sunder_clamp_##type(type min, type max, type val);

#define SUNDER_IMPLEMENT_CLAMP_FUNCTION(type)\
			type sunder_clamp_##type(type min, type max, type val)\
			{\
				if (val < min) { return min; }\
				else if (val > max) { return  max; }\
				return val; \
			}

#define SUNDER_DEFINE_QUICK_SORT_COMPARE_FUNCTION(type) bool (*comparison_function)(const type*, const type*)

#define SUNDER_DEFINE_QUICK_SORT_PARTITION_FUNCTION(type, type_name, prefix) \
			i64 prefix##_quick_sort_partition_##type_name(type* buffer, i64 starting_index, i64 ending_index, SUNDER_DEFINE_QUICK_SORT_COMPARE_FUNCTION(type));

#define SUNDER_IMPLEMENT_QUICK_SORT_PARTITION_FUNCTION(type, type_name, prefix) \
			 i64 prefix##_quick_sort_partition_##type_name(type* buffer, i64 starting_index, i64 ending_index, SUNDER_DEFINE_QUICK_SORT_COMPARE_FUNCTION(type)) \
			{\
				const type pivot = buffer[ending_index]; \
				i64 i = starting_index - 1;\
				\
				for (i64 j = starting_index; j <= ending_index - 1; j++)\
				{\
					if(comparison_function(&buffer[j], &pivot))\
					{\
						i++;\
						const type temp = buffer[i];\
						buffer[i] = buffer[j];\
						buffer[j] = temp;\
					}\
				}\
				i++;\
				\
				const type temp = buffer[i]; \
				buffer[i] = buffer[ending_index]; \
				buffer[ending_index] = temp; \
				\
				return i;\
			}

#define SUNDER_DEFINE_QUICK_SORT_FUNCTION(type, type_name, prefix) \
			void prefix##_quick_sort_##type_name(type* buffer, i64 starting_index, i64 ending_index, SUNDER_DEFINE_QUICK_SORT_COMPARE_FUNCTION(type));

#define SUNDER_IMPLEMENT_QUICK_SORT_FUNCTION(type, type_name,  prefix) \
			 void prefix##_quick_sort_##type_name(type* buffer, i64 starting_index, i64 ending_index, SUNDER_DEFINE_QUICK_SORT_COMPARE_FUNCTION(type)) \
			{ \
				if(ending_index <= starting_index)\
				{\
					return;\
				}\
				\
				const i64 pivot = prefix##_quick_sort_partition_##type_name(buffer, starting_index, ending_index, comparison_function);\
				\
				prefix##_quick_sort_##type_name(buffer, starting_index, pivot - 1, comparison_function);\
				prefix##_quick_sort_##type_name(buffer, pivot + 1, ending_index, comparison_function);\
			}

#define SUNDER_DEFINE_EXISTS_FUNCTION(type, prefix, type_name, index_type) \
			bool prefix##_exists_##type_name(const type* buffer,  index_type buffer_size, type val);

#define SUNDER_IMPLEMENT_EXISTS_FUNCTION(type, prefix, type_name, index_type) \
			bool prefix##_exists_##type_name(const type* buffer,  index_type buffer_size, type val) \
			{\
				for (index_type i = 0; i < buffer_size; i++) \
				{\
					if (buffer[i] == val)\
					{\
						return true;\
					}\
				}\
				\
				return false;\
			}

#define SUNDER_CAST(cast_type, val) (cast_type)(val)
#define SUNDER_CAST2(cast_type) (cast_type)

#define SUNDER_DEFINE_BUFFER_INDEX_QUERY_RESULT_STRUCTURE(type, prefix, type_name, index_type) \
			struct prefix##_buffer_index_query_result_##type_name##_t\
			{\
				type value_at_index{};\
				index_type return_index{};\
			};

#define SUNDER_DEFINE_QUERY_BUFFER_INDEX_FUNCTION(type, prefix, type_name, index_type) \
			prefix##_buffer_index_query_result_##type_name##_t prefix##_query_buffer_index_##type_name(const type* buffer, index_type starting_index, index_type ending_index, type val_at_index, bool reverse_logic);

#define SUNDER_IMPLEMENT_QUERY_BUFFER_INDEX_FUNCTION(type, prefix, type_name, index_type) \
			prefix##_buffer_index_query_result_##type_name##_t prefix##_query_buffer_index_##type_name(const type* buffer, index_type starting_index, index_type ending_index, type val_at_index, bool reverse_logic)\
			{\
				prefix##_buffer_index_query_result_##type_name##_t  res;\
				\
				if (reverse_logic)\
				{\
					for (u32 i = starting_index; i < ending_index; i++)\
					{\
						if (buffer[i] != val_at_index)\
						{\
							res.value_at_index = buffer[i];\
							res.return_index = i;\
							\
							return res;\
						}\
					}\
					\
					return res;\
				}\
				\
				else\
				{\
					for (u32 i = starting_index; i < ending_index; i++)\
					{\
						if (buffer[i] == val_at_index)\
						{\
							res.value_at_index = buffer[i];\
							res.return_index = i;\
							\
							return res;\
						}\
					}\
					\
					return res;\
				}\
				\
			return res;\
			\
		}

#define SUNDER_BIT_TO_MASK(bit, shift) (shift << (bit))

#define SUNDER_DEFAULT_ARENA_FREE_BUFFER_ELEMENT_COUNT 32u
#define SUNDER_DEFAULT_ARENA_FREE_CHUNK_BUFFER_ELEMENT_COUNT 32u
#define SUNDER_DEFAULT_ARENA_ELEMENT_COUNT_PER_FREE_CHUNK 4u
#define SUNDER_ARENA_SUBALLOCATION_MIN_ALIGNMENT 2u
#define SUNDER_ARENA_SUBALLOCATION_MAX_ALIGNMENT 4096u
#define SUNDER_PRE_FREE_CAST(ptr) (void**)&(ptr)

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
typedef u32 b32;
typedef const char cstring_literal;
typedef char cstring;
typedef f32 real32;
typedef f64 real64;

SUNDER_DEFINE_BUFFER_INDEX_QUERY_RESULT_STRUCTURE(u32, sunder, u32, u32)

SUNDER_DEFINE_FLUX_BUFFER(u16,  u16, u16)
SUNDER_DEFINE_FLUX_BUFFER(u32, u32, u32)
SUNDER_DEFINE_FLUX_BUFFER(u64, u64, u64)
SUNDER_DEFINE_FLUX_BUFFER(f32, f32, u32)
SUNDER_DEFINE_FLUX_BUFFER(f64, f64, u32)

SUNDER_DEFINE_FLUX(u16, u16, u16)
SUNDER_DEFINE_FLUX(u32, u32, u32)
SUNDER_DEFINE_FLUX(u64, u64, u64)
SUNDER_DEFINE_FLUX(f32, f32, u32)
SUNDER_DEFINE_FLUX(f64, f64, u32)

enum sunder_timer_bits : u32
{
	SUNDER_TIMER_BITS_SHOULD_ITERATE_BIT = 0u
};

enum sunder_arena_result : u32
{
	SUNDER_ARENA_RESULT_SUCCESS = 0u,
	SUNDER_ARENA_RESULT_FAILURE = 1u,
	SUNDER_ARENA_RESULT_ARENA_UNINITIALIZED = 2u,
	SUNDER_ARENA_RESULT_BUFFER_UNINITIALIZED = 3u,
	SUNDER_ARENA_RESULT_OUT_OF_ARENA_MEMORY = 4u,
	SUNDER_ARENA_RESULT_INVALID_REQUESTED_ALIGNMENT = 5u,
	SUNDER_ARENA_RESULT_OS_MEMORY_ALLOCATION_FAILURE =  6u,
	SUNDER_ARENA_RESULT_SUCCESS_REQUESTED_ALIGNMENT_HAS_BEEN_CLAMPED_TO_2 = 7u
};

enum sunder_arena_bits : u8
{
	SUNDER_ARENA_BITS_ALLOW_FREE_BUFFER_USAGE_BIT = 0,
	SUNDER_ARENA_BITS_SUBALLOCATION_ALGORITHM_FIRST_SUITABLE_BIT = 1
};

struct sunder_arena_free_memory_block_t
{
	u64 suballocation_starting_offset = 0;
	u64 suballocation_size = 0;
};

struct sunder_arena_allocation_data_t
{
	u64 arena_allocation_size = 0;
	u32 arena_allocation_alignment = 0;
	u32 free_buffer_element_count = 0;
	u8 flags = 0;
};

struct sunder_arena_suballocation_result_t
{
	void* data = nullptr;
	sunder_arena_result result = SUNDER_ARENA_RESULT_SUCCESS;
};

struct sunder_arena_t
{
	u8* buffer = nullptr;
	u64 capacity = 0;
	u64 offset = 0;
	//sunder_arena_t* chain;
	//u32 chain_count;
	//u32 allocation_alignment;
	//u32 flags;
};

struct sunder_timer_t
{
	f32 duration = 0.0f;
	f32 iterator = 0.0f;
	u32 flags = 0;
};

struct sunder_buffer_copy_data_t
{
	u64 dst_size = 0;
	u64 src_size = 0;
	u64 bytes_to_write = 0;
	u64 dst_offset = 0;
	u64 src_offset = 0;
};

struct sunder_string_t
{
	char* data = nullptr;
	u32 length = 0;
};

struct sunder_bit_index_buffer64_t { u8 index_buffer[64]; };
struct sunder_bit_index_buffer32_t { u8 index_buffer[32]; };
struct sunder_bit_index_buffer16_t { u8 index_buffer[16]; };
struct sunder_bit_index_buffer8_t   { u8 index_buffer[8];   };

typedef void (*sunder_thread_function_ptr)(void*);
typedef std::thread::id sunder_thread_id;

struct sunder_thread_t { std::thread thread; };
struct sunder_mutex_t { std::mutex mutex; };

static std::chrono::steady_clock::time_point sunder_initial_time;

typedef bool (*sunder_quick_sort_comparison_function_ptr)(const void*, const void*);

void*													sunder_halloc(u64 type_size_in_bytes, u64 element_count);
void*													sunder_halloc(u64 bytes);
void*													sunder_aligned_halloc(u64 type_size_in_bytes, u64 element_count, u64 alignment);
void*													sunder_aligned_halloc(u64 bytes, u64 alignment);
void														sunder_free(void** memblock);
void														sunder_aligned_free(void** memblock);
bool														sunder_is_valid(const void* memblock);
void														sunder_rand_seed();
i16														sunder_rand_i16(i16 start, i16 end);
i32														sunder_rand_i32(i32 start, i32 end);
i64														sunder_rand_i64(i64 start, i64 end);
u16														sunder_rand_u16(u16 start, u16 end);
u32														sunder_rand_u32(u32 start, u32 end);
u64														sunder_rand_u64(u64 start, u64 end);

															// returns amount of bytes written
u64														sunder_copy_buffer(void* dst, const void* src, const sunder_buffer_copy_data_t* copying_data);
bool														sunder_is_divisible_by(u64 val, u64 div);
bool														sunder_is_even(u64 val);
bool														sunder_is_power_of_2(u64 val);
u32														sunder_align32(u32 current_offset, u32 alignment);
u64														sunder_align64(u64 current_offset, u64 alignment);
u64														sunder_compute_array_size_in_bytes(u64 type_size_in_bytes, u64 element_count);

sunder_arena_suballocation_result_t   sunder_suballocate_from_arena_debug_internal(sunder_arena_t* arena, u64 bytes, u32 alignment);
sunder_arena_suballocation_result_t   sunder_suballocate_from_arena_internal(sunder_arena_t* arena, u64 bytes, u32 alignment);
sunder_arena_result								sunder_converge_arena_chain_debug(sunder_arena_t* arena);

															// alignment argument stands for alignment that will be used to allocate internal arena buffer with _aligned_malloc
sunder_arena_result								sunder_allocate_arena(sunder_arena_t* arena, u64 capacity, u32 arena_alignment);
sunder_arena_suballocation_result_t	sunder_suballocate_from_arena_debug(sunder_arena_t* arena, u64 bytes, u32 alignment);
sunder_arena_suballocation_result_t	sunder_suballocate_from_arena(sunder_arena_t* arena, u64 bytes, u32 alignment);
sunder_arena_result								sunder_free_arena(sunder_arena_t* arena);

u64														sunder_get_aligned_struct_allocation_size_debug(const u64* alignment_buffer, const u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment);
u64														sunder_get_aligned_struct_allocation_size(const u64* alignment_buffer, const u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment);

															// returns amount of bytes initialised
u64														sunder_initialize_buffer(void* buffer, u64 buffer_size, u64 starting_offset, u64 bytes_to_init);
u64														sunder_compute_aligned_allocation_size(u64 type_size_in_bytes, u64 element_count, u64 alignment);

															//	returns UINT8_MAX on failure
u8															sunder_to_bit_mask8(const sunder_bit_index_buffer8_t& storage, u32 count);

															//	returns UINT16_MAX on failure
u16														sunder_to_bit_mask16(const sunder_bit_index_buffer16_t& storage, u32 count);

															//	returns UINT32_MAX on failure
u32														sunder_to_bit_mask32(const sunder_bit_index_buffer32_t& storage, u32 count);

															//	returns UINT64_MAX on failure
u64														sunder_to_bit_mask64(const sunder_bit_index_buffer64_t& storage, u32 count);

SUNDER_DEFINE_EXISTS_FUNCTION(u32, sunder, u32, u32)

void														sunder_invoke_function_on_thread_launch(sunder_thread_function_ptr function_ptr, void* args);
void														sunder_launch_thread(sunder_thread_t* thread, sunder_thread_function_ptr function_ptr, void* args);
void														sunder_join_thread(sunder_thread_t* thread);
void														sunder_detach_thread(sunder_thread_t* thread);
void														sunder_sleep_on_current_thread_for(f64 seconds);
sunder_thread_id									sunder_get_current_thread_id();

void														sunder_initialize_time();
f64														sunder_get_elapsed_time_in_seconds();

SUNDER_DEFINE_CLAMP_FUNCTION(i8);
SUNDER_DEFINE_CLAMP_FUNCTION(i16);
SUNDER_DEFINE_CLAMP_FUNCTION(i32);
SUNDER_DEFINE_CLAMP_FUNCTION(i64);

SUNDER_DEFINE_CLAMP_FUNCTION(u8);
SUNDER_DEFINE_CLAMP_FUNCTION(u16);
SUNDER_DEFINE_CLAMP_FUNCTION(u32);
SUNDER_DEFINE_CLAMP_FUNCTION(u64);

SUNDER_DEFINE_CLAMP_FUNCTION(f32);
SUNDER_DEFINE_CLAMP_FUNCTION(f64);

bool														sunder_compare_strings(cstring_literal* str1, u32 str1_size,  cstring_literal* str2, u32 str2_size);

SUNDER_DEFINE_QUERY_BUFFER_INDEX_FUNCTION(u32, sunder, u32, u32)

SUNDER_DEFINE_QUICK_SORT_PARTITION_FUNCTION(sunder_arena_free_memory_block_t, arena_free_memory_block, sunder)
SUNDER_DEFINE_QUICK_SORT_FUNCTION(sunder_arena_free_memory_block_t, arena_free_memory_block, sunder)

void														sunder_log_string(const sunder_string_t* string);
u64														sunder_update_aligned_value_u64(u64 val, u64 update_val, u32 alignment);
u32														sunder_update_aligned_value_u32(u32 val, u32 update_val, u32 alignment);
u64														sunder_kilobytes_to_bytes(u64 kb);
u64														sunder_megabytes_to_bytes(u64 mb);
bool														sunder_valid_index(u32 index, u32 element_count);
bool														sunder_valid_offset(u64 offset, u64 capacity);

															//	aligns every single element in an array / written pretty much specifically for computing proper allocation size for vram suballocations that need to be treated as separate suballocations (etc. dynamicly offseting into descriptors)
u64														sunder_compute_aligned_array_allocation_size(u64 type_size_in_bytes, u64 element_count, u32 alignment);
u64														sunder_accumulate_aligned_allocation_size(const u64* aligned_allocation_size_buffer, u64 element_count, u32 alignment);
i32														sunder_int_to_string(i64 value, char* result, u32 base);
i32														sunder_uint_to_string(u64 value, char* result, u32 base);
i32														sunder_float_to_string(f64 value, char* result, u32 precision, u32 base);

