#include "snd_lib.h"
#include <ctime>

void* sunder_halloc(u64 type_size_in_bytes, u64 element_count)
{
	if (element_count > 0)
	{
		void* memblock = malloc(type_size_in_bytes * element_count);
		if (memblock == NULL) memblock = nullptr;
		return memblock;
	}

	return nullptr;
}

void* sunder_halloc(u64 bytes)
{
	if (bytes > 0)
	{
		void* memblock = malloc(bytes);
		if (memblock == NULL) memblock = nullptr;
		return memblock;
	}

	return nullptr;
}

void* sunder_aligned_halloc(u64 type_size_in_bytes, u64 element_count, u64 alignment)
{
	if (type_size_in_bytes ==  0 || alignment == 0 || element_count == 0) { return nullptr; }

	void* memblock = _aligned_malloc(type_size_in_bytes * element_count, alignment);
	if (memblock == NULL) { memblock = nullptr; }
		
	return memblock;
}

void* sunder_aligned_halloc(u64 bytes, u64 alignment)
{
	if (bytes < 0 || alignment == 0) { return nullptr; }

	void* memblock = _aligned_malloc(bytes, alignment);
	if (memblock == NULL) { memblock = nullptr; }

	return memblock;
}

void sunder_free(void** memblock)
{
	if (memblock == nullptr) { return; }

	if (*memblock != nullptr)
	{
		free(*memblock);
		*memblock = nullptr;
	}
}

void sunder_aligned_free(void** memblock)
{
	if (memblock == nullptr) { return; }

	if (*memblock != nullptr)
	{
		_aligned_free(*memblock);
		*memblock = nullptr;
	}
}

bool sunder_is_valid(const void* memblock)
{
	return memblock != nullptr;
}

void sunder_rand_seed()
{
	srand((u32)time(0));
}

