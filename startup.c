#include <stdint.h>

extern int main(void);

__attribute__ ((__section__ (".startuptext"))) void reset_handler(void)
{
	//symbols defined in linker script
	extern uint32_t _mytext_lma_start;
	extern uint32_t _mytext_vma_start;
	extern uint32_t _mytext_vma_end;
	extern uint32_t _mydata_vma_start;
	extern uint32_t _mydata_vma_end;
	extern uint32_t _mybss_vma_start;
	extern uint32_t _mybss_vma_end;
	//note that for the variables above, "symbol value" is equivalent to the address we want
	//use "&" operator to get symbol values

	uint32_t *mytext_lstart_ptr = &_mytext_lma_start;
	uint32_t *mytext_vstart_ptr = &_mytext_vma_start;
	uint32_t *mytext_vend_ptr = &_mytext_vma_end;

	uint32_t *mydata_vstart_ptr = &_mydata_vma_start;
	uint32_t *mydata_vend_ptr = &_mydata_vma_end;

	uint32_t *mybss_vstart_ptr = &_mybss_vma_start;
	uint32_t *mybss_vend_ptr = &_mybss_vma_end;

	uint32_t *src_ptr, *dst_ptr;

	src_ptr = mytext_lstart_ptr;
	dst_ptr = mytext_vstart_ptr;

	while (dst_ptr < mytext_vend_ptr)
		*dst_ptr++ = *src_ptr++;

	dst_ptr = mydata_vstart_ptr;

	while (dst_ptr < mydata_vend_ptr)
		*dst_ptr++ = *src_ptr++;

	dst_ptr = mybss_vstart_ptr;

	while (dst_ptr < mybss_vend_ptr)
		*dst_ptr++ = 0;

	main();
}
