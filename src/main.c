/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include <speex/speex.h>

#define FRAME_SIZE 320
#define BUFFER_SIZE 10000


char input_bytes[BUFFER_SIZE];
short output_frame[FRAME_SIZE];

int main(void)
{
	SpeexBits bits;

	void *dec_state;

	speex_bits_init(&bits);
	dec_state = speex_decoder_init(&speex_wb_mode);

	int frame_size;
	speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);

	int enh = 0;
	speex_decoder_ctl(dec_state, SPEEX_SET_ENH, &enh);



	char* ptr = input_bytes;
	while (1)
	{
		// decode byte size
		int wbBytes = *((int*)ptr);
		if(wbBytes == 0) break;

		ptr+=sizeof(int);

		/*Copy the data into the bit-stream struct*/
		speex_bits_read_from(&bits, ptr, wbBytes);

		/*Decode the data*/
		speex_decode_int(dec_state, &bits, output_frame);

		//play output frame

		//next speex frame
		ptr+=wbBytes;
	}

	speex_bits_destroy(&bits);
	speex_decoder_destroy(dec_state);

	for(;;);
}