i16 sunder_rand_i16(i16 start, i16 end)
{
	i16 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

i32 sunder_rand_i32(i32 start, i32 end)
{
	i32 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

i64 sunder_rand_i64(i64 start, i64 end)
{
	i64 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

u16 sunder_rand_u16(u16 start, u16 end)
{
	u16 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

u32 sunder_rand_u32(u32 start, u32 end)
{
	u32 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

u64 sunder_rand_u64(u64 start, u64 end)
{
	u64 diapason = end - start;

	return rand() % (diapason + 1) + start;
}

u64 sunder_copy_buffer(void* dst, const void* src, const sunder_buffer_copy_data_t* copying_data)
{
	if (dst == nullptr) { return 0; }
	if (src == nullptr) { return 0; }

	i8* temp_bytes_to_copy_to = (i8*)dst;
	i8* temp_bytes_to_copy = (i8*)src;

	if (copying_data->bytes_to_write > copying_data->dst_size || copying_data->bytes_to_write > copying_data->src_size || copying_data->bytes_to_write == 0) { return 0; }

		for (u64 i = 0; i < copying_data->bytes_to_write; i++)
		{
			temp_bytes_to_copy_to[i + copying_data->dst_offset] = temp_bytes_to_copy[i + copying_data->src_offset];
		}

	return copying_data->bytes_to_write;
}

bool sunder_is_even(u64 val)
{
	return val % 2 == 0;
}

bool sunder_is_power_of_2(u64 val)
{
	return val != 0 && (val & (val - 1)) == 0;
}

u64 sunder_align64(u64 current_offset, u64 alignment)
{
	return (current_offset + alignment - 1) & ~(alignment - 1);
}

u32 sunder_align32(u32 current_offset, u32 alignment)
{
	return (current_offset + alignment - 1) & ~(alignment - 1);
}

u64 sunder_compute_array_size_in_bytes(u64 type_size_in_bytes, u64 element_count)
{
	return type_size_in_bytes * element_count;
}

bool sunder_is_divisible_by(u64 val, u64 div)
{
	if (div == 0) { return false; }

	return val % div == 0;
}

sunder_arena_suballocation_result_t sunder_suballocate_from_arena_internal(sunder_arena_t* arena, u64 bytes, u32 alignment)
{
	sunder_arena_suballocation_result_t res;
	const u64 working_alignment = sunder_clamp_u32(SUNDER_ARENA_SUBALLOCATION_MIN_ALIGNMENT, SUNDER_ARENA_SUBALLOCATION_MAX_ALIGNMENT, alignment);

	const u64 aligned_offset = sunder_align64(arena->offset, working_alignment);
	const u64 post_suballocation_offset = aligned_offset + bytes;

	res.result = SUNDER_ARENA_RESULT_OUT_OF_ARENA_MEMORY;
	if (post_suballocation_offset > arena->capacity) { return res; }

	void* data = &arena->buffer[aligned_offset];
	arena->offset = post_suballocation_offset;

	res.result = SUNDER_ARENA_RESULT_SUCCESS;
	res.data = data;
	return res;
}

sunder_arena_suballocation_result_t sunder_suballocate_from_arena_debug_internal(sunder_arena_t* arena, u64 bytes, u32 alignment)
{
	sunder_arena_suballocation_result_t res;
	res.data = nullptr;
	
	const u32 working_alignment = sunder_clamp_u32(SUNDER_ARENA_SUBALLOCATION_MIN_ALIGNMENT, SUNDER_ARENA_SUBALLOCATION_MAX_ALIGNMENT, alignment);

	std::cout << "\n" << arena->offset << "/" << arena->capacity;
	std::cout << "\nrequested alignment: " << alignment;
	std::cout << "\nworking alignment: " << working_alignment;
	std::cout << "\nallocating " << bytes << " bytes";
	std::cout << "\ncurrent offset: " << arena->offset;

	const u64 aligned_offset = sunder_align64(arena->offset, working_alignment);
	const u64 bytes_of_padding = aligned_offset - arena->offset;
	const u64 post_suballocation_offset = aligned_offset + bytes;

	res.result = SUNDER_ARENA_RESULT_OUT_OF_ARENA_MEMORY;

	if (post_suballocation_offset > arena->capacity)
	{
		return res;
	}

	SUNDER_LOG("\ndata assigned offset: ");
	SUNDER_LOG(aligned_offset);
	SUNDER_LOG("\nbytes of padding added: ");
	SUNDER_LOG(bytes_of_padding);
	SUNDER_LOG("\npost suballocation offset: ");
	SUNDER_LOG(post_suballocation_offset);
	SUNDER_LOG("\n");

	void* user_block = &arena->buffer[aligned_offset];

	arena->offset = post_suballocation_offset;

	res.result = SUNDER_ARENA_RESULT_SUCCESS;
	res.data = user_block;

	return res;
}

sunder_arena_result sunder_converge_arena_chain_debug(sunder_arena_t* arena)
{
	return SUNDER_ARENA_RESULT_SUCCESS;
}

sunder_arena_result sunder_allocate_arena(sunder_arena_t* arena, u64 capacity, u32 arena_alignment)
{
	if (capacity == 0)
	{
		return SUNDER_ARENA_RESULT_FAILURE;
	}

	if (arena_alignment < 2 || !sunder_is_power_of_2(arena_alignment))
	{
		return SUNDER_ARENA_RESULT_FAILURE;
	}

	arena->buffer = (u8*)sunder_aligned_halloc(capacity, arena_alignment);

	if (arena->buffer == nullptr)
	{
		return SUNDER_ARENA_RESULT_OS_MEMORY_ALLOCATION_FAILURE; 
	}

	arena->capacity = capacity;
	arena->offset = 0;

	sunder_initialize_buffer(arena->buffer, arena->capacity, 0, arena->capacity);

	return SUNDER_ARENA_RESULT_SUCCESS;
}

sunder_arena_suballocation_result_t sunder_suballocate_from_arena(sunder_arena_t* arena, u64 bytes, u32 alignment)
{
	return sunder_suballocate_from_arena_internal(arena, bytes, alignment);
}

sunder_arena_suballocation_result_t sunder_suballocate_from_arena_debug(sunder_arena_t* arena, u64 bytes, u32 alignment)
{
	return sunder_suballocate_from_arena_debug_internal(arena, bytes, alignment);
}

sunder_arena_result sunder_free_arena(sunder_arena_t* arena)
{
	if (arena == nullptr) { return SUNDER_ARENA_RESULT_ARENA_UNINITIALIZED; }
	if (arena->buffer == nullptr) { return SUNDER_ARENA_RESULT_BUFFER_UNINITIALIZED; }

	arena->offset = 0;
	arena->capacity = 0;

	// later account for chained arena specification

	sunder_aligned_free((void**)&arena->buffer);

	return SUNDER_ARENA_RESULT_SUCCESS;
}

u64 sunder_get_aligned_struct_allocation_size_debug(const u64* alignment_buffer, const u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment)
{
	u64 offset = 0;
	u64 aligned_offset = 0;
	u64 bytes_of_padding = 0;

	for (u64 i = 0; i < buffer_size; i++)
	{
		SUNDER_LOG("\nrequested alignment: ");
		SUNDER_LOG(alignment_buffer[i]);
		aligned_offset = sunder_align64(offset, alignment_buffer[i]);
		SUNDER_LOG("\nallocating ");
		SUNDER_LOG(allocation_size_buffer[i]);
		SUNDER_LOG(" bytes");
		SUNDER_LOG("\ncurrent offset: ");
		SUNDER_LOG(offset);
		SUNDER_LOG("\naligned offset: ");
		SUNDER_LOG(aligned_offset);
		bytes_of_padding = aligned_offset - offset;
		SUNDER_LOG("\nbytes of padding added: ");
		SUNDER_LOG(bytes_of_padding);
		offset = aligned_offset + allocation_size_buffer[i];
		SUNDER_LOG("\npost allocation offset: ");
		SUNDER_LOG(offset);
		SUNDER_LOG("\n");
	}

	SUNDER_LOG("\nrequested alignment: ");
	SUNDER_LOG(struct_alignment);
	SUNDER_LOG("\nallocating ");
	SUNDER_LOG(0);
	SUNDER_LOG(" bytes");
	SUNDER_LOG("\ncurrent offset: ");
	SUNDER_LOG(offset);
	aligned_offset = sunder_align64(offset, struct_alignment);
	SUNDER_LOG("\naligned offset: ");
	SUNDER_LOG(aligned_offset);
	bytes_of_padding = aligned_offset - offset;
	SUNDER_LOG("\nbytes of padding added: ");
	SUNDER_LOG(bytes_of_padding);
	offset = aligned_offset;
	SUNDER_LOG("\npost allocation offset: ");
	SUNDER_LOG(offset);
	SUNDER_LOG("\n");

	return offset;
}

u64 sunder_get_aligned_struct_allocation_size(const u64* alignment_buffer, const u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment)
{
	u64 offset = 0;
	u64 aligned_offset = 0;
	u64 bytes_of_padding = 0;

	for (u64 i = 0; i < buffer_size; i++)
	{
		aligned_offset = sunder_align64(offset, alignment_buffer[i]);
		bytes_of_padding = aligned_offset - offset;
		offset = aligned_offset + allocation_size_buffer[i];
	}

	aligned_offset = sunder_align64(offset, struct_alignment);
	bytes_of_padding = aligned_offset - offset;
	offset = aligned_offset;

	return offset;
}

u64 sunder_initialize_buffer(void* buffer, u64 buffer_size, u64 starting_offset, u64 bytes_to_init)
{
	if (buffer == nullptr) { return 0; }
	if (starting_offset + bytes_to_init > buffer_size) { return 0; }
	if (starting_offset > buffer_size) { return 0; }

	i8* temp_ram_buffer_ptr = (i8*)buffer;

	for (u64 i  = starting_offset; i < bytes_to_init; i++)
	{
		temp_ram_buffer_ptr[i] = 0;
	}

	return bytes_to_init - starting_offset;
}

u64 sunder_compute_aligned_allocation_size(u64 type_size_in_bytes, u64 element_count, u64 alignment)
{
	return sunder_align64(sunder_compute_array_size_in_bytes(type_size_in_bytes, element_count), alignment);
}


u8 sunder_to_bit_mask8(const sunder_bit_index_buffer8_t& storage, u32 count)
{
	u8 mask = 0;
	u8 merged_count = 0;
	const u16 bit_count = sizeof(u8) * 8;

	SUNDER_TO_BIT_MASK(u8, 1, mask, storage, count, merged_count, bit_count);
	if (mask == 0) { return UINT8_MAX; }
	if (merged_count != count) { return UINT8_MAX; }

	return mask;
}

u16 sunder_to_bit_mask16(const sunder_bit_index_buffer16_t& storage, u32 count)
{
	u16 mask = 0;
	u16 merged_count = 0;
	const u16 bit_count = sizeof(u16) * 8;

	SUNDER_TO_BIT_MASK(u16, 1, mask, storage, count, merged_count, bit_count);
	if (mask == 0) { return UINT16_MAX; }
	if (merged_count != count) { return UINT16_MAX; }

	return mask;
}

u32 sunder_to_bit_mask32(const sunder_bit_index_buffer32_t& storage, u32 count)
{
	u32 mask = 0;
	u32 merged_count = 0;
	const u16 bit_count = sizeof(u32) * 8;

	SUNDER_TO_BIT_MASK(u32, 1U, mask, storage, count, merged_count, bit_count);
	if (mask == 0) { return UINT32_MAX; }
	if (merged_count != count) { return UINT32_MAX; }

	return mask;
}

u64 sunder_to_bit_mask64(const sunder_bit_index_buffer64_t& storage, u32 count)
{
	u64 mask = 0;
	u64 merged_count = 0;
	const u16 bit_count = sizeof(u64) * 8;

	SUNDER_TO_BIT_MASK(u64, 1ULL, mask, storage, count, merged_count, bit_count);
	if (mask == 0) { return UINT64_MAX; }
	if (merged_count != count) { return UINT64_MAX; }

	return mask;
}

SUNDER_IMPLEMENT_EXISTS_FUNCTION(u32, sunder, u32, u32)

void sunder_invoke_function_on_thread_launch(sunder_thread_function_ptr function_ptr, void* args)
{
	function_ptr(args);
}

void sunder_launch_thread(sunder_thread_t* thread, sunder_thread_function_ptr function_ptr, void* args)
{
	thread->thread = std::thread(function_ptr, args);
}

void sunder_join_thread(sunder_thread_t* thread)
{
	if (thread->thread.joinable())
	{
		thread->thread.join();
	}
}

void sunder_detach_thread(sunder_thread_t* thread)
{
	thread->thread.detach();
}

void sunder_sleep_on_current_thread_for(f64 seconds)
{
	std::this_thread::sleep_for(std::chrono::duration<f64>(seconds));
}

sunder_thread_id sunder_get_current_thread_id()
{
	return std::this_thread::get_id();
}

void sunder_initialize_time()
{
	sunder_initial_time = std::chrono::steady_clock::now();
}

f64 sunder_get_elapsed_time_in_seconds()
{
	return std::chrono::duration<f64>(std::chrono::steady_clock::now() - sunder_initial_time).count();
}

SUNDER_IMPLEMENT_CLAMP_FUNCTION(i8);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(i16);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(i32);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(i64);

SUNDER_IMPLEMENT_CLAMP_FUNCTION(u8);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(u16);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(u32);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(u64);

SUNDER_IMPLEMENT_CLAMP_FUNCTION(f32);
SUNDER_IMPLEMENT_CLAMP_FUNCTION(f64);

bool sunder_compare_strings(cstring_literal* str1, u32 str1_size, cstring_literal* str2, u32 str2_size)
{
	if (str1_size != str2_size)
	{
		return false;
	}

	for (u32 i = 0; i < str1_size; i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}

	return true;
}

SUNDER_IMPLEMENT_QUERY_BUFFER_INDEX_FUNCTION(u32, sunder, u32, u32)

SUNDER_IMPLEMENT_QUICK_SORT_PARTITION_FUNCTION(sunder_arena_free_memory_block_t, arena_free_memory_block, sunder)
SUNDER_IMPLEMENT_QUICK_SORT_FUNCTION(sunder_arena_free_memory_block_t, arena_free_memory_block, sunder)

void sunder_log_string(const sunder_string_t* string)
{
	const u32 length = string->length;

	for (u32 i = 0; i < length; i++)
	{
		SUNDER_LOG(string->data[i]);
	}
}

u64 sunder_update_aligned_value_u64(u64 val, u64 update_val, u32 alignment)
{
	u64 local_val = val;
	local_val += update_val;
	local_val = sunder_align64(local_val, alignment);

	return local_val;
}

u32 sunder_update_aligned_value_u32(u32 val, u32 update_val, u32 alignment)
{
	u32 local_val = val;
	local_val += update_val;
	local_val = sunder_align32(local_val, alignment);

	return local_val;
}

u64 sunder_kilobytes_to_bytes(u64 kb)
{
	return kb * 1024;
}

u64 sunder_megabytes_to_bytes(u64 mb)
{
	return sunder_kilobytes_to_bytes(1024) * mb;
}

bool sunder_valid_index(u32 index, u32 element_count)
{
	return !(index > element_count - 1);
}

bool sunder_valid_offset(u64 offset, u64 capacity)
{
	return !(offset > capacity - 1);
}

u64 sunder_compute_aligned_array_allocation_size(u64 type_size_in_bytes, u64 element_count, u32 alignment)
{
	u64 aligned_allocation_size = 0;

	for (u64 i = 0; i < element_count; i++)
	{
		aligned_allocation_size += sunder_align64(type_size_in_bytes, alignment);
		aligned_allocation_size = sunder_align64(aligned_allocation_size, alignment); // probably obsolete
	}

	return aligned_allocation_size;
}

u64 sunder_accumulate_aligned_allocation_size(const u64* aligned_allocation_size_buffer, u64 element_count, u32 alignment)
{
	u64 accumulated_allocation_size = 0;

	for (u64 i = 0; i < element_count; i++)
	{
		accumulated_allocation_size += aligned_allocation_size_buffer[i];
		accumulated_allocation_size = sunder_align64(accumulated_allocation_size, alignment);
	}

	return accumulated_allocation_size;
}

i32 sunder_int_to_string(i64 value, char* result, u32 base)
{// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return -1; }

	i64 original_value = value;
	char* ptr = result, * ptr1 = result, tmp_char;
	i64 tmp_value{};
	i32 length = 0;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
		length++;
	} while (value);

	// Apply negative sign
	if (original_value < 0)
	{
		*ptr++ = '-';
	}

	*ptr-- = '\0';

	// Reverse the string
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}

	return length;
}

i32 sunder_uint_to_string(u64 value, char* result, u32 base)
{
	if (base < 2 || base > 36) { *result = '\0'; return -1; }

	char* ptr = result, * ptr1 = result, tmp_char;
	u64 tmp_value{};
	i32 length = 0;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
		length++;
	} while (value);

	*ptr-- = '\0';

	// Reverse the string
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}

	return length;
}

i32 sunder_float_to_string(f64 value, char* result, u32 precision, u32 base)
{
	if (base < 2 || base > 36 || !result) return -1;

	char* ptr = result;
	i32 length = 0;

	// Handle negative values
	if (value < 0) {
		*ptr++ = '-';
		value = -value;
		length++;
	}

	// Extract integer part
	i64 int_part = (i64)value;

	// Convert integer part using your function
	i32 int_len = sunder_int_to_string(int_part, ptr, base);
	if (int_len < 0) return -1; // error from integer conversion

	ptr += int_len;
	length += int_len;

	// If no precision needed, terminate here
	if (precision == 0) {
		*ptr = '\0';
		return length;
	}

	*ptr++ = '.';  // add decimal point
	length++;

	// Extract fractional part
	f64 frac_part = value - int_part;

	// Convert fractional part
	for (u32 i = 0; i < precision; i++) {
		frac_part *= base;
		i64 digit = (i64)frac_part;
		// For bases > 10, convert digit to corresponding char
		if (digit < 10)
			*ptr++ = '0' + (char)digit;
		else
			*ptr++ = 'a' + ((char)digit - 10);
		frac_part -= digit;
		length++;
	}

	*ptr = '\0';
	return length;
}