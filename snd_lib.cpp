#include "snd_lib.h"
#include <ctime>

//namespace sunder
//{
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

	void sunder_aligned_ffree(void** memblock)
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

	i16 sunder_rand_s16(i16 start, i16 end)
	{
		i16 diapason = end - start;

		return rand() % (diapason + 1) + start;
	}

	i32 sunder_rand_s32(i32 start, i32 end)
	{
		i32 diapason = end - start;

		return rand() % (diapason + 1) + start;
	}

	i64 sunder_rand_s64(i64 start, i64 end)
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

	u64 sunder_copy_buffer(void* bytes_to_copy_to, const void* bytes_to_copy, u64 bytes_to_copy_to_size, u64 bytes_to_copy_size, u64 bytes_to_write)
	{
		if (bytes_to_copy_to == nullptr) { return 0; }
		if (bytes_to_copy == nullptr) { return 0; }

		i8* temp_bytes_to_copy_to = (i8*)bytes_to_copy_to;
		i8* temp_bytes_to_copy = (i8*)bytes_to_copy;

		if (bytes_to_write > bytes_to_copy_to_size || bytes_to_write > bytes_to_copy_size || bytes_to_write == 0) { return 0; }

			for (u64 i = 0; i < bytes_to_write; i++)
			{
				temp_bytes_to_copy_to[i] = temp_bytes_to_copy[i];
			}

		return bytes_to_write;
	}

	bool sunder_is_even(u64 val)
	{
		return val % 2 == 0;
	}

	bool sunder_is_power_of_2(u64 val)
	{
		return val != 0 && (val & (val - 1)) == 0;;
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

	sunder_arena_suballocation_result_t sunder_suballocate_from_arena_internal(u64* offset, u64* padding, u8* buffer, u64 capacity, u64 bytes, u64 alignment)
	{
		sunder_arena_suballocation_result_t res;
		res.result = ARENA_RESULT_BUFFER_UNINITIALIZED;
		if (buffer == nullptr) { return res; }
		
		u64 aligned_offset = sunder_align64(*offset, alignment);
		u64 bytes_of_padding = aligned_offset - (*offset);

		res.result = ARENA_RESULT_OUT_OF_MEMORY;
		if (aligned_offset + bytes > capacity) { return res; }

		(*padding) += bytes_of_padding;
		void* data = &buffer[aligned_offset];
		(*offset) = aligned_offset + bytes;

		res.result = ARENA_RESULT_SUCCESS;
		res.data = data;
		return res;
	}

	sunder_arena_suballocation_result_t sunder_suballocate_from_arena_internal_debug(u64* offset, u64* padding, u8* buffer, u64 capacity, u64 bytes, u64 alignment)
	{
		sunder_arena_suballocation_result_t res;
		res.result = ARENA_RESULT_BUFFER_UNINITIALIZED;
		if (buffer == nullptr) { return res; }

		std::cout << "\n" << *offset << "/" << capacity;
		std::cout << "\nrequested alignment: " << alignment;
		std::cout << "\nallocating " << bytes << " bytes";
		std::cout << "\ncurrent offset: " << *offset;
		u64 aligned_offset = sunder_align64(*offset, alignment);
		u64 bytes_of_padding = aligned_offset - (*offset);

		res.result = ARENA_RESULT_OUT_OF_MEMORY;
		if (aligned_offset + bytes > capacity) { return res; }

		std::cout << "\nbytes of padding added: " << bytes_of_padding;
		(*padding) += bytes_of_padding;
		std::cout << "\naligned offset: " << aligned_offset;
		void* data = &buffer[aligned_offset];
		std::cout << "\ndata assigned at: " << aligned_offset;
		(*offset) = aligned_offset + bytes;
		std::cout << "\npost allocation offset: " << *offset << "\n";

		res.result = ARENA_RESULT_SUCCESS;
		res.data = data;
		return res;
	}

	sunder_arena_result sunder_allocate_arena_internal(u8** buffer, u64* arena_capacity, u64 requested_capacity, u64 buffer_alignment)
	{
		if (!sunder_is_even(requested_capacity)) { return ARENA_RESULT_REQUESTED_ARENA_ALLOCATION_SIZE_IS_NOT_EVEN; }

		//(*buffer) = SUNDER_HALLOC(u8, requested_capacity);
		*buffer = (u8*)sunder_aligned_halloc(requested_capacity, buffer_alignment);

		if (*buffer == NULL) { return ARENA_RESULT_OS_MEMORY_ALLOCATION_FAILURE; }
		**buffer = {};
		(*arena_capacity) = requested_capacity;

		return ARENA_RESULT_SUCCESS;
	}

	sunder_arena_result sunder_allocate_arena(sunder_arena_t* arena, u64 bytes, u64 alignment, sunder_arena_type arena_type, u32 chain_count)
	{
		arena->type = arena_type;

		if (arena_type == ARENA_TYPE_CHAINED)
		{
			arena->chain_count = chain_count;
		}

		return sunder_allocate_arena_internal(&arena->buffer, &arena->capacity, bytes, alignment);
	}

	sunder_arena_suballocation_result_t sunder_suballocate_from_arena(sunder_arena_t* arena, u64 bytes, u64 alignment)
	{
		sunder_arena_suballocation_result_t res;
		res.result = ARENA_RESULT_ARENA_UNINITIALIZED;
		if (arena == nullptr) { return res; }

		return sunder_suballocate_from_arena_internal(&arena->offset, &arena->total_bytes_of_padding, arena->buffer, arena->capacity, bytes, alignment);
	}

	sunder_arena_suballocation_result_t sunder_suballocate_from_arena_debug(sunder_arena_t* arena, u64 bytes, u64 alignment)
	{
		sunder_arena_suballocation_result_t res;
		res.result = ARENA_RESULT_ARENA_UNINITIALIZED;
		if (arena == nullptr) { return res; }

		return sunder_suballocate_from_arena_internal_debug(&arena->offset, &arena->total_bytes_of_padding, arena->buffer, arena->capacity, bytes, alignment);
	}

	sunder_arena_result sunder_reset_arena(sunder_arena_t* arena)
	{
		if (arena == nullptr) { return ARENA_RESULT_ARENA_UNINITIALIZED; }

		arena->offset = 0;
		arena->total_bytes_of_padding = 0;

		return ARENA_RESULT_SUCCESS;
	}

	sunder_arena_result sunder_free_arena(sunder_arena_t* arena)
	{
		if (arena == nullptr) { return ARENA_RESULT_ARENA_UNINITIALIZED; }
		if (arena->buffer == nullptr) { return ARENA_RESULT_BUFFER_UNINITIALIZED; }

		sunder_reset_arena(arena);
		sunder_aligned_ffree((void**)&arena->buffer);

		return ARENA_RESULT_SUCCESS;
	}

	u64 sunder_get_aligned_struct_allocation_size_debug(u64* alignment_buffer, u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment)
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

	u64 sunder_get_aligned_struct_allocation_size(u64* alignment_buffer, u64* allocation_size_buffer, u64 buffer_size, u64 struct_alignment)
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

	u64 sunder_init_buffer(void* ram_buffer, u64 ram_buffer_size, u64 starting_offset, u64 ending_offset)
	{
		if (ram_buffer == nullptr) { return 0; }
		if (starting_offset + ending_offset > ram_buffer_size) { return 0; }
		if (starting_offset > ram_buffer_size) { return 0; }

		i8* temp_ram_buffer_ptr = (i8*)ram_buffer;

		for (u64 i  = starting_offset; i < ending_offset; i++)
		{
			temp_ram_buffer_ptr[i] = 0;
		}

		return ending_offset - starting_offset;
	}
//}